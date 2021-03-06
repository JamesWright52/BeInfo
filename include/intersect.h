#ifndef INTERSECT_H
#define INTERSECT_H

#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

/* Ici, on est oblige d'utiliser la notation struct listepoint,
car la structure s'auto-reference!*/
typedef struct elemListe {
	POINT p;
	VECTEUR vecteur;
	struct elemListe* suivant ;
} ELEMT ;

typedef struct Liste{
	ELEMT *premier;
} LISTE;

//fonction qui prends une matrice de coordonnees et une côte en argument
//renvoie la liste des points d'intersections entre le plan z et l'objet
//(format [[P1,P2,P3],...,[P3n,,P3n+1,P3n+2]])
LISTE* intersect(TRIANGLE* matrice, int* pnligne, double cote);

// Renvoie le plus petit réel parmi 3.
double min(double z1, double z2, double z3);

// Renvoie le plus grand réel parmi 3.
double max(double z1, double z2, double z3);

//renvoie 1 si le segment entre z1 et z2 intersecte le plan
int segment_intersecte(double cote,double z1, double z2);

//compte le nombre de fois où point apparaît
int compteOccurence(LISTE* liste, POINT point);

//Elimine les points en double
LISTE* listeSansDoublon(LISTE* liste);


#endif
