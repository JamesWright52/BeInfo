#include <stdio.h>
#include <stdlib.h>

typedef struct {double x; double y; double z;} POINT;

typedef struct {int a; int b; int c;} VECTEUR;

typedef struct {POINT p1; POINT p2; POINT p3; VECTEUR n;} TRIANGLE;

//fonction qui prends une matrice de coordonnees et une côte en argument et renvoie la liste
//des intersections entre le plan z et l'objet

POINT** intersect(TRIANGLE* matrice, int* pnligne, double cote){
  double z1, z2, z3;
  VECTEUR normal;
  //il faut allouer une matrice de taille *pnbligne * 3 *flemme de faire ça maintenant*
  int j;
  POINT** intersection = calloc(*pnligne,sizeof(**intersection));
  if (intersection == NULL){free (intersection);}
  else {
    *intersection = calloc(3, sizeof(*intersection));
    if (*intersection == NULL){free(intersection);}
    else {for (j=1 ; j<*pnligne ; j++){ intersection[j] = intersection[j-1] + 3 ;} }
  }
  //
  int i;
  for(i == 0; i < *pnligne; i++){
    z1 = matrice[i].p1.z;
    z2 = matrice[i].p2.z;
    z3 = matrice[i].p3.z;
    normal = matrice[i].n;
    //le triangle est intersecté par le plan concerné sinon rien !!!!définir max et min!!!!
    if ( (cote <= min(z1,z2,z3) ) || (max(z1,z2,z3) <= cote) ){
        //si le triangle de la ligne i est dans le plan
        if ( (z1 == cote) && (z2 == cote) && (z3 == cote) ){
           intersection[i][0] = matrice[i].p1;
           intersection[i][1] = matrice[i].p2;
           intersection[i][2] = matrice[i].p3;
         }
         //si le plan intersecte un sommet
         else if ( (z1 == cote) && (z2 != cote) && (z3 != cote) ){ intersection[i][0] = matrice[i].p1; }
         else if ( (z2 == cote) && (z1 != cote) && (z3 != cote) ){ intersection[i][1] = matrice[i].p2; }
         else if ( (z3 == cote) && (z1 != cote) && (z2 != cote) ){ intersection[i][2] = matrice[i].p3; }

         //si le plan intersecte un côté
         else if ( (z1 == cote) && (z2 == cote) && (z3 != cote) ){
           intersection[i][0] = matrice[i].p1;
           intersection[i][1] = matrice[i].p2;
           }
         else if ( (z1 == cote) && (z2 != cote) && (z3 == cote) ){
           intersection[i][0] = matrice[i].p1;
           intersection[i][2] = matrice[i].p3;
           }
         else if ( (z1 != cote) && (z2 == cote) && (z3 == cote) ){
           intersection[i][1] = matrice[i].p2;
           intersection[i][2] = matrice[i].p3;
           }
         //sinon on calcul l'intersection du plan avecle triangle
         else {
            //deux points sont du même côté du plan : le segment formé n'intersecte pas le plan
            //définir une fonction segment_intersecte(z1,z2) qui renvoie 1 si le segment entre z1 et z2 intersecte le plan
            if (segment_intersecte(z1,z2) == 1){
               // on applique les formules de géométries:
               // x = ((zi-z1)x2 -(zi-z2)x1)/(z2-z1)
               intersection[i][0].x = ( (cote - z1) * matrice[i].p2.x - (cote - z2) * matrice[i].p1.x ) / (z2-z1);
               intersection[i][0].y = ( (cote - z1) * matrice[i].p2.y - (cote - z2) * matrice[i].p1.y ) / (z2-z1);
               intersection[i][0].z = cote;
               }
            if (segment_intersecte(z2,z3) == 1) {
               intersection[i][1].x = ( (cote - z2) * matrice[i].p3.x - (cote - z3) * matrice[i].p2.x ) / (z3-z2);
               intersection[i][1].y = ( (cote - z2) * matrice[i].p3.y - (cote - z3) * matrice[i].p2.y ) / (z3-z2);
               intersection[i][1].z = cote;
               }
            if (segment_intersecte(z3,z1) == 1) {
               intersection[i][2].x = ( (cote - z3) * matrice[i].p1.x - (cote - z1) * matrice[i].p3.x ) / (z1-z3);
               intersection[i][2].y = ( (cote - z3) * matrice[i].p1.y - (cote - z1) * matrice[i].p3.y ) / (z1-z3);
               intersection[i][2].z = cote;
               }
         }
     }
  }
  return intersection;
}

//definir une fonction qui prends la matrice de coordonnes et une côte en paramètre
//et renvoie tous les points du périmètre de l'objet à cette côte.
//TRIANGLE perimetreSlice()
