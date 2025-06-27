%{
/*The execution of this program show  us well what contain $i(the rigth side of grammar prodction $1 is the first, $2 the second and so on) and $$ (the top of bison stack). We can also identify the reduce rule on which we will introduce semantic action if we want to evaluate expression*/
#include<stdio.h>
#include "simple.h"
#define nbMax
%}
%token INTEGER

%%
S:
  E	{printf("\n Réduction S ----> E    Fin!!!\n"); }

E:
  E '+' T {printf("\n Réduction E ----> E + T    $1=%d\t $2=%d \t $3=%d \t $$=%d",$1,$2,$3,$$); }
 |T	  {printf("\n Réduction E ----> T        $1=%d\t$$=%d",$1,$$); }

T:
  T '*' F {printf("\n Réduction T ----> T * F    $1=%d\t $2=%d \t $3=%d \t $$=%d",$1,$2,$3,$$); }
 |F       {printf("\n Réduction T ----> F        $1=%d\t$$=%d",$1,$$); }
 
F:
  INTEGER {printf("\n Réduction F ----> int      $1=%d\t$$=%d",$1,$$); }

%%

int main(void)
{
  
 yyparse();
  
 return 0;
 
}
int yyerror(char *str)
{
	printf("error parsing %s\n",str);
	return 0;
}
