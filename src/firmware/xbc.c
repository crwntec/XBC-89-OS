#include <kernel/util.h>
#include <drivers/libscreen.h>
#include "eval.h"
#include "tokenize.h"
#include "util.h"

float calculate(char str[])
{
    char tokenBuffer[256][256] = {0};
    tokenize(str, tokenBuffer);

    char outputBuffer[256][256] = {0};
    if(shunt(tokenBuffer, outputBuffer)==-1) return NaN;
    float result = evaluate(outputBuffer); // Store the result from evaluate
    if (result != result) {
        return NaN;
    }
    // Clear the token and output buffers
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < STACK_SIZE; j++) {
            tokenBuffer[i][j] = '\0';
            outputBuffer[i][j] = '\0';
        }
    }
    return result;
}
