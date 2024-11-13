#include <stdint.h>
#include <stdbool.h>

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = string_length(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void int_to_string(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void double_to_string(double n, char str[], int precision) {
    int int_part = (int)n;
    double frac_part = n - int_part;

    int_to_string(int_part, str);

    int i = 0;
    while (str[i]!='\0') i++;

    str[i++] = '.';

    int j = 0;
    for (j;j < precision;j++) {
        frac_part *= 10;
        int digit = (int) frac_part;
        str[i++] = digit + '0';
        frac_part -= digit;
    }

    str[i] = '\0';
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len+1] = '\0';
}

bool backspace(char s[]) {
    int len = string_length(s);
    if (len > 0) {
        s[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int compare_string(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

double c_pow (double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

float strToFloat(const char string[])
{
    int i;
    int j = 0;
    int ten = 0;
    float dec = 0; // initialize to zero
    float result = 0;

    for (i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == '-')
            continue; // skip to next iteration if string contains '-' char at front

        if (string[i] == '.' && string[i + 1] != '\0') // additional check to see if there are any chars following decimal point
        {
            for (j = i + 1; string[j] != '\0'; ++j)
            {

                /*Calculate value to right of decimal point.
                 similar technique to result's calculation*/
                dec = (dec * 10) + (string[j] - '0');

                ten = j - i; // keep track of the number of inner iterations
            }
            break; // you've grabbed every digit. Break from the outer for loop.
        }
        else
        {
            result = (result * 10) + (string[i] - '0');
        }
    }

    /*the denominator variable is the divisor of the final division calculation. The number of inner iterations (ten variable) is the power of
   10 that we need as the divisor. If the value to the right of the decimal is '234', then denominator will be 10^3 = 1000.
   This is because Length('234')=3, which is the number of inner iterations.
  */
    float denominator = c_pow(10, (float)ten);

    /* Now we'll multiply the value to the LEFT of the decimal with the denominator calculated above. This is setting up the value of the
   dividend for the final division calculation. Following from the example above, if denominator is 1000 and the value to the left of the
   decimal point is '11', then temp will be 11 * 1000 = 11000.
   */
    float temp = result * denominator;

    /* This expression will compute the final value of the dividend. We're simply adding the value to the RIGHT of the decimal point to
    temp's value from above. Following from the examples above, if the temp was computed to 11000 and the value to the right of the
    decimal point is '234', then temp's final value will be 11000 + 234 = 11234.
    */
    temp += dec;

    /* The hard part's over. The reason we went through all of that trouble is that now we can simply divide by the magnitude of the value
   to the right of the decimal point (1000 from the running example) to get the final answer. So 11234/1000 = 11.234, which was the original
   string.
   */
    result = temp / denominator;
    if (string[0] == '-')
        result *= -1; // if the string represented a negative number, perform the conversion here.
    return result;
}

void copy_string(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0')
    {
        s2[i] = s1[i];
        i++;
    }
}
