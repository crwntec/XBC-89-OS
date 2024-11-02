print:
    pusha               ; Save current register state
print_next_char:
    mov al, [bx]        ; Move current character to AL
    cmp al, 0           ; If current character is null, the string is terminated
    je print_done       ; Jump to return
    mov ah, 0x0e        ; Set BIOS to teletype mode
    int 0x10            ; Call print interrupt
    inc bx              ; Increment the current address to next character
    jmp print_next_char ; Continue printing

print_done:
    popa
    ret

print_hex:
    pusha
    ; DX contains the value to print
    mov bx, HEX_OUT
    call convert_hex_to_ascii ; Convert DX to ASCII and store at HEX_OUT
    mov ah, 0x0e
    mov al, [bx]        ; Print '0'
    int 0x10
    mov al, [bx + 1]    ; Print 'x'
    int 0x10
    mov al, [bx + 2]    ; Print first hexadecimal digit
    int 0x10
    mov al, [bx + 3]    ; Print second hexadecimal digit
    int 0x10
    mov al, [bx + 4]    ; Print third hexadecimal digit
    int 0x10
    mov al, [bx + 5]    ; Print fourth hexadecimal digit
    int 0x10
    popa
    ret

convert_hex_to_ascii:
    ; Convert the value in DX to an ASCII hex representation in HEX_OUT
    ; DX -> XXXX
    mov si, HEX_OUT + 2 ; Point to the third character of HEX_OUT
    mov cx, 4           ; Process four digits
convert_loop:
    rol dx, 4           ; Rotate left by 4 bits to bring the next hex digit into the lowest nibble
    mov al, dl          ; Copy the lowest nibble into AL
    and al, 0x0F        ; Mask to keep only the lower 4 bits
    cmp al, 9           ; Check if it's 0-9 or A-F
    jbe convert_digit   ; If <= 9, jump to convert_digit
    add al, 'A' - 10    ; Convert 10-15 to 'A'-'F'
    jmp store_digit

convert_digit:
    add al, '0'         ; Convert 0-9 to '0'-'9'

store_digit:
    mov [si], al        ; Store the converted digit
    inc si              ; Move to the next character
    loop convert_loop   ; Repeat for all four hex digits
    ret
HEX_OUT:
    db '0x0000', 0