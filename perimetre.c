#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "perimetre.h"
#include "listeSlicer.h"
#include "intersect.h"


ELEMT chercheElemSuivant(LISTE* liste_surface_z, LISTE* perimetre, POINT p0, double* ptheta ){
  ELEMT element_iteratif = *(liste_surface_z)-> premier;
  ELEMT element_adjacent;
  //on définit l'angle  theta comme l'angle (Oy,(M1,Msuivant))
  double theta_min = *ptheta;
  double theta;
  while( element_iteratif.suivant != NULL ){
    //on vérifie qu'on ne compare pas p0 avec lui-même
    if (compteOccurence(perimetre, element_iteratif.p) == 0){
      theta = arctan(element_iteratif.p.x - p0.x)/(element_iteratif.p.y - p0.y);
      printf("element_iteratif.p.y - p0.y = %lf, element_iteratif.p.x - p0.x = %lf ,theta = %lf, thetamin= %lf\n",element_iteratif.p.y - p0.y,element_iteratif.p.x - p0.x,theta, theta_min );
      if (theta_min > theta){
        theta_min = theta;
        element_adjacent = element_iteratif;
       }
      element_iteratif = *(element_iteratif.suivant);
    }
  }
  printListe(perimetre->premier);
  ptheta = &theta_min;
  return element_adjacent;
}

LISTE* perimetre_Marche_Jarvis(LISTE* liste_surface_z){
  LISTE* perimetre = initialisation();
  //theta varie entre 90° et -90°
  double theta = 90;
  POINT p0 = (*(liste_surface_z->premier)).p;
  while ( theta != -90 ){
    ELEMT element_adjacent = chercheElemSuivant(liste_surface_z, perimetre,p0, &theta);

    if (compteOccurence(perimetre, element_adjacent.p) == 0){
      push_head(perimetre, element_adjacent.p, element_adjacent.vecteur);
    }
    p0 = element_adjacent.p;
  }
  return perimetre;
}
