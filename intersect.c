#include <stdio.h>
#include <stdlib.h>
#include "intersect.h"
#include "listeSlicer.h"

//libérer la mémoire allouer un jour

double min(double z1, double z2, double z3){
  double min = z1;
  if (z2 < min){z2 = min;}
  if (z3 < min){z3 = min;}
  return min;
 }

double max(double z1, double z2, double z3){
  double max = z1;
  if (z2 > max){z2 = max;}
  if (z3 > max){z3 = max;}
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
  double z1, z2, z3;
  POINT interpoint;
  VECTEUR normal;
  LISTE* intersection = initialisation();

  //on parcourt la matrice contenant les coordonnées des triangles ligne par ligne
  for(i = 0; i < *pnligne; i++){
    z1 = matrice[i].p1.z;
    z2 = matrice[i].p2.z;
    z3 = matrice[i].p3.z;
    normal = matrice[i].vecteur;
    //le triangle est intersecté par le plan concerné sinon rien
    if ( (cote <= min(z1,z2,z3) ) || (max(z1,z2,z3) <= cote) ){
        //si le triangle de la ligne i est dans le plan
        if ( (z1 == cote) && (z2 == cote) && (z3 == cote) ){
           push_head(intersection,&matrice[i].p1, &normal);
           push_head(intersection,&matrice[i].p2, &normal);
           push_head(intersection,&matrice[i].p3, &normal);
         }
         //si le plan intersecte un sommet
         else if ( (z1 == cote) && (z2 != cote) && (z3 != cote) ){ push_head(intersection, &matrice[i].p1, &normal); }
         else if ( (z2 == cote) && (z1 != cote) && (z3 != cote) ){ push_head(intersection, &matrice[i].p2, &normal); }
         else if ( (z3 == cote) && (z1 != cote) && (z2 != cote) ){ push_head(intersection, &matrice[i].p3, &normal); }

         //si le plan intersecte un côté
         else if ( (z1 == cote) && (z2 == cote) && (z3 != cote) ){
           push_head(intersection, &matrice[i].p1, &normal);
           push_head(intersection, &matrice[i].p2, &normal);
           }
         else if ( (z1 == cote) && (z2 != cote) && (z3 == cote) ){
           push_head(intersection, &matrice[i].p1, &normal);
           push_head(intersection, &matrice[i].p3, &normal);
           }
         else if ( (z1 != cote) && (z2 == cote) && (z3 == cote) ){
           push_head(intersection, &matrice[i].p2, &normal);
           push_head(intersection, &matrice[i].p3, &normal);
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
               push_head(intersection, &interpoint, &normal);
               }
            if (segment_intersecte(cote,z2,z3) == 1) {
               interpoint.x = ( (cote - z2) * matrice[i].p3.x - (cote - z3) * matrice[i].p2.x ) / (z3-z2);
               interpoint.y = ( (cote - z2) * matrice[i].p3.y - (cote - z3) * matrice[i].p2.y ) / (z3-z2);
               interpoint.z = cote;
               push_head(intersection, &interpoint, &normal);
               }
            if (segment_intersecte(cote,z3,z1) == 1) {
               interpoint.x = ( (cote - z3) * matrice[i].p1.x - (cote - z1) * matrice[i].p3.x ) / (z1-z3);
               interpoint.y = ( (cote - z3) * matrice[i].p1.y - (cote - z1) * matrice[i].p3.y ) / (z1-z3);
               interpoint.z = cote;
               push_head(intersection, &interpoint, &normal);
               }
         }
     }
  }
  return intersection;
}

// //error not working
// POINT point_min_abscisse(POINT** liste_surface, int* pnligne){
//   int ligne,col;
//   double x_min = liste_surface[0] ;
//
//   for (ligne = 0; ligne < *pnligne; ligne ++){
//     for (col = 0; col < 3; col++){
//       if (x_min > liste_surface[i][j].x){
//         x_min = liste_surface[i][j].x;
//       }
//     }
//   }
//   return x_min
// }

// POINT* perimetre_Marche_Jarvis(POINT** liste_surface_z,int* pnligne){
//   //en espérant allouer suffisament de mémoire
//   POINT* perimetre = calloc(3*(*pnligne),sizeof(*perimetre));
//   if (perimetre == NULL){free (perimetre);}
//   int ligne,colonne;
//   int k =0;
//   POINT p0 = point_min_abscisse(liste_surface_z, pnligne);
//   POINT p = liste_surface_z[0][0];
//   double theta_max = (p.y - p0.y)/(p.x - p0.x);
//   for (ligne = 0; ligne < *pnligne; ligne++){
//     for (colonne = 0; colonne < 3; colonne ++){
//       if ( (p.x != p0.x) && (p.y != p0.y)){
//         if ( (p.y - p0.y)/(p.x - p0.x) > theta_max ){
//           theta_max = (p.y - p1.y)/(p.x - p1.x);
//         }
//       }
//       p = liste_surface_z[ligne][colonne];
//     }
//   }
//   while (p != p0){
//
//   }
// }
