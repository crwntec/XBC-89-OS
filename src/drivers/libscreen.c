#include "libscreen.h"
#include "kernel/low_level.h"

int get_screen_offset(int col, int row)
{
    return (row * MAX_COLS + col) * 2;
}

int get_row_from_offset(int offset) {
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

void print_string(char *string)
{
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0)
    {
        if (string[i] == "\n")
        {
            offset = get_screen_offset(0, get_row_from_offset(offset) + 1);
        }
        else
        {
            set_char_at(string[i], offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
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