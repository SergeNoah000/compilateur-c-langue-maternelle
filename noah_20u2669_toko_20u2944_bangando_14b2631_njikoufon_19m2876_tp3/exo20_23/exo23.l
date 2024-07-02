%{
#include "exo23.tab.h"
%}

%%
[ \t\n]+                 ;
"read"                   { return READ; }
"print"                  { return PRINT; }
"if"                     { return IF; }
"then"                   { return THEN; }
"fi"                     { return FI; }
"while"                  { return WHILE; }
"do"                     { return DO; }
"done"                   { return DONE; }
"="                      { return '='; }
"=="                     { return EQ; }
"!="                     { return NEQ; }
"<"                      { return LT; }
">"                      { return GT; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.strval = strdup(yytext); return ID; }
[0-9]+                   { yylval.intval = atoi(yytext); return NUMBER; }
.                        { return yytext[0]; }

%%
int yywrap() {
    return 1;
}
