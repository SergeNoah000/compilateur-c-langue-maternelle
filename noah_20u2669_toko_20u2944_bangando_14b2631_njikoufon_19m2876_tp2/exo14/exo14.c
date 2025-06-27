#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int state;
    char symbol;
} StackItem;

typedef struct {
    StackItem items[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack *stack, int state, char symbol) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->top++;
        stack->items[stack->top].state = state;
        stack->items[stack->top].symbol = symbol;
    } else {
        printf("Stack overflow\n");
    }
}

StackItem pop(Stack *stack) {
    StackItem item = {0, '\0'};
    if (stack->top >= 0) {
        item = stack->items[stack->top];
        stack->top--;
    } else {
        printf("Stack underflow\n");
    }
    return item;
}

StackItem peek(Stack *stack) {
    StackItem item = {0, '\0'};
    if (stack->top >= 0) {
        item = stack->items[stack->top];
    }
    return item;
}

int is_terminal(char symbol) {
    return (symbol == 'i' || symbol == '+' || symbol == '*' || symbol == '$');
}

int parse(char *input) {
    Stack stack;
    stack.top = -1;
    push(&stack, 0, '$');

    char *lexeme = input;
    int accepted = 0;

    while (!accepted) {
        StackItem top = peek(&stack);
        char current = *lexeme;

        printf("Stack: ");
        for (int i = 0; i <= stack.top; i++) {
            printf("%c ", stack.items[i].symbol);
        }
        printf("\nInput: %s\n", lexeme);

        switch (top.state) {
            case 0:
                if (current == 'i') {
                    push(&stack, 4, 'i');
                    lexeme++;
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 1:
                if (current == '+') {
                    push(&stack, 2, '+');
                    lexeme++;
                } else if (

current == '*') {
                    push(&stack, 3, '*');
                    lexeme++;
                } else if (current == '$') {
                    printf("Accepted\n");
                    accepted = 1;
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 2:
                if (current == 'i') {
                    push(&stack, 4, 'i');
                    lexeme++;
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 3:
                if (current == 'i') {
                    push(&stack, 4, 'i');
                    lexeme++;
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 4:
                // Reduce by E -> int
                pop(&stack);
                top = peek(&stack);
                if (top.state == 0) {
                    push(&stack, 1, 'E');
                } else if (top.state == 2) {
                    push(&stack, 5, 'E');
                } else if (top.state == 3) {
                    push(&stack, 6, 'E');
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 5:
                if (current == '+') {
                    push(&stack, 2, '+');
                    lexeme++;
                } else if (current == '*') {
                    push(&stack, 3, '*');
                    lexeme++;
                } else if (current == '$') {
                    // Reduce by E -> E + E
                    pop(&stack); // E
                    pop(&stack); // +
                    pop(&stack); // E
                    top = peek(&stack);
                    if (top.state == 0) {
                        push(&stack, 1, 'E');
                    } else if (top.state == 2) {
                        push(&stack, 5, 'E');
                    } else if (top.state == 3) {
                        push(&stack, 6, 'E');
                    } else {
                        printf("Syntax error\n");
                        return 0;
                    }
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            case 6:
                if (current == '+') {
                    push(&stack, 2, '+');
                    lexeme++;
                } else if (current == '*') {
                    push(&stack, 3, '*');
                    lexeme++;
                } else if (current == '$') {
                    // Reduce by E -> E * E
                    pop(&stack); // E
                    pop(&stack); // *
                    pop(&stack); // E
                    top = peek(&stack);
                    if (top.state == 0) {
                        push(&stack, 1, 'E');
                    } else if (top.state == 2) {
                        push(&stack, 5, 'E');
                    } else if (top.state == 3) {
                        push(&stack, 6, 'E');
                    } else {
                        printf("Syntax error\n");
                        return 0;
                    }
                } else {
                    printf("Syntax error\n");
                    return 0;
                }
                break;
            default:
                printf("Syntax error\n");
                return 0;
        }
    }

    return 1;
}

int main() {
    char input[] = "i+i*i$";
    if (parse(input)) {
        printf("The input is valid.\n");
    } else {
        printf("The input is invalid.\n");
    }
    return 0;
}

