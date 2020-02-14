#include <stdio.h>
#include <stdlib.h>
#include "intersect.h"
#include "listeSlicer.h"

//libérer la mémoire allouer un jour

double min(double z1, double z2, double z3){
  double min = z1;
  if (z2 < min){min = z2;}
  if (z3 < min){min = z3;}
  return min;
 }

double max(double z1, double z2, double z3){
  double max = z1;
  if (z2 > max){max = z2;}
  if (z3 > max){max = z3;}
  return max;
}

int segment_intersecte(double cote, double z1, double z2){
  if ( ( (z1 < cote) && (z2 > cote) ) || ( (z2 < cote) && (z1 > cote) ) ){
    return 1;
  }
  return 0;
}

LISTE* intersect(TRIANGLE* matrice, int* pnligne, double cote){
  int i;
  double z1, z2, z3, mini, maxi;
  POINT interpoint;
  VECTEUR normal;
  LISTE* intersection = initialisation();

  //on parcourt la matrice contenant les coordonnées des triangles ligne par ligne
  for(i = 0; i < *pnligne; i++){
    z1 = matrice[i].p1.z;
    z2 = matrice[i].p2.z;
    z3 = matrice[i].p3.z;
    mini =  min(z1,z2,z3);
    maxi =  max(z1,z2,z3);
    normal = matrice[i].vecteur;
    //le triangle est intersecté par le plan concerné sinon rien
    if ( (cote >= mini) && (maxi >= cote) ){
        //si le triangle de la ligne i est dans le plan
        if ( (z1 == cote) && (z2 == cote) && (z3 == cote) ){/* maxi = mini est plus simple non ? */
           push_head(intersection,matrice[i].p1, normal);
           push_head(intersection,matrice[i].p2, normal);
           push_head(intersection,matrice[i].p3, normal);
         }
         //si le plan intersecte un sommet
         else if ( (z1 == cote) && (z2 != cote) && (z3 != cote) ){ push_head(intersection, matrice[i].p1, normal); }
         else if ( (z2 == cote) && (z1 != cote) && (z3 != cote) ){ push_head(intersection, matrice[i].p2, normal); }
         else if ( (z3 == cote) && (z1 != cote) && (z2 != cote) ){ push_head(intersection, matrice[i].p3, normal); }

         //si le plan intersecte un côté
         else if ( (z1 == cote) && (z2 == cote) && (z3 != cote) ){
           push_head(intersection, matrice[i].p1, normal);
           push_head(intersection, matrice[i].p2, normal);
           }
         else if ( (z1 == cote) && (z2 != cote) && (z3 == cote) ){
           push_head(intersection, matrice[i].p1, normal);
           push_head(intersection, matrice[i].p3, normal);
           }
         else if ( (z1 != cote) && (z2 == cote) && (z3 == cote) ){
           push_head(intersection, matrice[i].p2, normal);
           push_head(intersection, matrice[i].p3, normal);
           }
         //sinon on calcul l'intersection du plan avecle triangle
         else {
            //deux points sont du même côté du plan : le segment formé n'intersecte pas le plan
            if (segment_intersecte(cote,z1,z2) == 1){
               // on applique les formules de géométries:
               // x = ((zi-z1)x2 -(zi-z2)x1)/(z2-z1)
               interpoint.x = ( (cote - z1) * matrice[i].p2.x - (cote - z2) * matrice[i].p1.x ) / (z2-z1);
               interpoint.y = ( (cote - z1) * matrice[i].p2.y - (cote - z2) * matrice[i].p1.y ) / (z2-z1);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
            if (segment_intersecte(cote,z2,z3) == 1) {
               interpoint.x = ( (cote - z2) * matrice[i].p3.x - (cote - z3) * matrice[i].p2.x ) / (z3-z2);
               interpoint.y = ( (cote - z2) * matrice[i].p3.y - (cote - z3) * matrice[i].p2.y ) / (z3-z2);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
            if (segment_intersecte(cote,z3,z1) == 1) {
               interpoint.x = ( (cote - z3) * matrice[i].p1.x - (cote - z1) * matrice[i].p3.x ) / (z1-z3);
               interpoint.y = ( (cote - z3) * matrice[i].p1.y - (cote - z1) * matrice[i].p3.y ) / (z1-z3);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
         }
     }
  }
  return intersection;
}

//Elimine les points en double
int compteOccurence(LISTE* liste, POINT point){
	ELEMT* elementListe = liste->premier;
	int occurence = 0;
  int i = 0;
	while (NULL != elementListe->suivant){
		if   (   (point.x == (elementListe->p).x)
		      && (point.y == (elementListe->p).y)
				  && (point.z == (elementListe->p).z) ){
			occurence = occurence + 1;
      i = i+1;
    }
		elementListe = elementListe->suivant;
	}
	return occurence;
}


LISTE* listeSansDoublon(LISTE* liste){
  ELEMT* elementListe;
  LISTE* sansDoublon = initialisation();
	elementListe = liste->premier;
	while (NULL != elementListe->suivant){
    if (compteOccurence(sansDoublon, elementListe->p) == 0){
       push_head(sansDoublon, elementListe->p, elementListe->vecteur);
    }
    elementListe = elementListe->suivant;
  }
  efface(liste);
  return sansDoublon;
}
