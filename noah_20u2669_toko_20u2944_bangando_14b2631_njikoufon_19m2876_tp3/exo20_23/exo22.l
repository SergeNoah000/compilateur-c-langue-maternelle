%{
#include "exo22.tab.h"
%}

%%

[0-9]+              { yylval.num = atoi(yytext); return NUMBER; }
[a-z]               { yylval.id = yytext[0]; return IDENTIFIER; }
"="                 { return '='; }
";"                 { return ';'; }
"print"             { return PRINT; }
[ \t\n]             ;  // Ignore whitespace
.                   { yyerror("Unknown character"); }

%%

int yywrap(void) { return 1; }
