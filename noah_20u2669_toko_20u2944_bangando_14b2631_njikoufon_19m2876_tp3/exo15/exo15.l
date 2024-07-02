%{
#include "exo15.tab.h"
%}

%%

[0-9]+      { 
                printf("Token: NUMBER, Value: %s\n", yytext); 
                yylval = atoi(yytext); 
                return NUMBER; 
             }
[ \t\n]     { /* ignore whitespace */ }
.           { 
                printf("Token: %c\n", yytext[0]); 
                return yytext[0]; 
             }

%%

int yywrap(void) {
  return 1;
}