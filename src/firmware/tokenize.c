#include "util.h"

void tokenize(const char str[], char buf[][256])
{
    int i = 0;
    int j = 0;
    while (str[i] != '\0' && i < 255)
    {
        if (is_space(str[i]))
        {
            i++;
            continue;
        }
        if (is_digit(str[i]) || str[i] == '.')
        {
            int lookOutOffset = i;
            int k = 0;
            while (is_digit(str[lookOutOffset]) || str[lookOutOffset] == '.')
            {
                if (k < 255)
                { // Prevent overflow in numBuf
                    buf[j][k++] = str[lookOutOffset++];
                }
                else
                {
                    break;
                }
            }
            buf[j][k] = '\0';
            j++;
            i = lookOutOffset;
        }
        else
        {
            // Directly add the operator or parentheses to buf
            if (j < 255)
            {
                buf[j][0] = str[i];
                buf[j][1] = '\0'; // Add a space after the operator for separation
                j++;
            }
            i++; // Move to the next character
        }
    }
}
