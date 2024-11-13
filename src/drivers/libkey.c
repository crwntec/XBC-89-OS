#include <stdint.h>
#include <drivers/libscreen.h>
#include <cpu/isr.h>
#include <cpu/low_level.h>
#include <kernel/util.h>
#include <kernel/kernel.h>

#define SC_MAX 57

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define LSHIFT 0x2A
#define LCTRL 0x1D

static char key_buffer[256];

bool shift = false;
bool ctrl = false;

const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', 'ß', '\'', '?', '?', 'q', 'w', 'e', 'r', 't', 'z',
                         'u', 'i', 'o', 'p', 'ü', '+', '?', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', 'ö', 'ä', '#', '?', '<', 'y', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '-', '?', '?', '?', ' '};

const char sc_ascii_shift[] = {'?', '?', '!', '@', '§', '$', '%', '&',
                               '/', '(', ')', '=', '?', '`', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Z',
                               'U', 'I', 'O', 'P', '{', '*', '?', '?', 'A', 'S', 'D', 'F', 'G',
                               'H', 'J', 'K', 'L', 'Ö', '"', '~', '?', '|', 'Y', 'X', 'C', 'V',
                               'B', 'N', 'M', ';', ':', '?', '?', '?', '?', '?'};

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        if (backspace(key_buffer)) {
            print_backspace();
        }
    } else if (scancode == ENTER) {
        print_nl();
        execute(key_buffer);
        key_buffer[0] = '\0';
    } else if (scancode == LSHIFT) {
        shift = true;
    } else if (scancode == LCTRL) {
        ctrl = true;
    }
    else {
        char letter = shift ? sc_ascii_shift[(int)scancode] : sc_ascii[(int)scancode];
        if (ctrl) {
            execute_combination(letter);

        } else {
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print_string(str);
        }
        shift = false;
        ctrl = false;
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
    print_string("Keyboard initialized.\n");
}