/*
 * listeChaine.h
 *
 *  Created on: Dec 28, 2012
 *      Author: messi
 */

#ifndef UTILITAIRE_H_
#define UTILITAIRE_H
#define INT 0
#define FLOAT 1
#define OPER 2
/*
 * Manipulation des listes chainées
 */
struct Noeud{
	int info;
	float f_info;
	int type;
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

//Gestion des reels
Noeud *f_nouveau(float val);
void f_insert_tete(Noeud** liste, float val);
void f_insert_queue(Noeud** liste, float val);
float f_tete_de_liste(Noeud* liste);
float f_fin_de_liste(Noeud* liste);

Noeud *c_nouveau(char val);
void c_insert_tete(Noeud** liste, char val);
void c_insert_queue(Noeud** liste, char val);
//char c_tete_de_liste(Noeud* liste);
//char c_fin_de_liste(Noeud* liste);


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

//Gestion des reels
void f_empiler(Pile*p, float val);
float f_tete_de_pile(Pile p);
float f_depiler(Pile*p);

void c_empiler(Pile*p, char val);
//char c_tete_de_pile(Pile p);
//char c_depiler(Pile*p);

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

//Gestion des reels
void f_enfiler(File*p, float val);
float f_defiler(File*f);
float f_tete_de_file(File f);

void c_enfiler(File*p, char val);
//char c_defiler(File*f);

#endif /* UTILITAIRE_H_ */
