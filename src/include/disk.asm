disk_load:
    push dx
    mov ah, 0x02        ; Set BIOS to read mode
    mov dl, [BOOT_DRIVE] ; Use the stored boot drive value
    mov ch, 0           ; Select cylinder 0
    mov dh, 0           ; Select head 0
    mov cl, 2           ; Start reading from sector 2
    mov al, 1           ; Read 1 sector

    int 0x13            ; Call read interrupt

    pop dx
    jc disk_error       ; Jumps if carry flag was set
    cmp al, 1           ; Compare number of sectors read (should be 1)
    jne disk_error      ; Jump if not equal
    ret

disk_error:
    mov bx, DISK_ERROR_MESSAGE
    call print
    hlt                 ; Halt execution

DISK_ERROR_MESSAGE:
    db 'Disk read error', 0
