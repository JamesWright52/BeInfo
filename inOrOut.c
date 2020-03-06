#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"
#include "inOrOut.h"

LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau){
  int i,j;
  POINT ** plat = plateau(x_plateau,y_plateau);
  LISTE* liste_interieur = initialisation();
  VECTEUR vecteur ={0,0,0};
  POINT m_courant;

  //scanf("%lf%lf", &x_plateau, &y_plateau);
  for (i=0; i < x_plateau; i++){
    for (j=0; j < y_plateau ; j++){
      m_courant = **plateau[i][j];
      if ( nombredinter(perimetre->premier)%2 == 0) {
        return 0;
      }
      else {
        //on ajoute le point M dans la liste des points intérieur pour le futur maillage
      }
    }
  }
}

      //if (IN(plat[i][j]) == 1){
        push_head(liste, plat[i][j],vecteur);
      }
  printListe(liste_interieur -> premier);

  destructeur(plat, 200);

}

// tableau 2D (matrice) avec tous les points du plateau
// plateau d'impression de 200*200 mm
// pas entre chaque point de 1 mm variable en fonction de la densité choisi par l'utilisateur

POINT** plateau(double x, double y) {
  int i,j;
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

void destructeur(int ** p, double x_plateau){
  int i;
  for  ( i = 0; i < x_plateau ; i++) {free(p[i])};
  free(p);
}


int xinter(POINT m_courant, POINT point_bord_1, POINT point_bord_2){
  double x_inter;
  double y_inter;
  //cas où M est sur l'axe des ordonnées (pas d'intérêt car il n'est pas à l'intérieur de l'objet)
  if(m_courant.x == 0){
    return 0;
  }

  double pente_m = m_courant.y/m_courant.x;
  //si le bord est parallèle à l'axe des ordonnées
  if (point_bord_1.x == point_bord_2.x){
    x_inter = point_bord_1.x;
  }
  else {
    double pente_seg = (point_bord_1.y - point_bord_2.y)/(point_bord_1.x - point_bord_2.x);
    //ordonnée à l'origine du bord
    ordonnee_bord = (point_bord_1.y - pente_seg*point_bord_1.x);
    // cas où OM n'est pas parallèle au bord (sinon le point n'est pas dans l'objet)
    if ( (pente_m - pente_seg) != 0 ) {
      //x_inter = ordonnee_bord/(pente_m - pente_seg);
      return 1;
    }
    else {return 0;}
  }

  //y_inter = x_inter * pente_m;
  //if ( (min(point_bord_1.y, point_bord_2.y) <= y_inter) && (y_inter <= max(point_bord_1.y, point_bord_2.y)) ){
  //return 1;
  }
  //else {return 0;}
//}

double nombredinter(LISTE* perimetre){
  ELEMT* element_parcouru = perimetre->premier ;
  int compt = 0;
  while(NULL != element_parcouru){
    if ( xinter(m_courant, element_parcouru->p, (element_parcouru->suivant->p) == 1 ){
      compt += 1;
    }
  }
  return compt;
}
