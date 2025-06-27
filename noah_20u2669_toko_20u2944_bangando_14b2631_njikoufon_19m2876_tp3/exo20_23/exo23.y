%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex();
int reg = 0;
%}

%union {
    int intval;
    char *strval;
}

%token <intval> NUMBER
%token <strval> ID
%token READ PRINT IF THEN FI WHILE DO DONE EQ NEQ LT GT

%type <intval> expression condition
%type <strval> statement statements

%start program

%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    READ ID {
        printf("mov eax, 3\n");
        printf("mov ebx, 0\n");
        printf("mov ecx, %s\n", $2);
        printf("mov edx, 1\n");
        printf("int 0x80h\n");
    }
    | PRINT expression {
        printf("mov eax, %%d\n", $2);
        printf("call print_int\n");
    }
    | ID '=' expression {
        printf("mov [%s], %%d\n", $1, $3);
    }
    | IF condition THEN statements FI {
        printf("cmp %%d, 0\n", $2);
        printf("je endif_%%d\n", reg);
        printf("%s\n", $4);
        printf("endif_%%d:\n", reg++);
    }
    | WHILE condition DO statements DONE {
        printf("startwhile_%%d:\n", reg);
        printf("cmp %%d, 0\n", $2);
        printf("je endwhile_%%d\n", reg);
        printf("%s\n", $4);
        printf("jmp startwhile_%%d\n", reg);
        printf("endwhile_%%d:\n", reg++);
    }
    ;

expression:
    NUMBER {
        $$ = $1;
    }
    | ID {
        printf("mov eax, [%s]\n", $1);
        $$ = reg++;
    }
    | expression '+' expression {
        printf("mov eax, %%d\n", $1);
        printf("add eax, %%d\n", $3);
        $$ = reg++;
    }
    | expression '*' expression {
        printf("mov eax, %%d\n", $1);
        printf("imul eax, %%d\n", $3);
        $$ = reg++;
    }
    ;

condition:
    expression EQ expression {
        printf("cmp %%d, %%d\n", $1, $3);
        printf("sete al\n");
        printf("movzx eax, al\n");
        $$ = reg++;
    }
    | expression NEQ expression {
        printf("cmp %%d, %%d\n", $1, $3);
        printf("setne al\n");
        printf("movzx eax, al\n");
        $$ = reg++;
    }
    | expression LT expression {
        printf("cmp %%d, %%d\n", $1, $3);
        printf("setl al\n");
        printf("movzx eax, al\n");
        $$ = reg++;
    }
    | expression GT expression {
        printf("cmp %%d, %%d\n", $1, $3);
        printf("setg al\n");
        printf("movzx eax, al\n");
        $$ = reg++;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}
