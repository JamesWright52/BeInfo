#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "fonction.h"
#include "perimetre.h"
#include "listeSlicer.h"
#include "intersect.h"


ELEMT* chercheElemSuivant(LISTE* liste_surface_z, LISTE* perimetre, POINT p0, double* ptheta_balaye, double distance_max){
  ELEMT* p_element_k = liste_surface_z -> premier;
  ELEMT* element_adjacent;
  //on définit l'angle  theta comme l'angle (Oy,(M1,Msuivant))
  double theta_min = 360;
  double theta_entre_points;
  double distance_entre_points;
  double distance_min_alignes = distance_max;
  double dy = 0;
  double dx = 0;
  //  double M_PI = 3.14159265358979323846;
  while ( NULL != p_element_k ){
    //si le point a déjà été traité, on ne le considère pas
    printf("%lf %lf\n",p_element_k->p.x,p_element_k->p.y);
    if ( compteOccurence(perimetre,p_element_k->p) != 0){ p_element_k = p_element_k -> suivant; }
    else {
          dy = p_element_k->p.y - p0.y;
          dx = p_element_k->p.x - p0.x;
          //printf ("distance_entre_points = %lf distance_min_alignes= %lf\n", distance_entre_points, distance_min_alignes);

          //--------------------------------------------------------------------------
          //Ce bloc calcul theta entre le point fixé en entrée et le point de la liste désigné par p_element_k

          //topo sur arctangente pour l'angle considéré
          //dx>=0 et dy>0 => theta = arctan(dx/dy)        (varie de 0 à pi/2)
          //dx>=0 et dy<0 => theta = pi + arctan(dx/dy)   (varie de pi/2 à pi)
          //dx<=0 et dy<0 => theta = pi + arctan(dx/dy)   (varie de pi à 3pi/2)
          //dx<=0 et dy>0 => theta = 2pi + arctan(dx/dy)  (varie de 3pi/2 à 2pi)
          if ( (dy == 0) && (dx > 0)){
            theta_entre_points = 90;
          }
          else if ( (dy == 0) && (dx < 0)){
            theta_entre_points = 270;
          }
          else if ((dx >= 0) && (dy > 0)){
            theta_entre_points = atan( (dx)/(dy) ) * 180/M_PI;
          }
          else if ( (dy < 0) ) {
            theta_entre_points = (M_PI + atan( (dx)/(dy) )) * 180/M_PI;
          }
          else if ( (dx <= 0) && (dy > 0) ) {
            theta_entre_points = (2*M_PI + atan( (dx)/(dy) )) * 180/M_PI;
          }
          //le cas où on compare un point à lui-même
          else {
            theta_entre_points = 360;
          }

          //--------------------------------------------------------------------------
          //Ce bloc permet d'extraire l'angle le plus petit ainsi que, en cas d'alignement de plusieurs points, la distance la plus courte au point p0
          //on récupère l'angle le plus petit qui correspond à l'élément recherché
          distance_entre_points = sqrt(dx*dx + dy*dy);
          printf("\nPoint fixé : x = %lf, y = %lf\n",p0.x, p0.y);
          printf("Point comparé : x = %lf, y = %lf\n",p_element_k->p.x ,p_element_k->p.y);
          printf("theta=%lf theta_min=%lf\n distance_entre_points = %lf distance_min_alignes= %lf\n-------\n",theta_entre_points, theta_min, distance_entre_points, distance_min_alignes );
          if ( theta_entre_points <= theta_min ){
            theta_min = theta_entre_points;
            if ( (distance_entre_points <= distance_min_alignes) ){
              distance_min_alignes = distance_entre_points;
              element_adjacent = p_element_k;
            }
          }
          //--------------------------------------------------------------------------
          p_element_k = p_element_k -> suivant;
    }
  }
  *ptheta_balaye = theta_min;
  return element_adjacent;
}

LISTE* perimetre_Marche_Jarvis(LISTE* liste_surface_z, double distance_max){
  LISTE* perimetre = initialisation();
  //theta varie entre 0° et 360° dans le sens horaire
  double theta_balaye = 0;
  ELEMT* element_adjacent = liste_surface_z->premier ;
  while ( (compteOccurence(perimetre, element_adjacent->p) == 0 ) && (theta_balaye <= 360)){
    push_head(perimetre, element_adjacent->p, element_adjacent->vecteur);
    element_adjacent = chercheElemSuivant(liste_surface_z, perimetre, element_adjacent->p, &theta_balaye, distance_max);
    printf("compteOccurence=%d theta balaye=%lf\n", compteOccurence(perimetre, element_adjacent->p),theta_balaye);
  }
  remove_head(perimetre);
  return perimetre;
}
