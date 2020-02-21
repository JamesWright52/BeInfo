#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "perimetre.h"
#include "listeSlicer.h"
#include "intersect.h"


ELEMT* chercheElemSuivant(LISTE* liste_surface_z, LISTE* perimetre, POINT p0, double* ptheta ){
  ELEMT* p_element_k = liste_surface_z -> premier;
  ELEMT* element_adjacent;
  //on définit l'angle  theta comme l'angle (Oy,(M1,Msuivant))
  double theta_min = *ptheta;
  double theta_entre_points;
  double M_PI = 3.14159265358979323846;
  while ( p_element_k->suivant != NULL ){
    //on vérifie qu'on ne compare pas p0 avec lui-même
    if (compteOccurence(perimetre, p_element_k->p) == 0){
      if ( (p_element_k->p.y - p0.y == 0) && (p_element_k->p.x - p0.x > 0)){
        theta_entre_points = 90;
      }
      else if ((p_element_k->p.y - p0.y == 0) && (p_element_k->p.x - p0.x < 0)){
        theta_entre_points = 270;
      }
      //+- pi/2
      else if ( (p_element_k->p.x - p0.x == 0) && (p_element_k->p.y - p0.y > 0) ) {
        theta_entre_points = 0;
      }
      else if ( (p_element_k->p.x - p0.x == 0) && (p_element_k->p.y - p0.y < 0) ) {
        theta_entre_points = 180;
      }
      //le cas où on compare un point à lui-même
      else if ( (p_element_k->p.x - p0.x != 0) && (p_element_k->p.y - p0.y > 0) ){
        theta_entre_points = atan( (p_element_k->p.x - p0.x)/(p_element_k->p.y - p0.y) ) * (180/(M_PI));}
      }
      else if ( (p_element_k->p.x - p0.x != 0) && (p_element_k->p.y - p0.y < 0) ){
        theta_entre_points = atan( (p_element_k->p.x - p0.x)/(p_element_k->p.y - p0.y) ) * (180/(M_PI));}
      }
    //comme le premier point est quelconque, il faut vérifier que tous les angles sont positifs
    if ( (theta_entre_points < 0) || ( (theta_entre_points == 0) && (p_element_k->p.y - p0.y < 0) )){ theta_entre_points += 360;}
    //on récupère l'angle le plus petit qui correspond à l'élément recherché
    if (theta_min > theta_entre_points){
      theta_min = theta_entre_points;
      element_adjacent = p_element_k;
    }
    printf("1 dy = %lf, dx = %lf ,theta_entre_points = %lf, thetamin= %lf\n",p_element_k->p.y - p0.y,p_element_k->p.x - p0.x,theta_entre_points, theta_min );
    p_element_k = p_element_k -> suivant;
  }
  printListe(perimetre->premier);
  ptheta = &theta_min;
  return element_adjacent;
}

LISTE* perimetre_Marche_Jarvis(LISTE* liste_surface_z){
  LISTE* perimetre = initialisation();
  //theta varie entre 0° et 360° dans le sens horaire
  double theta = 359;
  double somme_theta = 0;
  POINT p0 = (*(liste_surface_z->premier)).p;
  ELEMT* element_adjacent = chercheElemSuivant(liste_surface_z, perimetre, p0, &theta);
  while ( somme_theta < 360 ){
    element_adjacent = chercheElemSuivant(liste_surface_z, perimetre, p0, &theta);
    somme_theta += theta;
    if (compteOccurence(perimetre, element_adjacent->p) == 0){
      push_head(perimetre, element_adjacent->p, element_adjacent->vecteur);
    }
    p0 = element_adjacent->p;
  }
  return perimetre;
}
