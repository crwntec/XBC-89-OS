#include "util.h"

void tokenize(const char str[], char buf[][256]) {
    int i = 0, j = 0;
    int negate = 0;
    
    while (str[i] != '\0' && j < 255) {
        if (is_space(str[i])) {
            i++;
            continue;
        }
        
        if (str[i] == '-' && (i == 0 || !is_digit(str[i - 1]))) {
            negate = 1;  // Set negate if '-' is a negative sign, not an operator
            i++;
            continue;
        }
        
        if (is_digit(str[i]) || str[i] == '.') {
            int k = 0;
            if (negate) {
                buf[j][k++] = '-';
                negate = 0;
            }
            while ((is_digit(str[i]) || str[i] == '.') && k < 255) {
                buf[j][k++] = str[i++];
            }
            buf[j][k] = '\0';  // Null-terminate the current token
            j++;
        } else {
            buf[j][0] = str[i];
            buf[j][1] = '\0';  // Null-terminate for single-character tokens
            j++;
            i++;
        }
    }
}
