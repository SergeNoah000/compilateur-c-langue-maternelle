/*
 * listeChaine.c
 *
 *  Created on: Dec 28, 2012
 *      Author: messi
 */
#include <stdlib.h>
#include "utilitaire.h"
#include <stdio.h>


/*
 * Manipulation des listes chainées
 */
Noeud* nouveau(int val)
{
  	Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
  	noeud->info = val;
  	noeud->suivant = 0;
    return noeud;
}

void insert_tete(Noeud** liste, int val)
{
	Noeud* l = nouveau(val);
	l->suivant = *liste;
	*liste = l;
}
void inverse_liste(Noeud**liste)
{
	Noeud* l = 0;
	Noeud* q = *liste;
	Noeud* p;
	while(q!=0){
		insert_tete(&l,q->info);
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

int fin_de_liste(Noeud* liste)
{
	int val;
	inverse_liste(&liste);
	val = liste->info;
	inverse_liste(&liste);

	return val;
}

void affiche(Noeud * liste)
{
	Noeud * l = liste;
	printf("\n");

	while(l!=0){
		printf("%d",l->info);
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
int tete_de_pile(Pile p)
{
	int val = -1;
	if(!pile_est_vide(p))
		val = p.liste->info;
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
void enfiler(File*f, int val)
{
  insert_queue(&((*f).liste),val);
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
int tete_de_file(File f)
{
	int val = -1;
	if(!file_est_vide(f))
		val = f.liste->info;
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
