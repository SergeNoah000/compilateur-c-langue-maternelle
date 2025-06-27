%{
#include<stdio.h>
#include "simple.h"

%}

entier [0-9]+
operateur \+|\*|\=|\;|\=\=|\!\=|\<|\>
parenthese \(|\)
variable a|b|c|d

%%
{entier} { yylval=atoi(yytext);return INTEGER;}
{operateur} {return *yytext;}
{variable}  {yylval=*yytext; return VARIABLE;}
print {return PRINT;}
[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n",yytext); }

%%

/*flex -o tp7.yy.c tp7.lex
gcc -pedantic -Wall -O2 tp7.yy.c -o tp7 -lfl
utilisation : echo "12+6*8" | ./tp7 */

