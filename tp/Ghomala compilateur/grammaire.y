%{
#include<stdio.h>
#include "simple.h"
#define nbMax
int compteurSi = 0, compteurTest = 0, compteurWhile = 0;
FILE *yyout;

char *header="extern printf,scanf \nsection .data\n; declaration des variables en memoire\na:  dd  0\nb:  dd  0\nc:  dd  0\nd:  dd  0\ne:  dd  0\nf:  dd  0\ng:  dd  0\nh:  dd  0\ni:  dd  0\nj:  dd  0\nk:  dd  0\nl:  dd  0\nm:  dd  0\nn:  dd  0\no:  dd  0\np:  dd  0\nq:  dd  0\nr:  dd  0\ns:  dd  0\nt:  dd  0\nu:  dd  0\nv:  dd  0\nw:  dd  0\nx:  dd  0\ny:  dd  0\nz:  dd  0\nA:  dd  0\nB:  dd  0\nC:  dd  0\nD:  dd  0\nE:  dd  0\nF:  dd  0\nG:  dd  0\nH:  dd  0\nI:  dd  0\nJ:  dd  0\nK:  dd  0\nL:  dd  0\nM:  dd  0\nN:  dd  0\nO:  dd  0\nP:  dd  0\nQ:  dd  0\nR:  dd  0\nS:  dd  0\nT:  dd  0\nU:  dd  0\nV:  dd  0\nW:  dd  0\nX:  dd  0\nY:  dd  0\nZ:  dd  0\nfmt:db \"%d\", 10, 0 \nfmtlec:db \"%d\",0\nsection .text\nglobal _start\n\n_start:\n\n";

char *trailer="mov eax,1 ; sys_exit \nmov ebx,0; Exit with return code of 0 (no error)\nint 80h";
char *add=" ;addition\npop eax\npop ebx\nadd eax,ebx\npush eax\n\n";
char *mul=" ;multiplication\npop eax\npop ebx\nmul ebx\npush eax\n\n";
char *sub=" ;soustraction\npop eax\npop ebx\nsub ebx,eax\npush ebx\n\n"; 
char *div=" ;division\npop ebx\npop eax\nmov edx,0\ndiv ebx\npush eax\n\n";
char *mod=" ;modulo\npop ebx\npop eax\nmov edx,0\ndiv ebx\npush edx\n\n";
char *affec=" ;affectation\npop eax\nmov";
char *affecComp1=" ;affectation composee pour l'addition\npop eax\nadd eax,";
char *affecComp2=" ;affectation composee pour la soustraction\npop eax\nsub ";
char *affecComp3=" ;affectatiion composee pour la division(modulo)\npop ebx\nmov edx, 0\nmov eax,";
char *affecComp4=" ;affectation composee pour la multiplication\npop eax\nmov ebx,  ";
char *take=" ;recuperation en memoire\nmov eax,";
char *affec1=";affectation\n";
char *afficher1=";affiher\nmov eax,";
char *afficher2="\npush eax\npush dword fmt\ncall printf\n\n";
char *lire1=";lire\npush ";
char *lire2="\npush dword fmtlec\ncall scanf\n\n";
char *cmp = "pop ebx\npop eax\ncmp eax, ebx\n\n";
char *cmpEgal;
char *testGene;
char *cmpDifferent;
char *cmpSuperieur;
char *cmpInferieur;
char *tmp1,*tmp2;
int sinonVu = 0;

%}

%token INTEGER
%token PRINT
%token VARIABLE
%token SI
%token ALORS
%token SINON
%token FSI
%token FSIN
%token READ
%token WHILE
%token DONE
%token DO

%%
Program:
	program_body {printf(" Aucune erreur de syntaxe détectée \n");}

program_body:
	stat 
       | stat program_body

stat: 
      bloc
     |blocSi

bloc:
      instr ';'
     |instr ';' bloc


