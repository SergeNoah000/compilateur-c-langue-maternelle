/*
 * exo8_9.c
 *
 *  Created on: Jan 1, 2013
 *      Author: messi
 * In this exercice, we do left-right evaluation with and without operator priority
 * using respectively functions exp_post_fixe_avec_prio and exp_post_fixe_sans_prio
 * usage: ./exo8_9 ../../tp1/exo4/test.txt
 */

#include <stdio.h>
#include "utilitaire.h"

#define etat_initial 0
#define etat_nombre 1
#define etat_operateur 2
#define etat_final 3

typedef int Etat;
char*yytext;
Noeud * exp_arith;

void afficher(int valeur, Etat q_courant){
	if(q_courant == etat_nombre)
		printf("<int:%d>",valeur);
	if(q_courant == etat_operateur)
		printf("<oper:%c>",valeur);
	insert_queue(&exp_arith, valeur);
}

int est_operateur(int car){
	int bool = 0;
	if(car=='+'||car=='*')
		bool = 1;
	return bool;
}
void exp_post_fixe_sans_prio(Noeud* exp, File* sortie)
{
	Pile p; Noeud*l = exp;
	int val;
	init_file_vide(sortie);
	init_pile_vide(&p);

	while(exp!=0){
       if(!est_operateur(exp->info))
       {
    	   enfiler(sortie, exp->info);
       }
       else
       {
    	   if(!pile_est_vide(p))
    	   {
    		   val = depiler(&p);
    		   enfiler(sortie,val);
    	   }

    	   empiler(&p, exp->info);
       }
       exp = exp->suivant;
	}
	if(!pile_est_vide(p))
    {
	   val = depiler(&p);
	   enfiler(sortie,val);
    }
}
int priorite_operateur(int operateur)
{
	int priorite = -1;

	switch(operateur){
	case '+':priorite = 0;
			  break;
	case '*':priorite = 1;
			  break;
	}

	return priorite;
}
/*
 * Shunting-yard algorithm
 */
void exp_post_fixe_avec_prio(Noeud* exp, File* sortie)
{
	Pile p; Noeud*l = exp;
	int val;
	init_file_vide(sortie);
	init_pile_vide(&p);

	while(exp!=0){
       if(!est_operateur(exp->info))
       {
    	   enfiler(sortie, exp->info);
       }
       else
       {
    	   while(!pile_est_vide(p) && (priorite_operateur(tete_de_pile(p))>priorite_operateur(exp->info)))
    	   {
    		   val = depiler(&p);
    		   enfiler(sortie,val);
    	   }

    	   empiler(&p, exp->info);
       }
       exp = exp->suivant;
	}
	while(!pile_est_vide(p))
    {
	   val = depiler(&p);
	   enfiler(sortie,val);
    }
}
int calcul(int operateur, int operande_1, int operande_2)
{
	switch(operateur){
		case'+': return operande_1 + operande_2;
		case'*': return operande_1 * operande_2;
	}
}

int evaluation_gauche_droite(File exp_post_fixe)
{
	Pile p;
	int val, operateur, operande_1, operande_2, resultat;
	while(!file_est_vide(exp_post_fixe)){
		val = defiler(&exp_post_fixe);
		if(!est_operateur(val)){
			empiler(&p,val);
		}else
		{
			operande_1 = depiler(&p);
			operande_2 = depiler(&p);
			operateur = val;
			resultat = calcul(operateur,operande_1,operande_2);
			empiler(&p, resultat);
		}
	}
	resultat = depiler(&p);
	return resultat;
}

int analyse_lexicale(FILE* fdw)
{
	int nbOc = 0, i = 0, j = 0, state = -1, nbr=0,nbr1;
	int init = 0;
	Etat q = etat_initial, q_precedent = etat_initial;


	char car,tmp;
	printf("\n");

	while(!feof(fdw)){
		fread(&car,1,1,fdw);

		switch(car)
		{
		   	case '0':
		   	case '1':
		   	case '2':
		   	case '3':
		   	case '4':
		   	case '5':
		   	case '6':
		   	case '7':
		   	case '8':
		   	case '9':
		   			  q = etat_nombre;
		              nbr = nbr*10 + (car-'0');
	                  break;

		   	case '+':

		   	case '*':

					if(q==etat_nombre){
						afficher(nbr,q);
						nbr = 0;
					}

					q = etat_operateur;
					afficher(car,q);
				    break;
		   	case '\n':
		   				break;

			default:
				printf("\n%c : Parse Error, unkown char\n",car);
				return 1;
		}
	}
	fclose(fdw);

	if(q==etat_nombre)
		afficher(nbr,q);
	printf("\n\n");
	return 0;
}

int main(int argc, char** argv)
{
int resultat1, resultat2;
FILE* fdw = fopen(argv[1],"r");
File sortie;

int val_anal = analyse_lexicale(fdw);
exp_post_fixe_sans_prio(exp_arith, &sortie);
resultat1 = evaluation_gauche_droite(sortie);

exp_post_fixe_avec_prio(exp_arith, &sortie);
resultat2 = evaluation_gauche_droite(sortie);

printf("Avec priorité: %d\t Sans priorité:%d\n",resultat2,resultat1);
/*if(val_anal == 0)*/


return 0;
}





