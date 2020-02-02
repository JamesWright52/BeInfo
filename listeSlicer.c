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
	ELEMT* element = calloc(1,sizeof(*element));
	if (element == NULL || liste == NULL){
		exit(EXIT_FAILURE);
	}
	POINT p0 = {0,0,0};
	element->p = &p0;
	element->suivant = NULL;
	liste->premier = element;
	return liste;
}

/* Insertion en d�but de liste */
void push_head(LISTE* liste, POINT* nouveauPoint){
	ELEMT* nouveau = calloc(1,sizeof(ELEMT));
	if (nouveau == NULL || liste == NULL){exit(1);}
	nouveau->p = nouveauPoint;
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
void print(ELEMT * ptr){
	if ( NULL == ptr ){
		printf("Empty!\n") ;
		return;
	}

	printf("List : \n") ;
	while ( NULL != ptr ) 	{
		printf("ptr=%p point=(%f %f %f) ptr->next=%p\n", ptr, ptr->p->x, ptr->p->y, ptr->p->z, ptr->suivant);
		ptr = ptr->suivant ;
	}
	printf("\n") ;
	getchar();
}
