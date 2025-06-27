%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *msg);
int yylex(void);

%}

%union {
    int num;
    char id;
    char *str;
}

%token <num> NUMBER
%token <id> IDENTIFIER
%token PRINT

%type <str> expr term factor

%start program

%%

program: statements
       ;

statements: statements statement
          | /* empty */
          ;

statement: IDENTIFIER '=' expr ';' {
                printf("mov [%c], eax\n%s\n", $1, $3);
                free($3);
            }
         | PRINT IDENTIFIER ';' {
                printf("mov eax, [%c]\nprint eax\n", $2);
            }
         ;

expr: expr '+' term {
            $$ = malloc(strlen($1) + strlen($3) + 20);
            sprintf($$, "%s\nmov ebx, %s\nadd eax, ebx", $1, $3);
            free($1);
            free($3);
        }
    | expr '-' term {
            $$ = malloc(strlen($1) + strlen($3) + 20);
            sprintf($$, "%s\nmov ebx, %s\nsub eax, ebx", $1, $3);
            free($1);
            free($3);
        }
    | term {
            $$ = $1;
        }
    ;

term: term '*' factor {
            $$ = malloc(strlen($1) + strlen($3) + 20);
            sprintf($$, "%s\nimul ebx, %s", $1, $3);
            free($1);
            free($3);
        }
    | term '/' factor {
            $$ = malloc(strlen($1) + strlen($3) + 20);
            sprintf($$, "%s\nmov edx, 0\nidiv %s", $1, $3);
            free($1);
            free($3);
        }
    | factor {
            $$ = $1;
        }
    ;

factor: NUMBER {
            $$ = malloc(20);
            sprintf($$, "mov eax, %d", $1);
        }
       | IDENTIFIER {
            $$ = malloc(20);
            sprintf($$, "mov eax, [%c]", $1);
        }
       | '(' expr ')' {
            $$ = $2;
        }
       ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int main(void) {
    printf("Enter commands:\n");
    yyparse();
    return 0;
}
