#include <drivers/libscreen.h>
#include <drivers/libkey.h>
#include <cpu/isr.h>
#include "util.h"

void execute_command(char *input) {
   if (compare_string(input, "EXIT") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (compare_string(input, "") == 0) {
        print_string("\n> ");
    }
    else {
        print_string("Unknown command: ");
        print_string(input);
        print_string("\n> ");
    }
}

int main()
{
    clear_screen();
    print_string("Installing interrupt service routines.\n");
    isr_install();
    
    print_string("Enabling external interrupts.\n");
    asm volatile ("sti");

    print_string("Initializing keyboard.\n");
    init_keyboard();

    clear_screen();
    print_string("> ");

    return 0;
}