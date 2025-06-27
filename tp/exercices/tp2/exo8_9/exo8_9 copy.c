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
#include <stdlib.h>
#include "utilitaire.h"
#include <math.h>
#define etat_initial 0
#define etat_entier_positif 1
#define etat_entier_negatif 2
#define etat_reel_positif 3
#define etat_reel_negatif 4
#define etat_operateur 5
#define etat_puit 6
#define etat_par_ouvr 7
#define etat_par_ferm 8
#define etat_signe_pos 9
#define etat_signe_neg 10

typedef int Etat;
char *yytext;
Noeud *exp_arith;

void afficher(float valeur, Etat q_courant)
{
	if (q_courant == etat_entier_negatif || q_courant == etat_entier_positif){
		printf("<int:%d>", (int)valeur);
		insert_queue(&exp_arith, (int)valeur );
	}
		
	if (q_courant == etat_operateur){
		printf("<oper:%c>", (int)valeur);
		c_insert_queue(&exp_arith, (char)valeur );
	}
		
	if (q_courant == etat_par_ouvr || q_courant == etat_par_ferm){
		printf("<paren:%c>", (char)valeur);
		c_insert_queue(&exp_arith, (char)valeur );
	}
	if (q_courant == etat_reel_negatif || q_courant == etat_reel_positif){
		printf("<reel:%f>", valeur);
		f_insert_queue(&exp_arith, valeur );
	}
		
		//printf("%d\n",(int)valeur);
	//insert_queue(&exp_arith, valeur );
	//affiche(exp_arith);
}

int est_operateur(int car)
{
	int bool = 0;
	if (car == '+' || car == '*' || car == '%' || car == '/' || car == '-')
		bool = 1;
	return bool;
}

void exp_post_fixe_sans_prio(Noeud *exp, File *sortie)
{
	Pile p;
	Noeud *l = exp;
	int val;
	init_file_vide(sortie);
	init_pile_vide(&p);

	while (exp != 0)
	{
		if (!(exp->type==OPER))
		{
			enfiler(sortie, exp->info);
		}
		else
		{
			if (!pile_est_vide(p))
			{
				val = depiler(&p);
				enfiler(sortie, val);
			}

			empiler(&p, exp->info);
		}
		exp = exp->suivant;
	}
	if (!pile_est_vide(p))
	{
		val = depiler(&p);
		enfiler(sortie, val);
	}
}

int priorite_operateur(int operateur)
{
	int priorite = -1;

	switch (operateur)
	{
	case '+':
	case '-':
		priorite = 0;
		break;
	case '*':
	case '/':
		priorite = 1;
		break;
	case '^':
		priorite = 2;
		break;
	
	}

	return priorite;
}

/*
 * Shunting-yard algorithm
 */
int exp_post_fixe_avec_prio(Noeud *exp, File *sortie)
{
	//affiche(exp);
	Pile p;
	Noeud *l = exp;
	int val;
	init_file_vide(sortie);
	init_pile_vide(&p);

	while (exp != 0)
	{
		if (est_operateur(exp->info))
		{
			while (!pile_est_vide(p) && tete_de_pile(p)!='(' && (priorite_operateur(tete_de_pile(p)) > priorite_operateur(exp->info)))
			{
				val = depiler(&p);
				enfiler(sortie, val);
			}

			empiler(&p, exp->info);
		}else if(exp->info=='('){ 
			empiler(&p, exp->info);

		}else if(exp->info=='('){
			empiler(&p, exp->info);

		}else if (exp->info==')')
		{
			while (1)
			{
				if (pile_est_vide(p))
				{
					printf("parenthes mismatch1");
					return 1;
				}
				if (tete_de_pile(p)!='(')
				{
					val = depiler(&p);
					enfiler(sortie, val);
				}else{
					val = depiler(&p);
					break;
				}
				
			
			}
		}else{
			enfiler(sortie, exp->info);

		}
		
		/*
		else
		{
			while (!pile_est_vide(p)&& tete_de_pile(p)!='(' && (priorite_operateur(tete_de_pile(p)) > priorite_operateur(exp->info)))
			{
				val = depiler(&p);
				enfiler(sortie, val);
			}

			empiler(&p, exp->info);
		}
		*/
		exp = exp->suivant;
	}
	while (!pile_est_vide(p))
	{
		if (tete_de_pile(p)=='(')
				{
					printf("parenthes mismatch2");
					return 1;
				}
		val = depiler(&p);
		enfiler(sortie, val);
	}
}

