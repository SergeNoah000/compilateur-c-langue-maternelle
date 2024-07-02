// %{
// #include <stdio.h>
// #include <stdlib.h>
// %}
// 
// %token NUMBER PLUS MULT
// %left PLUS
// %left MULT
// %start program
// 
// %%
// 
// program: expr { /*printf("Compilation successful!\n");*/ }
//        ;
// 
// expr: expr PLUS term { printf("\tadd eax, %d\n", $3); }
//     | term { printf("\tmov eax, %d\n", $1); }
//     ;
// 
// term: term MULT factor { printf("\tmul ebx\n"); }
//     | factor { printf("\tmov ebx, %d\n", $1); }
//     ;
// 
// factor: NUMBER { $$ = $1; }
//        | '(' expr ')' { $$ = $2; }
//        ;
// 
// %%
// 
// int yywrap(void) { return 1; }
// 
// int main(void) {
//     printf("section .data\n\tresult db 0\n\nsection .text\n\tglobal _start\n_start:\n");
//     yyparse();
//     printf("\tmov [result], eax\n\tmov eax, 1\n\txor ebx, ebx\n\tint 0x80\n");
// 
//     return 0;
// }
// 
// void yyerror(const char *msg) {
//     fprintf(stderr, "Error: %s\n", msg);
//     exit(1);
// }


%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER PLUS MULT
%left PLUS
%left MULT
%start program

%%

program: expr { 
            printf("\t; Store result in memory\n");
            printf("\tmov [result], eax\n");
            printf("\t; Print result\n");
            printf("\tmov eax, 4\n");
            printf("\tmov ebx, 1\n");
            printf("\tmov ecx, result\n");
            printf("\tmov edx, 1\n");
            printf("\tint 0x80\n");
            printf("\t; Exit program\n");
            printf("\tmov eax, 1\n");
            printf("\txor ebx, ebx\n");
            printf("\tint 0x80\n");
        }
       ;

expr: expr PLUS term { printf("\tadd eax, %d\n", $3); }
    | term { printf("\tmov eax, %d\n", $1); }
    ;

term: term MULT factor { printf("\tmul ebx\n"); }
    | factor { printf("\tmov ebx, %d\n", $1); }
    ;

factor: NUMBER { $$ = $1; }
       | '(' expr ')' { $$ = $2; }
       ;

%%

// int yywrap(void) { return 1; }

int main(void) {
    printf("section .data\n\tresult db 0\n\nsection .text\n\tglobal _start\n_start:\n");
    yyparse();
    return 0;
}

void yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}
