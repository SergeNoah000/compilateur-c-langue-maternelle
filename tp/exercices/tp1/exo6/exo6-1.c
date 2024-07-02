/*
 * exo6-1.c
 *
 *  Created on: Dec 26, 2012
 *      Author: messi
 *  this exercise builds an automaton who recognizes this regex: ^if.*n$
 *	usage: ./exo6-1 file_name (/etc/bash.bashrc for example)
 */

#include <stdio.h>
#define etat_initial 0
#define etat_1 1
#define etat_2 2
#define etat_3 3
#define etat_final 4
#define etat_puit 5

typedef int Etat;

int main(int argc, char **argv) {
	FILE* fdw = fopen(argv[1],"r");
	char car;
	Etat q = etat_initial;
	int nboc = 0;

	while(!feof(fdw)){
			fread(&car,1,1,fdw);

			switch(car){
				case 'i': if(q==etat_initial){
							 q = etat_1;
						   }
						   else
							   if(q==etat_2||q==etat_3||q==etat_final)
							       q = etat_3;
							   else
							   q = etat_puit;

						   break;

				case 'f': if(q==etat_1)
								q = etat_2;
						   else
							   if(q==etat_2||q==etat_3||q==etat_final)
							   		q = etat_3;
							   else
								   	q = etat_puit;
						   break;

				case 'n': if(q==etat_3||q==etat_final)
								q = etat_final;
						   else
							   if(q==etat_2)
							   	q = etat_3;
							   else
							    q = etat_puit;
						   break;

				case '\n':
						   if(q==etat_final)
						   {
                             nboc++;

						   }
						   q = etat_initial;
						   break;

				default:
						   if(q==etat_2||q==etat_3||q==etat_final)
							   q = etat_3;
						   else
							   q = etat_puit;
						   break;
			}


	}
	fclose(fdw);
		printf("Le nombre d'occurence est: %d\n",nboc);

		return 0;
}


