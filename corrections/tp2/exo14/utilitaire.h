/*
 * listeChaine.h
 *
 *  Created on: Dec 28, 2012
 *      Author: messi
 */

#ifndef UTILITAIRE_H_
#define UTILITAIRE_H

/*
 * Manipulation des listes chainées
 */
struct Noeud{
	int info;
	struct Noeud * suivant;
};
typedef struct Noeud Noeud;

Noeud* nouveau(int val);
void insert_tete(Noeud** liste, int val);
void supprime_tete(Noeud ** liste);
void inverse_liste(Noeud**liste);
void insert_queue(Noeud** liste, int val);
void supprime_queue(Noeud**liste);
int tete_de_liste(Noeud* liste);
int fin_de_liste(Noeud* liste);
void affiche(Noeud * liste);


/*
 * Manipulation des piles
 */
struct Pile{
	Noeud* liste;
	int taille;
	int indiceCourant;
};

typedef struct Pile Pile;

void init_pile_vide(Pile *p);
void empiler(Pile*p, int val);
int depiler(Pile*p);
int pile_est_vide(Pile p);
int tete_de_pile(Pile p);
int taille_de_pile(Pile p);
int indice_de_pile(Pile p);

/*
 * Manipulation des files
 */
/*
 * Manipulation des piles
 */
struct File{
	Noeud* liste;
	int taille;
	int indiceCourant;
};

typedef struct File File;

void init_file_vide(File *f);
void enfiler(File*f, int val);
int defiler(File*f);
int file_est_vide(File f);
int tete_de_file(File f);
int taille_de_file(File f);
int indice_de_file(File f);



#endif /* UTILITAIRE_H_ */
