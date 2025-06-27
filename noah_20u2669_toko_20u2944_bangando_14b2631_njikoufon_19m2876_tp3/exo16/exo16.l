%{
#include "exo16.tab.h"
%}

%%

[0-9]+      { 
            
                yylval = atoi(yytext); 
                return NUMBER; 
             }
[ \t\n]     { /* ignore whitespace */ }
.           { 
                
                return yytext[0]; 
             }

%%

int yywrap(void) {
  return 1;
}
