/*
 * main.c
 *
 *  Created on: Dec 30, 2012
 *      Author: messi
 */

#include "utilitaire.h"
#include "stdio.h"

int main(int argc, char **argv)
{
    File p;
	init_file_vide(&p);
	printf("La taille de la file est: %d\n",p.taille);
	enfiler(&p,1);
	printf("La taille de la file est: %d\n",p.taille);
	affiche(p.liste);
	enfiler(&p,2);
	printf("La taille de la file est: %d\n",p.taille);
	affiche(p.liste);
	enfiler(&p,3);
	printf("La taille de la file est: %d\n",p.taille);
	affiche(p.liste);
	defiler(&p);
	affiche(p.liste);
	defiler(&p);
    affiche(p.liste);
	return 0;
}




