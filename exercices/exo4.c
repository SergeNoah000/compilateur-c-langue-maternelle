#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    INT,
    OPERATOR,
    ERROR,
    END
} TokenType;

typedef struct {
    TokenType type;
    char value[3]; // As integers are 2 characters long plus a null terminator
} Token;

Token getNextToken(const char **str) {
    Token token;
    while (isspace(**str)) {
        (*str)++;
    }

    if (isdigit(**str)) {
        // Expecting two digits integer
        if (isdigit(*(*str + 1))) {
            token.type = INT;
            token.value[0] = **str;
            token.value[1] = *(*str + 1);
            token.value[2] = '\0';
            *str += 2;
        } else {
            token.type = ERROR;
        }
    } else if (**str == '+' || **str == '*') {
        token.type = OPERATOR;
        token.value[0] = **str;
        token.value[1] = '\0';
        (*str)++;
    } else if (**str == '\0') {
        token.type = END;
    } else {
        token.type = ERROR;
    }

    return token;
}

void analyze(const char *expression) {
    const char *str = expression;
    Token token;
    do {
        token = getNextToken(&str);
        switch (token.type) {
            case INT:
                printf("<int:%s>", token.value);
                break;
            case OPERATOR:
                printf("<operateur:%s>", token.value);
                break;
            case ERROR:
                printf("\nparse error\n");
                return;
            case END:
                break;
        }
    } while (token.type != END);
    printf("\n");
}

int main() {
    const char *expression1 = "21+12*45";
    const char *expression2 = "1.2+12*45";
    const char *expression3 = "11+23*78+12*45";

    printf("Analyzing: %s\n", expression1);
    analyze(expression1);

    printf("Analyzing: %s\n", expression2);
    analyze(expression2);

    printf("Analyzing: %s\n", expression3);
    analyze(expression3);

    return EXIT_SUCCESS;
}
