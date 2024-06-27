#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    START,
    INTEGER,
    OPERATOR,
    ERROR,
    END
} State;

typedef enum {
    INT,
    OPER,
    NONE
} TokenType;

typedef struct {
    TokenType type;
    char value[3]; // Pour les entiers à 2 chiffres
} Token;

void printToken(Token token) {
    if (token.type == INT) {
        printf("<int:%s>", token.value);
    } else if (token.type == OPER) {
        printf("<operateur:%s>", token.value);
    }
}

Token getNextToken(const char **str) {
    Token token;
    token.type = NONE;
    State state = START;

    while (state != END && state != ERROR) {
        char c = **str;
        switch (state) {
            case START:
                if (isdigit(c)) {
                    state = INTEGER;
                    token.value[0] = c;
                    (*str)++;
                } else if (c == '+' || c == '*') {
                    state = OPERATOR;
                    token.value[0] = c;
                    token.value[1] = '\0';
                    (*str)++;
                } else if (c == '\0') {
                    state = END;
                } else {
                    state = ERROR;
                }
                break;

            case INTEGER:
                if (isdigit(c)) {
                    token.value[1] = c;
                    token.value[2] = '\0';
                    (*str)++;
                    token.type = INT;
                    state = END;
                } else {
                    state = ERROR;
                }
                break;

            case OPERATOR:
                token.type = OPER;
                state = END;
                break;

            case ERROR:
                token.type = NONE;
                break;

            case END:
                break;
        }
    }

    if (state == ERROR) {
        token.type = NONE;
    }

    return token;
}

void analyze(const char *expression) {
    const char *str = expression;
    Token token;

    do {
        token = getNextToken(&str);
        if (token.type == NONE) {
            printf("\nparse error\n");
            return;
        }
        printToken(token);
    } while (token.type != NONE);

    printf("\n");
}

int main() {
    const char *expression1 = "21+12*45";
    const char *expression2 = "1.2+12*45";

    printf("Analyzing: %s\n", expression1);
    analyze(expression1);

    printf("Analyzing: %s\n", expression2);
    analyze(expression2);

    return EXIT_SUCCESS;
}
