%{
/*This program build an interpreter for the language defined in the grammar section*/
#include<stdio.h>
#include "simple.h"
#include "utilitaire.h"
#define nbMax
int compteurSi = 0, compteurTest = 0, compteurWhile = 0;
//FILE *yyout;
int var[4];
Pile p;
int eax, ebx;

int take(int address)
{
  return var[address -'a'];
}
void affec(int address)
{
  int val = depiler(&p);
  var[address -'a'] = val;
}

void add()
{
  eax = depiler(&p);
  ebx = depiler(&p);
  
  empiler(&p, eax + ebx);
}

void mult()
{
  eax = depiler(&p);
  ebx = depiler(&p);
  
  empiler(&p,eax * ebx);
}

%}

%token INTEGER
%token PRINT
%token VARIABLE

%%
Program:
       stat {printf("\n\n\t\t Programme exécuté avec succès \n\n");}
       

stat: 
      bloc

bloc:
      instr ';'
     |instr ';' bloc


instr:

      VARIABLE '=' E {affec($1);}
     | PRINT VARIABLE {printf("\n%d", take($2));}


E:
   T
   | E '+' T {add();}


T:
   F 
   | T '*' F {mult(); }

F:  
    INTEGER {empiler(&p, $1);}
    | VARIABLE  {empiler(&p, take($1));}   

%%

int main(void)
{
   
 init_pile_vide(&p);
 
 yyparse();
  
 return 0;

}


int yyerror(char *str)
{
	printf("error parsing %s\n",str);
	return 0;
}
