#include <drivers/libscreen.h>
#include <drivers/libkey.h>
#include <cpu/isr.h>
#include <firmware/xbc.h>
#include "util.h"

void execute(char *input) {
   if (compare_string(input, "EXIT") == 0) {
        print_string("\nStopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (compare_string(input, "") == 0) {
        print_string("\n> ");
    }
    else {
        float result = calculate(input);
        if (result==result) print_fmt("%f", result);
        print_string("\n> ");
    }
}
void execute_combination(char *input) {
    if (input == 'c') {
        execute("EXIT");
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