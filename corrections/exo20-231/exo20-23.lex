%{
#include<stdio.h>
#include "simple.h"
extern FILE *yyout;

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
lepele {return PRINT;}
yi {return SI;}
lo {return ALORS;}
ngueba {return SINON;}
lezoko {return FSI;}
leton {return READ;}
ngue {return WHILE;}
leghu {return DO;}
lemak {return DONE;}
te {return FOR;}  /* Ajout de l'instruction for */
[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n",yytext); }

%%

/*flex -o exo20-23.yy.c exo20-23.lex
gcc -pedantic -Wall -O2 exo20-23.yy.c -o exo20-23 -lfl
utilisation : echo "12+6*8" | ./exo20-23 */
