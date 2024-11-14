#include <drivers/libscreen.h>

int is_space(const char c) { return c == ' '; }

int is_digit(char c)
{
    return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
}

int is_num(char s[])
{
    int i = 0;
    if (s[i] == '-') i++;
    int has_digit = 0;
    int has_decimal = 0;
    while (s[i] != '\0')
    {
        if (is_digit(s[i])) {
            has_digit = 1;
        } else if (s[i] == '.' && !has_decimal) {
            has_decimal = 1;  // Allow only one decimal point
        } else {
            return 0;  // Invalid character found
        }
        i++;
    }
    return has_digit;
}

int is_op(char s[])
{
    char c = s[0];
    char operands[] = "+-*/";
    int i = 0;
    while (operands[i]!='\0') {
        if (c==operands[i]) {
            return 1;
        };
        i++;
    }
    
    return 0;
}