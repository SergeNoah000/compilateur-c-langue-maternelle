/*
 ============================================================================
 Name        : exo3-1.c, created on: Dec 23, 2012
 Author      : Messi Nguélé Thomas
 Version     : 1.0
 Copyright   : Welcome, your are allowed to copy this code and reuse it as you want!
 Description : This program  rewrite exo2 in C but now using an automaton , Ansi-style
Usage	     : ./exo3-2 file_name word
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tailleMax 100
#define etat_initial 0
#define etat_intermediare 1
#define etat_final 2

typedef int Etat;


int main(int argc, char** argv)
{

	int nbOc = 0, i = 0;
	int taille;

	FILE* fdw = fopen(argv[1],"r");
	char car;
	char* chaine = (char*)malloc(sizeof(char)*tailleMax);/*Chaine dont les occurences sont comptées.*/
    Etat q = etat_initial;

	chaine = argv[2];
	taille = strlen(chaine);

	while(!feof(fdw)){
		fread(&car,1,1,fdw);

		if(car==chaine[0]){
			q = etat_intermediare;
			printf("|");
		}

		if((car==chaine[i])&&(q==etat_intermediare)){
			if(i==taille-1){
				q=etat_final;
			}
			else
				i++;
		}
		else
		{
			i = 0;
		        q = etat_initial;
		}

		printf("%c",car);
		if(q == etat_final )
		{
			nbOc = nbOc + 1;
			printf(">>");
			i = 0;
			q = etat_initial;
		}


	}
	fclose(fdw);
	printf("Le nombre d'occurence est: %d\n",nbOc);

	return 0;
}