int calcul(int operateur, int operande_1, int operande_2)
{
	switch (operateur)
	{
	case '+':
		return operande_1 + operande_2;
	case '*':
		return operande_1 * operande_2;
	case '/':
		return operande_1 / operande_2;
	case '-':
		return operande_1 - operande_2;
	}
}

int evaluation_gauche_droite(File exp_post_fixe)
{
	Pile p;
	int val, operateur, operande_1, operande_2, resultat;
	while (!file_est_vide(exp_post_fixe))
	{
		val = defiler(&exp_post_fixe);
		//printf("%d",val);
		if (!est_operateur(val))
		{
			empiler(&p, val);
		}
		else
		{
			operande_1 = depiler(&p);
			operande_2 = depiler(&p);
			operateur = val;
			resultat = calcul(operateur, operande_1, operande_2);
			empiler(&p, resultat);
			//printf("Res:%d ",resultat);
		}
	}
	resultat = depiler(&p);
	return resultat;
}

int analyse_lexicale(FILE *fdw)
{
	int nbOc = 0, i = 0, j = 0, state = -1, nbr1;
	float dec = 0, nbr = 0;
	int rg = 1;
	int init = 0;
	Etat q = etat_initial, q_precedent = etat_initial;

	char car, tmp;
	printf("\n");

	while (!feof(fdw))
	{
		fread(&car, 1, 1, fdw);

		switch (car)
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
			if (q == etat_reel_positif || q == etat_reel_negatif)
			{
				//printf("test %d",car-'0');
				rg *= 10;
				dec = dec*10 + (car - '0');
				//printf("dec: %f",dec);
			}else if (q == etat_entier_positif || q ==etat_entier_negatif)
			{

				nbr = nbr * 10 + (car - '0');
			}else if(q==etat_signe_neg)
			{
				q = etat_entier_negatif;
				nbr = nbr * 10 + (car - '0');
			}else if(q==etat_initial||q==etat_signe_pos||q==etat_operateur)
			{
				q = etat_entier_positif;
				nbr = nbr * 10 + (car - '0');
			}else if(q==etat_par_ouvr)
			{
				q = etat_entier_positif;
				nbr = nbr * 10 + (car - '0');
			}else
			{
				printf("Etat puits\n");
				exit(1);
			}
			

			break;


		case '.':

			if (q == etat_entier_positif)
			{
				q = etat_reel_positif;

				dec = 0;
				rg = 1;
			}else if(q==etat_entier_negatif)
			{
				q = etat_reel_negatif;

				dec = 0;
				rg = 1;
			}

			break;


		
		case '+':

			if (q == etat_entier_negatif)
			{
				afficher(nbr*(-1), q);
				nbr = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_entier_positif)
			{
				afficher(nbr, q);
				nbr = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_reel_negatif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr*(-1), q);

				nbr = 0;
				dec = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_reel_positif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr, q);

				nbr = 0;
				dec = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_par_ferm)
			{
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_par_ouvr || q==etat_operateur || q==etat_initial)
			{
				q = etat_entier_positif;
				
			}else{
				printf("Etat puits\n");
				exit(1);
			}

			//q = etat_operateur;
			//afficher(car, q);
			break;



		case '-':

			if (q == etat_entier_negatif)
			{
				afficher(nbr*(-1), q);
				nbr = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_entier_positif)
			{
				afficher(nbr, q);
				nbr = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_reel_negatif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr*(-1), q);

				nbr = 0;
				dec = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_reel_positif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr, q);

				nbr = 0;
				dec = 0;
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_par_ferm)
			{
				q = etat_operateur;
				afficher(car, q);
			}else if (q == etat_par_ouvr || q==etat_operateur || q==etat_initial)
			{
				q = etat_entier_negatif;
				
			}else{
				printf("Etat puits\n");
				exit(1);
			}

			break;


		case '(':
			if(q==etat_initial ||q==etat_operateur){
				q=etat_par_ouvr;
				afficher(car, q);
			}else{
				printf("Etat puits\n");
				exit(1);
			}
			break;



		case ')':
			if (q == etat_entier_negatif)
			{
				afficher(nbr*(-1), q);
				nbr = 0;
			}else if (q == etat_entier_positif)
			{
				afficher(nbr, q);
				nbr = 0;
			}else if (q == etat_reel_negatif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr*(-1), q);

				nbr = 0;
				dec = 0;
			}else if (q == etat_reel_positif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(nbr, q);

				nbr = 0;
				dec = 0;
			}else if (q == etat_par_ferm)
			{
				afficher(car, q);
				
			}else{
				printf("Etat puits\n");
				exit(1);
			}
			q=etat_par_ferm;
			afficher(car, q);
			break;


		case '*':
		case '%':
		case '/':

			if (q == etat_entier_negatif)
			{
				afficher(nbr*(-1), q);
				nbr = 0;
			}else if (q == etat_entier_positif)
			{
				afficher(nbr, q);
				nbr = 0;
			}else if (q == etat_reel_negatif)
			{
				dec = (float)dec / rg;
				nbr += dec;
				afficher(-nbr, q);

				nbr = 0;
				rg=1;
				dec = 0;
				
			}else if (q == etat_reel_positif)
			{
				
				dec = (float)dec / rg;
				
				nbr =nbr+dec;
				//printf("dec2: %f, rg2: %i, nbr: %f",dec,rg,nbr);
				afficher(nbr, q);
				rg=1;
				nbr = 0;
				dec = 0;
			}else if (q == etat_par_ferm)
			{
				q = etat_operateur;
				afficher(car, q);
			}else{
				printf("Etat puits\n");
				exit(1);
			}

			q = etat_operateur;
			afficher(car, q);
			break;


		case '\n':
			// afficher(nbr,q);
			break;

		default:
			printf("\n%c : Parse Error, unkown char\n", car);
			return 1;
		}
		/*
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
			return -1;
	}
	*/
	}
	fclose(fdw);

	if (q == etat_entier_positif|| q==etat_reel_positif){
		dec=dec/rg;		
		nbr=nbr+dec;
		afficher(nbr, q);
		printf("\n\n");
	}
	if(q==etat_entier_negatif || q==etat_reel_negatif){
		dec=(float)dec/rg;
		nbr=nbr+dec;
		//printf("%f",nbr);
		afficher(nbr*(-1),q);
		printf("\n\n");
	}

	return 0;
}

