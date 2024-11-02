[org 0x7c00]
KERNEL_OFFSET equ 0x1000

; Set Boot drive to current drive
mov [BOOT_DRIVE], dl

; Setup stack
mov bp, 0x8000
mov sp, bp

mov bx, REAL_MODE_MESSAGE
call print

call load_kernel

call switch_to_pm

jmp $
; INCLUDES
%include "print.asm"
%include "disk.asm"
%include "gdt.asm"
%include "print_pm.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET_MESSAGE
    call print

    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov ah, 0x0
    mov al, 0x3
    int 0x10
    
    ret

[bits 32]
BEGIN_PM:
    mov ebx, PROTECTED_MODE_MESSAGE
    call print_pm

    call KERNEL_OFFSET

    jmp $

; Store the boot drive value
BOOT_DRIVE: db 0

REAL_MODE_MESSAGE: db 'Started in 16-bit real mode', 0
REAL_MODE_GDT_MESSAGE: db 'GDT loaded', 0
PROTECTED_MODE_MESSAGE: db 'Enabled 32-bit protected mode', 0
KERNEL_OFFSET_MESSAGE: db 'Loaded kernel', 0


; Padding and magic number
times 510-($-$$) db 0
dw 0xaa55
