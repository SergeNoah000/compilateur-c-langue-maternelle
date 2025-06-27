/*
 * listeChaine.c
 *
 *  Created on: Dec 28, 2012
 *      Author: messi
 */
#include <stdlib.h>
#include "utilitaire.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>


/*
 * Manipulation des listes chainées
 */
Noeud* nouveau(int val)
{
  	Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
  	noeud->info = val;
	noeud->type=INT;
	noeud->f_info=NAN;
  	noeud->suivant = 0;
    return noeud;
}

Noeud* c_nouveau(char val)
{
	//printf("enteredchar");
  	Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
  	noeud->info = val;
	noeud->type=OPER;
	//printf("type:%d",noeud->type);
	noeud->f_info=NAN;
  	noeud->suivant = 0;
    return noeud;
}

Noeud* f_nouveau(float val)
{
  	Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
  	noeud->f_info = val;
	noeud->type=FLOAT;
	noeud->info=INFINITY;
  	noeud->suivant = 0;
    return noeud;
}

void insert_tete(Noeud** liste, int val)
{
	Noeud* l = nouveau(val);
	l->suivant = *liste;
	*liste = l;
}
void c_insert_tete(Noeud** liste, char val)
{
	Noeud* l = c_nouveau(val);
	l->suivant = *liste;
	*liste = l;
}

void f_insert_tete(Noeud** liste, float val)
{
	Noeud* l = f_nouveau(val);
	l->suivant = *liste;
	*liste = l;
}


void inverse_liste(Noeud**liste)
{
	Noeud* l = 0;
	Noeud* q = *liste;
	Noeud* p;
	while(q!=0){
		if (q->type==INT)
		{
			insert_tete(&l,q->info);
		}else if(q->type==FLOAT){
			f_insert_tete(&l,q->f_info);
		}else
		{
			c_insert_tete(&l,q->info);
		}
		
		
		p = q;
		q = q->suivant;
		free(p);
	}
	*liste = l;

}

void insert_queue(Noeud** liste, int val)
{
	inverse_liste(liste);
	insert_tete(liste, val);
	inverse_liste(liste);
}

void f_insert_queue(Noeud** liste, float val)
{
	inverse_liste(liste);
	f_insert_tete(liste, val);
	inverse_liste(liste);
}
void c_insert_queue(Noeud** liste, char val)
{
	inverse_liste(liste);
	c_insert_tete(liste, val);
	inverse_liste(liste);
}


void supprime_tete(Noeud ** liste)
{
	Noeud* l = *liste;
	*liste = (*liste)->suivant;
	free(l);
}

void supprime_queue(Noeud**liste)
{
	inverse_liste(liste);
	supprime_tete(liste);
	inverse_liste(liste);
}


int tete_de_liste(Noeud* liste)
{
	return liste->info;
}

float f_tete_de_liste(Noeud* liste)
{
	return liste->f_info;
}

int fin_de_liste(Noeud* liste)
{
	int val;
	inverse_liste(&liste);
	val = liste->info;
	inverse_liste(&liste);

	return val;
}

float f_fin_de_liste(Noeud* liste)
{
	float val;
	inverse_liste(&liste);
	val = liste->f_info;
	inverse_liste(&liste);

	return val;
}


void affiche(Noeud * liste)
{
	Noeud * l = liste;
	printf("\n");

	while(l!=0){
		if (l->type==INT)
		{
			if (l->info=='('||l->info==')')
			{
				printf("%c",l->info);
			}else{
				printf("%d",l->info);
			}
			
		}else if(l->type==OPER){
			printf(" %c ",l->info);
			

		}else{
			printf("%f",l->f_info);
			
		}
		
		l = l->suivant;
	}

	printf("\n");
}

/*
 * Manipulation des piles
 */

void init_pile_vide(Pile *p)
{
	(*p).indiceCourant = -1;
	(*p).liste = 0;
	(*p).taille = 0;
}
int pile_est_vide(Pile p)
{
	int taille = p.taille;

	if(taille == 0)
		return 1;
	else
		return 0;
}
void empiler(Pile*p, int val)
{
  insert_tete(&((*p).liste),val);
  (*p).indiceCourant ++;
  (*p).taille++;
}
void c_empiler(Pile*p, char val)
{
  c_insert_tete(&((*p).liste),val);
  (*p).indiceCourant ++;
  (*p).taille++;
}

void f_empiler(Pile*p, float val)
{
  f_insert_tete(&((*p).liste),val);
  (*p).indiceCourant ++;
  (*p).taille++;
}


int depiler(Pile*p)
{
   int val = -1;
   if(!pile_est_vide(*p))
   {
	   val = tete_de_liste((*p).liste);
       supprime_tete(&((*p).liste));
       (*p).indiceCourant --;
       (*p).taille--;
   }
   return val;
}

float f_depiler(Pile *p)
{
   float val = -1;
   if(!pile_est_vide(*p))
   {
	   val = f_tete_de_liste((*p).liste);
       supprime_tete(&((*p).liste));
       (*p).indiceCourant --;
       (*p).taille--;
   }
   return val;
}

int tete_de_pile(Pile p)
{
	int val = -1;
	if(!pile_est_vide(p))
		val = p.liste->info;
	return val;
}

float f_tete_de_pile(Pile p)
{
	float val = -1;
	if(!pile_est_vide(p))
		val = p.liste->f_info;
	return val;
}


int taille_de_pile(Pile p)
{
	return p.taille;
}

int indice_de_pile(Pile p)
{
	return p.indiceCourant;
}

/*
 * Manipulation des files
 */

void init_file_vide(File *f)
{
	(*f).indiceCourant = -1;
	(*f).liste = 0;
	(*f).taille = 0;
}
int file_est_vide(File f)
{
	int taille = f.taille;

	if(taille == 0)
		return 1;
	else
		return 0;
}



void enfiler(File *f, int val)
{
  insert_queue(&((*f).liste),val);
  (*f).indiceCourant ++;
  (*f).taille++;
}

void c_enfiler(File *f, char val)
{
  c_insert_queue(&((*f).liste),val);
  (*f).indiceCourant ++;
  (*f).taille++;
}

void f_enfiler(File*f, float val)
{
  f_insert_queue(&((*f).liste),val);
  (*f).indiceCourant ++;
  (*f).taille++;
}




int defiler(File*f)
{
   int val = -1;
   if(!file_est_vide(*f))
   {
	   val = tete_de_liste((*f).liste);
       supprime_tete(&((*f).liste));
       (*f).indiceCourant --;
       (*f).taille--;
   }
   return val;
}

float f_defiler(File*f)
{
   float val = -1;
   if(!file_est_vide(*f))
   {
	   val = f_tete_de_liste((*f).liste);
       supprime_tete(&((*f).liste));
       (*f).indiceCourant --;
       (*f).taille--;
   }
   return val;
}



int tete_de_file(File f)
{
	int val = -1;
	if(!file_est_vide(f))
		val = f.liste->info;
	return val;
}
float f_tete_de_file(File f)
{
	float val = -1;
	if(!file_est_vide(f))
		val = f.liste->f_info;
	return val;
}



int taille_de_file(File f)
{
	return f.taille;
}

int indice_de_file(File f)
{
	return f.indiceCourant;
}
