/*
 ============================================================================
 Name        : exo3-1.c
 Author      : Messi Nguélé Thomas
 Version     : 1.0
 Copyright   : Welcome, your are allowed to copy this code and reuse it as you want!
 Description : This program  rewrite exo1 in C but now using an automaton , Ansi-style
 Usage        : ./exo3-2 file_name
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define etat_initial 0
#define etat_1 1     /* Etat dans lequel on sera après avoir lu m*/
#define etat_2 2     /* Etat dans lequel on sera après avoir lu u*/
#define etat_final 3 /* Etat dans lequel on sera après avoir lu r*/

typedef int Etat;

int main(int argc, char** argv) {
	int nbOc = 0;
	char car;
	Etat q = etat_initial;

	FILE* fdw = fopen(argv[1],"r");

	while(!feof(fdw)){
		fread(&car,1,1,fdw);

		switch(car){
			case 'm': q = etat_1;
					   break;

			case 'u': if(q==etat_1)
							q = etat_2;
					   else
						    q = etat_initial;
			           break;

			case 'r': if(q==etat_2)
							q = etat_final;
					   else
						   q = etat_initial;
					   break;
			default:
					   q = etat_initial;
					   break;
		}

		if(q==etat_final){
			nbOc = nbOc + 1;
			q = etat_initial;
		}
	}


	fclose(fdw);
	printf("Le nombre d'occurence est: %d\n",nbOc);

	return 0;
}