//*******Moi*******
Noeud *build_exp_arith(FILE *fdw)
{
	Noeud **exp = (Noeud **)malloc(sizeof(Noeud *));
	exp[0] = NULL;
	char car;
	while (!feof(fdw))
	{
		fread(&car, 1, 1, fdw);
		printf("%c", car);
		if (car == '\n')
		{
			return *exp;
		}
		Noeud *noeud = nouveau(car);
		if (*exp == NULL)
		{
			*exp = noeud;
		}
		else
		{
			insert_queue(exp, car);
		}
	}
	fclose(fdw);
	return *exp;
}

//*******

int main(int argc, char **argv)
{
	int resultat1, resultat2;
	FILE *fdw = fopen(argv[1], "r");
	File sortie;

	int val_anal = analyse_lexicale(fdw);
	if (val_anal == -1)
		return -1;

	// Moi
	/********
	fdw = fopen(argv[1], "r");
	exp_arith = build_exp_arith(fdw);
	affiche(exp_arith);
	//*********
	*/

	affiche(exp_arith);
	exp_post_fixe_avec_prio(exp_arith, &sortie);
	
	resultat2 = evaluation_gauche_droite(sortie);
	printf("Avec priorité: %d\t ", resultat2);
/*
	exp_post_fixe_sans_prio(exp_arith, &sortie);
	resultat1 = evaluation_gauche_droite(sortie);

	exp_post_fixe_avec_prio(exp_arith, &sortie);
	resultat2 = evaluation_gauche_droite(sortie);

	printf("Avec priorité: %d\t Sans priorité:%d\n", resultat2, resultat1);
	/*if(val_anal == 0)*/

	return 0;
}
