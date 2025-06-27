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

[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n",yytext); }

%%

/*flex -o tp7.yy.c tp7.lex
gcc -pedantic -Wall -O2 exo15.yy.c -o exo15 -lfl
utilisation : echo "12+6*8" | ./exo15 */

