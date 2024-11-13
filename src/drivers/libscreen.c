#include "libscreen.h"
#include <stdarg.h>
#include <cpu/low_level.h>
#include <kernel/util.h>

int get_screen_offset(int col, int row)
{
    return (row * MAX_COLS + col) * 2;
}

int get_row_from_offset(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_cursor()
{
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);

    return offset * 2;
}

void set_cursor(int offset)
{
    offset /= 2;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset & 0xff));
}

void set_char_at(char character, int offset)
{
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}
void print_char(char c)
{
    int offset = get_cursor();
    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
        offset = scroll_ln(offset);
    }
    if (c == '\n')
    {
        offset = get_screen_offset(0, get_row_from_offset(offset) + 1);
    }
    else
    {
        set_char_at(c, offset);
        offset += 2;
    }

    set_cursor(offset);
}
void print_string(char *string)
{
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0)
    {
        print_char(string[i]);
        i++;
    }
}

void print_fmt(char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int i = 0;
    int escaped = 0;
    for (i; i < string_length(format); i++)
    {
        char c = format[i];
        if (!escaped && c == '%')
        {
            escaped = 1;
            continue;
        }
        if (escaped)
        {
            switch (c)
            {
            case 'f':
            case 'd':
            { // Float / Double
                double arg = va_arg(ap, double);
                char double_str[32];
                double_to_string(arg, double_str, 10);
                print_string(double_str);
                break;
            }
            case 'i':
            { // Integer
                int arg = va_arg(ap, int);
                char int_str[12];
                int_to_string(arg,int_str);
                print_string(int_str);
                break;
            }
            case 's':
            { // string
                char *arg = va_arg(ap, char *);
                print_string(arg);
                break;
            }
            case 'c':
            { // Char
                char arg = (char)va_arg(ap, int);
                print_char(arg);
                break;
            }
            default:
                break;
            }
            escaped = 0;
        }
        else
        {
            print_char(c);
        }
    }
}

void print_nl()
{
    print_string("\n");
}

void print_backspace()
{
    set_char_at(' ', get_cursor() - 2);
    set_cursor(get_cursor() - 2);
}

int scroll_ln(int offset)
{
    memcopy(
        (char *)(get_screen_offset(0, 1) + VIDEO_ADDRESS),
        (char *)(get_screen_offset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2);
    for (int col = 0; col < MAX_COLS; col++)
    {
        set_char_at(' ', get_screen_offset(col, MAX_ROWS - 1));
    }
    return offset - 2 * MAX_COLS;
}

void clear_screen()
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            set_char_at(' ', get_screen_offset(j, i));
        }
    }
    set_cursor(0);
}