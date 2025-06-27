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
  
  printf("\tdans add : eax=%d ebx=%d prod=%d ",eax,ebx,eax + ebx);
}

void mult()
{
  eax = depiler(&p);
  ebx = depiler(&p);
  
  empiler(&p,eax * ebx);
  
  printf("\tdans mult: eax=%d ebx=%d prod=%d ",eax,ebx,eax * ebx);
}

%}

%token INTEGER
%token PRINT
%token VARIABLE

%%
Program:
       stat {printf("\n\n\t\t OK pourla syntaxe \n\n");}
       

stat: 
      bloc

bloc:
      instr ';'
     |instr ';' bloc


instr:

      VARIABLE '=' E {affec($1); printf("\nRéduction instr ---> var = E ");}
     | PRINT VARIABLE {printf("\nRéduction instr ---> print: %d", take($2));}


E:
   T{printf("\nRéduction E ----> T    $$=%d",$$); }
   | E '+' T {add(); printf("\nRéduction E ----> E + T    "); }


T:
   F 
   | T '*' F {mult(); printf("\nRéduction T ----> T * F    "); }

F:  
    INTEGER {empiler(&p, $1);printf("\nRéduction F ----> int"); }
    | VARIABLE  {empiler(&p, take($1)); printf("\nRéduction F ----> var");}   

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
