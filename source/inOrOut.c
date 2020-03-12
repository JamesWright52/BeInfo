#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"
#include "inOrOut.h"

double minim(double P1, double P2){
  if (P1 < P2){ return P1;}
  return P2;
}

double maxim(double P1, double P2){
  if (P1 > P2){ return P1;}
  return P2;
}

// tableau 2D (matrice) avec tous les points du plateau
// plateau d'impression de 680*680 mm

POINT** plateau(double x, double y) {
  int i;
  POINT** p;
  p = calloc(x, sizeof(*p));
  if (p == NULL) return NULL;
  else{
    for (i = 0; i < x; i++){
      p[i] = calloc(y, sizeof(**p));
      if (p[i] == NULL) {return NULL;}
    }
  }
  return p;
}

int inter_OM(POINT m_courant, POINT origine, POINT point_bord_1, POINT point_bord_2){
  // P1 et P2 sont dans le cadran positif
  if ( (point_bord_1.x <= origine.x) || (point_bord_2.x <= origine.x)
    || (point_bord_1.y <= origine.y) || (point_bord_2.y <= origine.y) ) {
      return 0;
    }

    //cas où M n'est pas dans le cadran x>0 et y>0
    //pas d'intérêt car il n'est pas à l'intérieur de l'objet, au mieux est-il à sa surface.
    if ( (m_courant.x <= origine.x) || (m_courant.y <= origine.y) ){
      return 0;
    }

  // pente de la droite (OM)
  double pente_M = (m_courant.y - origine.y) / (m_courant.x - origine.x);
  double pente_P1 = (point_bord_1.y - origine.y) / (point_bord_1.x - origine.x);
  double pente_P2 = (point_bord_2.y - origine.y) / (point_bord_2.x - origine.x);

  //cas où le bord considéré est parallèle à l'axe des ordonnées
  if (point_bord_1.x == point_bord_2.x){
    // M doit être au-delà du point d'abscisse minimum
    if ( minim(point_bord_1.x,point_bord_2.x) < m_courant.x){
      // M doit se trouver entre les droites (OP1) et (OP2)
      if ( (minim(pente_P1,pente_P2) <= pente_M) && (pente_M <= maxim(pente_P1,pente_P2)) ){
        return 1;
      }
      return 0;
    }
    return 0;
  }
  else {return 0;}
}

int nombre_inter_2par2(LISTE* perimetre, POINT m_courant, POINT origine){
  ELEMT* element_parcouru = perimetre->premier ;
  int compt = 0;
  // perimetre est supposé triée
  while(NULL != element_parcouru){
    if ( inter_OM(m_courant, element_parcouru->p, origine, element_parcouru->suivant->p) == 1 ){
      compt += 1;
    }
    element_parcouru = element_parcouru->suivant->suivant;
  }
  return compt;
}

int nombre_inter_triee(LISTE* perimetre, POINT m_courant, POINT origine){
  ELEMT* element_parcouru = perimetre->premier ;
  int compt = 0;
  // perimetre est supposé triée
  while(NULL != element_parcouru){
    if ( inter_OM(m_courant, origine, element_parcouru->p, element_parcouru->suivant->p) == 1 ){
      compt += 1;
    }
    element_parcouru = element_parcouru->suivant;
    // on évite de provoquer un segfault en étudiant à part le cas où element_parcouru est le dernier élément de la liste
    // on rattache le dernier élement au premier
    if ( (element_parcouru != NULL) && (element_parcouru->suivant == NULL) ){
      if ( inter_OM(m_courant, origine, element_parcouru->p, perimetre->premier->p) == 1 ){
        compt += 1;
      }
    }
  }
  return compt;
}

void destructeur(POINT** tab_plateau, double x_plateau){
  int i;
  for  ( i = 0; i < x_plateau ; i++) {free(tab_plateau[i]);}
  free(tab_plateau);
}

int dedans(LISTE* perimetre, POINT plateau_ij, POINT origine){
  if ( (nombre_inter_2par2(perimetre, plateau_ij, origine) % 2) == 0){
    return 0;
  }
  return 1;
}

// LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau, POINT origine){
//   int i,j;
//   POINT** tab_plateau = plateau(x_plateau,y_plateau);
//   LISTE* liste_interieur = initialisation();
//   VECTEUR vecteur;
//   for (i = 0; i < x_plateau; i++){
//     for (j = 0; j < y_plateau ; j++){
//       //Si le nombre d'intersection entre la surface de l'objet et [OM] est impaire, M est à l'intérieur de l'objet
//       if ( dedans(perimetre, tab_plateau[i][j], origine) == 1 ) {
//         push_head(liste_interieur, tab_plateau[i][j], vecteur);
//       }
//     }
//   }
//   destructeur(tab_plateau, x_plateau);
//   return liste_interieur;
// }
