%{
#include <stdio.h>
#include "simple.h"
%}

entier [0-9]+
operateur \+|\*|\=|\;|\=\=|\!\=|\<|\>
parenthese \(|\)
variable [a-z]

%%
{entier}      { yylval=atoi(yytext); return INTEGER; }
{operateur}   { return *yytext; }
{parenthese}  { return *yytext; }
{variable}    { yylval=*yytext; return VARIABLE; }
print         { return PRINT; }
if            { return SI; }
then          { return ALORS; }
else          { return SINON; }
fi            { return FSI; }
read          { return READ; }
while         { return WHILE; }
do            { return DO; }
done          { return DONE; }
for           { return FOR; }
to            { return TO; }
[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n", yytext); }

%%
