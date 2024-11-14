#pragma once

#include <stdint.h>
#include <stdbool.h>

#define NaN 0.f / 0.f

#ifndef NULL
#define NULL ((void*)0)
#endif

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

int string_length(char s[]);

void reverse(char s[]);

void int_to_string(int n, char str[]);
void double_to_string(double n, char str[], int precision);

double c_pow (double base, int exponent);
float strToFloat(const char string[]);
bool backspace(char s[]);

void append(char s[], char n);

int compare_string(char s1[], char s2[]);

void copy_string(char s1[], char s2[]);