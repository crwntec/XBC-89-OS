disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh

    jne sectors_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR_MESSAGE
    call print
    jmp $
sectors_error:
    mov bx, SECTOR_MISMATCH_MESSAGE
    call print
    jmp $

DISK_ERROR_MESSAGE:
    db 'Disk read error', 0

SECTOR_MISMATCH_MESSAGE:
    db 'Sectors read do not match requirements', 0