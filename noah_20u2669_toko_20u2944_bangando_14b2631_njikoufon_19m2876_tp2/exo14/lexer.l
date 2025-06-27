%{
#include "y.tab.h"
%}

%%
"+"     { return PLUS; }
"*"     { return MUL; }
"("     { return LPAREN; }
")"     { return RPAREN; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\n      { return 0; }
[ \t]   { /* ignore whitespace */ }
.       { printf("Unexpected character: %s\n", yytext); return 0; }
%%

int yywrap() {
    return 1;
}
