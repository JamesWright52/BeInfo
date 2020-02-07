#ifndef LISTESLICER_H
#define LISTESLICER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "intersect.h"

//initialisation du début de la liste chainée
LISTE* initialisation();

/* Insertion en début de liste */
void push_head(LISTE* liste, POINT* nouveauPoint, VECTEUR* vecteur);

//enlève le premier élément de la liste
void remove_head(LISTE* liste);

/* Suppression de la liste" */
void efface(LISTE* liste);

/* Procedure d'affichage de la liste */
void printListe(ELEMT * ptr0);

//Elimine les points en double
int compteOccurence(LISTE* liste, POINT* point);

#endif
