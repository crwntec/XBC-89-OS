#include <drivers/libscreen.h>

int is_space(const char c) { return c == ' '; }

int is_digit(char c)
{
    return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
}

int is_num(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (!is_digit(s[i]) && s[i] != '.')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int is_op(char s[])
{
    char c = s[0];
    char operands[] = "+-*/";
    int i = 0;
    while (operands[i]!='\0') {
        if (c==operands[i]) return 1;
        i++;
    }
    
    return 0;
}