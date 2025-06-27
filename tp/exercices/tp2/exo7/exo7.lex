/*
 * exo7.lex
 *
 *  Created on: Dec 31, 2012
 *      Author: messi
 * Description: We do again exo4 but now using flex
 * Usage      : echo "12+4+56" | ./exo7
 */

%{
/*code qui sera rajouté en haut du fichier généré*/
#include<stdio.h>
%}

/* entier*/
entier [0-9]+
reel ([0-9]+)\.([0-9]+)

/*operateur*/
operateur  \+|\*|\-|\%|\/
/*error*/
error .

%%

{entier}     printf("<int:%s>",yytext);
{reel}     printf("<reel:%s>",yytext);
{operateur}  printf("<operateur:");ECHO; printf(">");
{error} printf("\n%s : Parse Error,You must enter an operator or a digit\n",yytext); return 1;
[\n];

%%
/* code ajouté en bas du parseur*/
int main(int argc, char **argv)
{
	printf("\n");
	yylex();
	printf("\n");
	return 0;
}
/*compilation
flex -o exo7.lex.yy.c exo7.lex
gcc -pedantic -Wall -O2 exo7.lex.yy.c -o exo7 -lfl
utilisation : echo "12+4+56" | ./exo7
*/


