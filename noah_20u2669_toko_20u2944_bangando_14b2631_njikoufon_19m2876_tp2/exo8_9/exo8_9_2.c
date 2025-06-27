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

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

void apply_operator(Stack* values, char op) {
    int b = pop(values);
    int a = pop(values);
    switch (op) {
        case '+': push(values, a + b); break;
        case '*': push(values, a * b); break;
        case '-': push(values, a - b); break;
        case '/': push(values, a / b); break;
    }
}

int evaluate_expression(const char* expression) {
    Stack values;
    values.top = -1;
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
            push(&values, num);
        } else if (expression[i] == '+' || expression[i] == '*' || expression[i] == '-' || expression[i] == '/') {
            while (!is_empty(&operators) && precedence(operators.data[operators.top]) >= precedence(expression[i])) {
                apply_operator(&values, pop(&operators));
            }
            push(&operators, expression[i]);
            i++;
        } else {
            fprintf(stderr, "Syntax error: invalid character '%c'\n", expression[i]);
            exit(EXIT_FAILURE);
        }
    }

    while (!is_empty(&operators)) {
        apply_operator(&values, pop(&operators));
    }

    return pop(&values);
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
