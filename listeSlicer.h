#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "intersect.h"

typedef struct Liste{
	ELEMT *premier;
} LISTE;

/* Ici, on est oblige d'utiliser la notation struct listepoint,
car la structure s'auto-reference!*/
typedef struct elemListe {
	POINT* p;
	struct elemListe *suivant ;
} ELEMT ;

//initialisation du début de la liste chainée
LISTE* initialisation();

/* Insertion en début de liste */
ELEMT* push_head(LISTE* liste, POINT nouveauPoint);

//enlève le premier élément de la liste
void remove_head(LISTE* liste);

/* Suppression de la liste" */
void* efface(LISTE* liste);

/* Procedure d'affichage de la liste */
void print(ELEMT * ptr);
