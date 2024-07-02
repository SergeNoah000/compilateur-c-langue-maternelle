%{
#include "exo17.tab.h"
%}

%%
[a-dA-D]    { 
                printf("Token: IDENTIFIER, Value: %c\n", yytext[0]); 
                yylval = yytext[0]; 
                return IDENTIFIER; 
             }
[0-9]+      { 
                printf("Token: NUMBER, Value: %s\n", yytext); 
                yylval = atoi(yytext); 
                return NUMBER; 
             }
"print"     { 
                printf("Token: PRINT\n"); 
                return PRINT; 
             }
[ \t\n]     { /* ignore whitespace */ }
"="         { 
                printf("Token: =\n"); 
                return '='; 
             }
";"         { 
                printf("Token: ;\n"); 
                return ';'; 
             }
.           { 
                printf("Token: %c\n", yytext[0]); 
                return yytext[0]; 
             }

%%

int yywrap(void) {
  return 1;
}
