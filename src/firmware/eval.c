#include <kernel/util.h>
#include <drivers/libscreen.h>
#include "util.h"

#define END_OPERATOR  '\0'

struct operator
{
    char symbol;
    int precedence;
    int associativity;
};

struct operator OPERATORS[] = {
    {'+', 1, 0},
    {'-', 1, 0},
    {'*', 2, 1},
    {'/', 2, 1},
    {END_OPERATOR, 0, 0}  // Sentinel operator to mark the end of the list
};

int top = -1;
char stack[STACK_SIZE];

// Retrieve operator details by symbol
struct operator* get_operator(char c)
{
    for (int i = 0; OPERATORS[i].symbol != END_OPERATOR; i++)
    {
        if (OPERATORS[i].symbol == c)
            return &OPERATORS[i];
    }
    print_fmt("Error: Operator %c not found\n", c);
    return NULL;
}

int push(char c)
{
    if (top >= STACK_SIZE - 1) // Prevent stack overflow
    {
        print_string("ERROR: STACK OVERFLOW\n");
        return -1;
    }
        stack[++top] = c;
        return 0;
}

char pop()
{
    if (top == -1)
    {
        print_string("Error: Stack underflow\n");
        return NaN;
    }
    return stack[top--];
}

int shunt(char buf[][STACK_SIZE], char output[][STACK_SIZE])
{
    int i = 0, k = 0;
    while (buf[i][0] != '\0')
    {
        if (is_num(buf[i]))
        {
            copy_string(buf[i], output[k++]);
        }
        else if (is_op(buf[i]))
        {
            if (is_op(buf[i + 1]) && buf[i + 1][0] != '-') {
                print_string("SYNTAX ERROR: INVALID SYNTAX");
                return -1;
            }
            
            struct operator* op = get_operator(buf[i][0]);
            if (op == NULL) {
                print_string("SYNTAX ERROR: UNKNOWN OPERATOR\n");
                return -1;
            }

            while (top != -1 && stack[top] != '(' &&
                   (get_operator(stack[top])->precedence > op->precedence ||
                    (get_operator(stack[top])->precedence == op->precedence && op->associativity == 1)))
            {
                output[k][0] = pop();
                output[k++][1] = '\0';
            }
            push(op->symbol);
        }
        else if (buf[i][0] == '(')
        {
            push('(');
        }
        else if (buf[i][0] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                output[k][0] = pop();
                output[k++][1] = '\0';
            }
            if (top == -1 || stack[top] != '(') {
                print_string("SYNTAX ERROR: MISMATCHED PARENTHESES\n");
                return NaN;
            }
            pop(); // Discard the '('
        }
        else {
            print_string("SYNTAX ERROR: UNKNOWN SYMBOL\n");
            return -1;
        }
        i++;
    }

    while (top != -1)
    {
        if (stack[top] == '(') {
            print_string("SYNTAX ERROR: MISMATCHED PARENTHESES\n");
            return -1;
        }
        output[k][0] = pop();
        output[k++][1] = '\0';
    }
    return 0;
}

float evaluate(char buf[][STACK_SIZE])
{
    int i = 0;
    int top = -1;
    float numStack[STACK_SIZE];
    while (buf[i][0] != '\0')
    {
        if (is_num(buf[i]))
        {
            numStack[++top] = strToFloat(buf[i]);
        }
        else if (is_op(buf[i]))
        {
            struct operator* op = get_operator(buf[i][0]);
            if (!op) {
                print_string("Error: Unknown operator\n");
                return NaN;
            }
            float right = numStack[top--];
            float left = numStack[top];
            switch (op->symbol)
            {
                case '+': numStack[top] = left + right; break;
                case '-': numStack[top] = left - right; break;
                case '*': numStack[top] = left * right; break;
                case '/':
                    if (right == 0) {
                        print_string("ERROR: DIVISION BY ZERO");
                        return NaN;
                    } 
                    numStack[top] = left / right; break;
                default: return 0;
            }
        }
        i++;
    }
    float result = numStack[top];
     // Reset the stack
    top = -1;
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = '\0';
    }
    return result;
}
