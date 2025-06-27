/*
 * exo14.lex
 *
 *  Created on: Dec 31, 2012
 *      Author: messi
 * Description: We build a pushdown automaton for parsing the arithmetical grammar
 * we use flex to do it.
 */

%{
/*code qui sera rajouté en haut du fichier généré*/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "utilitaire.h"
#define INTEGER 256

#define nbEtat   7
#define nbSymbT  4
#define nbSymbNT 1
#define tailleGr 3
#define shift    1
#define reduce   2
#define error    -1
#define accept   0
#define nbRefSft 4/*Nombre de reférence pour les actions shift, il vaut 4 parce ce qu'on a r1, r2, et r3 (il n'y a trois actions reduce possible)*/

int yylval;
int t_shift_reduce[nbEtat][nbSymbT];
int t_goto[nbEtat][nbSymbNT];
char* tabGramPDroite[tailleGr];
int tabGramPGauche[tailleGr];
%}

/* entier*/
entier [0-9]+

/*operateur*/
operateur  \+|\*
error .
%%
{entier} { yylval=atoi(yytext);return INTEGER;}
{operateur} {return *yytext;}
[\$] {return *yytext;}
{error} { yylval=*yytext ;return -1;}

[\n];


%%
int indice_symbole(int a, int typeToken)
{
  int indice_a = -1;
  
  if(typeToken == INTEGER)
  {
    /*Tous les entiers sont représentés par le symbole terminal i*/
    a = 'i';
  }
  
  switch(a)
  {
    case 'i':
	      indice_a = 0;
	      break;
    case '+':
	      indice_a = 1;
	      break;
    case '*':
	      indice_a = 2;
	      break;
    case '$':
	      indice_a = 3;
	      break;
    case 'E': /*Symbole non terminal*/
	      indice_a = 0;
	      break;
  }
  return indice_a;
}
/* code ajouté en bas du parseur*/
void init_t_shift_reduce(){
  int i, j;
  
  for(i=0; i<nbEtat; i++)
  {
    for(j=0; j<nbSymbT; j++)
    {
      t_shift_reduce[i][j] = error;
    }
  }
  
  t_shift_reduce[0][indice_symbole('i','i')]= nbRefSft + 2;
  
  t_shift_reduce[1][indice_symbole('+','+')]= nbRefSft + 3;
  t_shift_reduce[1][indice_symbole('*','*')]= nbRefSft + 4;
  t_shift_reduce[1][indice_symbole('$','$')]= accept;
  
  t_shift_reduce[2][indice_symbole('+','+')]= 3;
  t_shift_reduce[2][indice_symbole('*','*')]= 3;
  t_shift_reduce[2][indice_symbole('$','$')]= 3;
  
  t_shift_reduce[3][indice_symbole('i','i')]= nbRefSft + 2;
  
  t_shift_reduce[4][indice_symbole('i','i')]= nbRefSft + 2;
  
  t_shift_reduce[5][indice_symbole('+','+')]= nbRefSft + 3;
  t_shift_reduce[5][indice_symbole('*','*')]= nbRefSft + 4;
  t_shift_reduce[5][indice_symbole('$','$')]= 1;

  t_shift_reduce[6][indice_symbole('+','+')]= 2;
  t_shift_reduce[6][indice_symbole('*','*')]= 2;
  t_shift_reduce[6][indice_symbole('$','$')]= 2;
  
}

void init_t_goto(){
  int i, j, indice_E = indice_symbole('E','E');
  
  for(i=0; i<nbEtat; i++)
  {
    for(j=0; j<nbSymbNT; j++)
    {
      t_goto[i][j] = error;
    }
  }
  t_goto[0][indice_E] = 1;
  t_goto[3][indice_E] = 5;
  t_goto[4][indice_E] = 6;
}
void initTabGram()
{
  tabGramPGauche[0]='E';tabGramPDroite[0]="E+E";
  tabGramPGauche[1]='E';tabGramPDroite[1]="E*E";
  tabGramPGauche[2]='E';tabGramPDroite[2]="i";
}
void initTabAnalyse(){
  init_t_shift_reduce();
  init_t_goto();
  initTabGram();
}


void action(int etat_s, int indice_a, int result[])
{
  int temp = t_shift_reduce[etat_s][indice_a];
  
  
    if(temp==error|| temp == accept)
    {
      result[0] = temp;
    }
    else
	if(temp>=nbRefSft)/* S'agit -il d'un shift?*/
	{
	  result[0] = shift;
	  result[1] = temp - nbRefSft;
	}else
	     {
	      result[0] = reduce;
	      result[1] = temp;
	     } 
  
}

int successeur(int etat_s_p,int indice_a)
{
  return t_goto[etat_s_p][indice_a];
}

void analyseLR(File entree, File listeToken)
{
  
  Pile p;
  int act[2];/*act[0] signifie shift ou reduce et act[1] designe un etat si c'est shift et un numéro de règle si c'est reduce*/
  
  int symbole_a, indice_a, typeToken;/*Symbole d'entrée courant*/
  int etat_s, etat_s_p;	/*etat courant*/
  int taille_partieD, i, num_production;
  char A;
  
  initTabAnalyse();
  init_pile_vide(&p);
   
  empiler(&p,0);/* On empile 0, l'etat initial de l'automate*/
  
  
  while(1){
    symbole_a = tete_de_file(entree);
    typeToken = tete_de_file(listeToken);   
    indice_a = indice_symbole(symbole_a, typeToken);
    etat_s = tete_de_pile(p);
    
    action(etat_s, indice_a, act);
		    
    switch(act[0]){
    
	case shift:
		    empiler(&p,symbole_a);
		    empiler(&p,act[1]);
		    defiler(&entree);
		    defiler(&listeToken);
        printf("\n Shift state %d-->state %d",act[0],act[1]);
		    break;
	
	case reduce:
		    num_production = act[1] - 1;
		    taille_partieD = strlen(tabGramPDroite[num_production]);
		    
		    for(i = 0; i<taille_partieD*2; i++){
		      depiler(&p);
		    }
			
		    etat_s_p = tete_de_pile(p);
		    A = tabGramPGauche[num_production];
		    empiler(&p, A);
		    empiler(&p, successeur(etat_s_p,indice_symbole(A,A)));
		    
		    printf("\n Reduce %c-->%s",A,tabGramPDroite[num_production]);
		    break;
  case accept:
		    printf("\nAnalyse effectuée avec succès!!!!\n");
		    return;
		    break;
	
	case error:
		    printf("\nErreur\n");
		    return;
		    break;
	
    
    }
  
  }
  
  
  
  
}
int main(int argc, char **argv)
{
	int code;
	File entree;   /* pour obtenir la chaine après analyse lexicale*/
	File typeToken;/* on garde le type de lexème rencontré*/
	
	init_file_vide(&entree);
	init_file_vide(&typeToken);

/*Lecture des token à partir de lexpression en entrée */
	while((code = yylex())){
	  if(code == 256){
	    enfiler(&entree, yylval);
	    enfiler(&typeToken, code);
	    printf("%d\t",yylval);
	    
	  }else if(code==-1){
      printf("\n'%c' : Parse Error, unkown char\n",yylval); 
      return 1;
    } 
	  else
	  {
	    enfiler(&entree, code);
	    enfiler(&typeToken, code);
	    printf("%c\t",code);
	  }
	    
	}
	
	analyseLR(entree, typeToken);
	return 0;
}
/*compilation
flex -o exo7.lex.yy.c exo7.lex
gcc -pedantic -Wall -O2 exo7.lex.yy.c -o exo7 -lfl
utilisation : echo "12+4+56" | ./exo14
*/


