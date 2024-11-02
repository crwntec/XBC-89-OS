gdt_start:

gdt_null:
    dd 0x0  ; Null descriptor
    dd 0x0

gdt_code:
    dw 0xffff ; Limit (low 16 bits)
    dw 0x0    ; Base (low 16 bits)
    db 0x0    ; Base (middle)
    db 10011010b ; Flags
    db 11001111b ; Flags
    db 0x0    ; Base (high)

gdt_data:
    dw 0xffff ; Limit (low 16 bits)
    dw 0x0    ; Base (low 16 bits)
    db 0x0    ; Base (middle)
    db 10010010b ; Flags
    db 11001111b ; Flags
    db 0x0    ; Base (high)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start