instr:

     | VARIABLE '=' E { fprintf(yyout,"%s [%c], eax\n\n",affec,$1); }
     | VARIABLE '+=' E { fprintf(yyout,"%s [%c]\nmov [%c], eax\n\n",affecComp1,$1,$1); }
     | VARIABLE '-=' E { fprintf(yyout,"%s [%c], eax\n\n",affecComp2,$1); }
     | VARIABLE '/=' E { fprintf(yyout,"%s [%c]\ndiv ebx\nmov [%c], eax\n\n",affecComp3,$1,$1); }
     | VARIABLE '%=' E { fprintf(yyout,"%s [%c]\ndiv ebx\nmov [%c], edx\n\n",affecComp3,$1,$1); }
     | VARIABLE '*=' E { fprintf(yyout,"%s [%c]\nmul ebx\nmov [%c], eax\n\n",affecComp4,$1,$1); }
     | PRINT VARIABLE {fprintf(yyout,"%s [%c] %s",afficher1,$2,afficher2);}
     | READ VARIABLE {fprintf(yyout,"%s %c %s",lire1,$2,lire2);}
     | VARIABLE '=' cond { fprintf(yyout,"%s [%c], eax\n\n",affec,$1); }





blocSi:
      SI cond alo  bloc finSi      
     |SI cond alo  bloc sino  bloc  finSi {fprintf(yyout,";Condition detectée 2\n");}

finSi:
      FSI{
	    if(sinonVu)
	    {
	      fprintf(yyout,"suite%d:\n",compteurSi);
	      fprintf(yyout,";Réduction du fsis%d\n",compteurSi);
	      sinonVu = 0;
	    }
	    else{
	      fprintf(yyout,"sinon%d:\n",compteurSi);
	      fprintf(yyout,";Réduction du fsi%d\n",compteurSi);
	    }
	      
	    
	 }


alo:
     ALORS{
	    compteurSi++;
	    fprintf(yyout,";Réduction du alors%d\n",compteurSi);
	    fprintf(yyout,"pop eax\ncmp eax,1\njne sinon%d\n",compteurSi);
	  }

sino:
     SINON{
	    fprintf(yyout,"jmp suite%d\nsinon%d:\n",compteurSi,compteurSi);
	    fprintf(yyout,";Réduction du sinon%d\n",compteurSi);
	    sinonVu = 1;
	  }
	  
      
cond:
     |'(' F '==' F ')' {
			compteurTest++;
			cmpEgal = ";Teste d'égalité\n";
			
			fprintf(yyout,"%s%sjne test%d\npush 1\njmp fintest%d \ntest%d:\npush 0\nfintest%d:\n\n\n",cmpEgal,cmp,compteurTest,compteurTest,compteurTest,compteurTest);
		      
		      }
		      
     |'(' F '!=' F ')' {
			compteurTest++;
			cmpDifferent=";Teste de différence\n";
			
			fprintf(yyout,"%s%sjne test%d\npush 0\njmp fintest%d \ntest%d:\npush 1\nfintest%d:\n\n\n",cmpDifferent,cmp,compteurTest,compteurTest,compteurTest,compteurTest);

		      }
		      
     |'(' F '<' F ')'  {
			compteurTest++;
                       cmpInferieur=";Teste d'infériorité\n";
			fprintf(yyout,"%s%sjge test%d\npush 1\njmp fintest%d \ntest%d:\npush 0\nfintest%d:\n\n\n",cmpInferieur,cmp,compteurTest,compteurTest,compteurTest,compteurTest);
		       	      
		      }
     |'(' F '>' F ')'  {
		       compteurTest++;
		       cmpSuperieur=";Teste de superiorité\n";
		       		       
		       fprintf(yyout,"%s%sjg test%d\npush 0\njmp fintest%d \ntest%d:\npush 1\nfintest%d:\n\n\n",cmpSuperieur,cmp,compteurTest,compteurTest,compteurTest,compteurTest);
		      }


E:
   T;
   | E '+' T { fprintf(yyout,"%s ",add); }
   | E '-' T { fprintf(yyout,"%s ", sub); }


T:
   F ;
   | T '*' F { fprintf(yyout,"%s ",mul); }
   | T '/' F { fprintf(yyout,"%s ",div); } 
   | T '%' F { fprintf(yyout,"%s ",mod); }

F:  
    INTEGER { fprintf(yyout,"push %d\n",$1);}
    | VARIABLE  { fprintf(yyout,"%s [%c] \npush eax\n",take,$1);}   
    | '(' E ')';

%%

int main(void)
{
 yyout=fopen("code_assembleur.asm","w");
 fprintf(yyout,"%s",header);
 
  
 yyparse();
  
 fprintf(yyout,"%s",trailer);
fclose(yyout);
 return 0;


}

int yyerror(char *str)
{
	printf("error parsing %s\n",str);
	return 0;
}
