/*
 ============================================================================
 Name        : exo2.c
 Author      : Messi Nguélé Thomas
 Version     : 1.0
 Copyright   : Welcome, your are allowed to copy this code and reuse it as you want!
 Description : This code count the number of word that is in a file given as an input, word is also given as a parameter
 Usage       : ./exo1 input_file_name word
 ============================================================================
 */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define tailleMax 100


int main(int argc, char** argv)
{

int nbOc = 0, i = -1, j = 0;
int taille;

FILE* fdw = fopen(argv[1],"r");
char car, car_pre;
char* chaine = (char*)malloc(sizeof(char)*tailleMax);

chaine = argv[2]; 
taille = strlen(chaine);

printf("taille = %d\n",taille);

while(!feof(fdw)){
	fread(&car,1,1,fdw);
        
	if(car==chaine[0]){
		i = 0;
		j = 1;
		car_pre = chaine[i];
		printf("|");
	}else
	{
		if((car==chaine[j])&&(i == j-1)){
		//	if((car==chaine[j])&&(car_pre == chaine[i])){
        	        i= j;
               		j= j + 1;	
			car_pre = chaine[i];		
		}else
			i = -1;

	} 

		printf("%c",car);
		
	if(i == taille - 1)
	{
		nbOc = nbOc + 1;
		printf(">>");
			i = -1;
	}
	
	
}
fclose(fdw);
printf("Le nombre d'occurence est: %d\n",nbOc);

return 0;
}
/* Usage: ./exo2 ../lire.txt chaineAreconnaitre */
