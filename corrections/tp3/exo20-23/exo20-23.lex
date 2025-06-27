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
{parenthese} {return *yytext;}
{variable}  {yylval=*yytext; return VARIABLE;}
print {return PRINT;}
if {return SI;}
then {return ALORS;}
else {return SINON;}
fi {return FSI;}
read {return READ;}
while {return WHILE;}
do {return DO;}
done {return DONE;}
[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n",yytext); }

%%

/*flex -o tp7.yy.c tp7.lex
gcc -pedantic -Wall -O2 tp7.yy.c -o tp7 -lfl
utilisation : echo "12+6*8" | ./tp7 */

