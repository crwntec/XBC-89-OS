#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

int get_screen_offset(int col, int row);

int get_cursor();
void set_cursor(int offset);

void set_char_at(char character, int offset);
void print_string(char *string);
void print_fmt(char* format, ...);
void print_nl();
void print_backspace();

int scroll_ln(int offset);
void clear_screen();