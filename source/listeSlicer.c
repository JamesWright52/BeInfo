/*
 ============================================================================
 Name        : slist.c
 Author      :
 Version     :
 Copyright   : free to be used
 Description : linked List in C
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "listeSlicer.h"

LISTE* initialisation(){
	LISTE* liste = calloc(1,sizeof(*liste));
	if ( liste == NULL ){
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
	return liste;
}

/* Insertion en d�but de liste */
void push_head(LISTE* liste, POINT nouveauPoint, VECTEUR vecteur){
	ELEMT* nouveau = calloc(1,sizeof(ELEMT));
	if (nouveau == NULL || liste == NULL){exit(1);}
	nouveau->p = nouveauPoint;
	nouveau->vecteur = vecteur;
	nouveau->suivant = liste->premier;
	liste->premier = nouveau;
}

void remove_head(LISTE* liste){
	if (liste == NULL){exit(EXIT_FAILURE);}
	if (liste->premier != NULL){
		ELEMT* aSupprimer = liste->premier;
		liste->premier =liste->premier->suivant;
		free(aSupprimer);
	}
}

/* Suppression de la liste" */
void efface(LISTE* liste){
	ELEMT* p = liste->premier;
	while(p != NULL){
		ELEMT* suivant = p->suivant;
		free(p);
		p = suivant;
	}
}

/* Procedure d'affichage de la liste */
void printListe(ELEMT * ptr0){
	if ( NULL == ptr0 ){ printf("Vide!\n"); }
	printf("Liste : \n") ;
	while ( NULL != ptr0 ){
		printf("point=(%f, %f, %f,)\n", (ptr0->p).x, (ptr0->p).y, (ptr0->p).z);
		ptr0 = ptr0->suivant ;
	}
}
