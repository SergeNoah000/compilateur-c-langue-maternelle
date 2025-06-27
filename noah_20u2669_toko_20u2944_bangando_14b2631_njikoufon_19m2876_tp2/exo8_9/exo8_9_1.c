#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack* stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    return stack->data[stack->top--];
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

int evaluate_expression(const char* expression) {
    Stack operands;
    operands.top = -1;
    Stack operators;
    operators.top = -1;

    int i = 0;
    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            push(&operands, num);
        } else if (expression[i] == '+' || expression[i] == '*') {
            push(&operators, expression[i]);
            i++;
        } else {
            fprintf(stderr, "Syntax error: invalid character '%c'\n", expression[i]);
            exit(EXIT_FAILURE);
        }
    }

    while (!is_empty(&operators)) {
        int b = pop(&operands);
        int a = pop(&operands);
        char op = pop(&operators);

        if (op == '+') {
            push(&operands, a + b);
        } else if (op == '*') {
            push(&operands, a * b);
        }
    }

    return pop(&operands);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    int result = evaluate_expression(argv[1]);
    printf("Result: %d\n", result);

    return 0;
}
