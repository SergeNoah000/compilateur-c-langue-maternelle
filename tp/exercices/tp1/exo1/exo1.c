/*
 ============================================================================
 Name        : exo1.c
 Author      : Messi Nguélé Thomas
 Version     : 1.0
 Copyright   : Welcome, your are allowed to copy this code and reuse it as you want!
 Description : This code count the number of "mur" that is in a file given as an input
 Usage       : ./exo1 input_file_name
 ============================================================================
 */

#include<stdio.h>

int main(int argc, char** argv)
{

int nbOc = 0, i = -1;

FILE* fdw = fopen(argv[1],"r");
char car;

while(!feof(fdw)){
	fread(&car,1,1,fdw);
	if(car == 'm' || car == 'u' || car == 'r')
	{
		if(car=='m')
		   i = 0;
		if((car=='u')&&(i==0))
			i = 1;
		if((car=='r')&&(i==1))
			i=2;
		if(i==2){
			nbOc = nbOc + 1;
			i = -1;
		}
	}
	else
		i = -1;	    
}


fclose(fdw);
printf("Le nombre d'occurence est: %d\n",nbOc);

return 0;
}
