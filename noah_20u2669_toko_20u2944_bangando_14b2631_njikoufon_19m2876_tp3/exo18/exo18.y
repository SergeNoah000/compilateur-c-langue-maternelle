%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

int vars[4]; // Tableau pour stocker les valeurs des variables A, B, C, D
%}

%token NUMBER IDENTIFIER PRINT
%left '+' '-'
%left '*' '/'

%%

program:
    statements
    ;

statements:
    statements statement
  | /* vide */
  ;

statement:
    IDENTIFIER '=' expression ';' {
        int idx = $1 - 'A'; // Convertit 'A', 'B', 'C', 'D' en index 0, 1, 2, 3
        vars[idx] = $3;
//         printf("Assign: %c = %d\n", $1, $3);
    }
  | PRINT IDENTIFIER ';' {
        int idx = $2 - 'A';
        printf("%d\n",vars[idx]);
    }
  ;

expression:
    expression '+' expression { $$ = $1 + $3; }
  | expression '-' expression { $$ = $1 - $3; }
  | expression '*' expression { $$ = $1 * $3; }
  | expression '/' expression { $$ = $1 / $3; }
  | '(' expression ')'        { $$ = $2; }
  | NUMBER                    { $$ = $1; }
  | IDENTIFIER                { $$ = vars[$1 - 'A']; }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
//   printf("Enter commands:\n");
  yyparse();
  return 0;
}
