%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
%}

DIGIT   [0-9]
NUMBER  {DIGIT}{DIGIT}      

%%

{NUMBER}                { printf("<int:%s>", yytext); }
[+*-]                    { printf("<operateur:%s>", yytext); }
\n                      { /* ignore newlines */ }
[ \t]                   { /* ignore whitespace */ }
.                       { yyerror("parse error"); }

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int main() {
    yylex();
    return 0;
}
