%{
#include "exo21.tab.h"
%}

%%

[0-9]+              { yylval = atoi(yytext); return NUMBER; }
"+"                 { return PLUS; }
"*"                 { return MULT; }
"("                 { return '('; }
")"                 { return ')'; }
[ \t\n]             ;  // Ignore whitespace
.                   { yyerror("Unknown character"); }

%%

int yywrap(void) { return 1; }
