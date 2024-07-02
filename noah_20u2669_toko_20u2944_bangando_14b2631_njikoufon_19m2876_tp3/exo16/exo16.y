%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
int result; // Variable globale pour stocker le résultat final
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%

expression:
    expression '+' expression {  $$ = $1 + $3; result = $$; }
  | expression '-' expression {  $$ = $1 - $3; result = $$; }
  | expression '*' expression {  $$ = $1 * $3; result = $$; }
  | expression '/' expression {  $$ = $1 / $3; result = $$; }
  | '(' expression ')'        { $$ = $2; result = $$; }
  | NUMBER                    { $$ = $1; result = $$; }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
  
  yyparse();
  printf("Result: %d\n", result); // Affiche le résultat final
  return 0;
}
