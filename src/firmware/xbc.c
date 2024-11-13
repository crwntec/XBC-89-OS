#include <kernel/util.h>
#include <drivers/libscreen.h>
#include "eval.h"
#include "tokenize.h"

float calculate(char str[])
{
    char tokenBuffer[256][256] = {0};
    tokenize(str, tokenBuffer);

    char outputBuffer[256][256] = {0};
    shunt(tokenBuffer, outputBuffer);
    float result = evaluate(outputBuffer); // Store the result from evaluate
    if (result != result) {
        return NaN;
    }
    return result;
}
