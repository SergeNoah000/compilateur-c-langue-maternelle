/*
 ============================================================================
 Name        : exo4.c, created on: Dec 23, 2012
 Author      : Messi Nguélé Thomas
 Version     : 1.0
 Copyright   : Welcome, your are allowed to copy this code and reuse it as you want!
 Description : This program build a tinny lexical analysis for arithmetic expression which print lexemes come from the file file_expression_name. Ansi-style
 Usage        : ./exo3-2 file_expression_name
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
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

void afficher(float valeur, Etat q_courant)
{
	if (q_courant == etat_entier_negatif || q_courant == etat_entier_positif){
		printf("<int:%d>", (int)valeur);
		//insert_queue(&exp_arith, (int)valeur );
	}
		
	if (q_courant == etat_operateur){
		printf("<oper:%c>", (int)valeur);
		//c_insert_queue(&exp_arith, (char)valeur );
	}
		
	if (q_courant == etat_par_ouvr || q_courant == etat_par_ferm){
		printf("<paren:%c>", (char)valeur);
		//insert_queue(&exp_arith, valeur );
	}
	if (q_courant == etat_reel_negatif || q_courant == etat_reel_positif){
		printf("<reel:%f>", valeur);
		//f_insert_queue(&exp_arith, valeur );
	}
		
		//printf("%d\n",(int)valeur);
	//insert_queue(&exp_arith, valeur );
	//affiche(exp_arith);
}
/*
void afficher(float valeur, Etat q_courant){
	if(q_courant == etat_nombre)
		printf("<int:%d>",(int)valeur);
	if(q_courant == etat_operateur)
		printf("<oper:%c>",(char)valeur);
	if(q_courant == etat_reel)
		printf("<reel:%f>",valeur);
}

int analyse_lexicale(FILE* fdw)
{
	float nbOc = 0, i = 0, j = 0, state = -1, nbr=0,nbr1;
	int init = 0;
	Etat q = etat_initial, q_precedent = etat_initial;


	char car,tmp; 
	int rg=1; 
	float dec=0;
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
					  if(q==etat_reel){
						  
						  rg*=10;
						  dec=dec*10+(car-'0');
						  
						}else{
							q = etat_nombre;
							nbr = nbr*10 + (car-'0');
							
					  }

	                  break;
			case '.':

					if(q==etat_nombre){
						q = etat_reel;

						
						dec=0;
						rg=1;
					
					}

					
				    break;

		   	case '+':
		   	case '*':
			case '-':
			case '/':
			

					if(q==etat_nombre){
						afficher(nbr,q);
						nbr = 0;
					}
					if (q==etat_reel){
						dec=(float)dec/rg;
						nbr+=dec;
						afficher(nbr,q);
						
						nbr=0;
						dec=0;
					}

					q = etat_operateur;
					afficher(car,q);
				    break;
		   	case '\n':
			   			//afficher(nbr,q);
		   				break;

			default:
				printf("\n%c : Parse Error, unkown char\n",car);
				return 1;
		}
	}
	fclose(fdw);

	if(q==etat_nombre || q==etat_reel){
		

		dec=(float)dec/rg;
		
		nbr=nbr+dec;
		afficher(nbr,q);}
	printf("\n\n");
	return 0;
}

*/
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


int main(int argc, char** argv)
{
FILE* fdw = fopen(argv[1],"r");
int val_anal = analyse_lexicale(fdw);

return 0;
}


