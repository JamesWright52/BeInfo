#include <stdio.h>
#include <stdlib.h>
#include "inOrOut.h"
#include "maillage.h"
#include "listeSlicer.h"


//densité, type de maillage, dimension fixe du plateau

// double** faux_main(){
//   char* type;
//   scanf("%s",type);
//   if (type == ){   //1= rectiligne
//     maillage  = motif_rectiligne();
//   }
//   else {
//     maillage = motif_abeille();
//   }
// }


LISTE* motif_rectiligne(LISTE* perimetre, double densite, double epaisseur_fil, POINT minPoint, POINT maxPoint, POINT origine){
  // longueur de l'objet
  double longueur = maxPoint.x - minPoint.x;
  // largeur de l'objet
  double largeur = maxPoint.y - minPoint.y;
  // Maillage carré => pas = Longueur / nombre de ligne sur la longueur = largeur / nombre de ligne sur la largeur .
  // Les nombres de lignes sont calculés à partir de la densié, de l'épaisseur du fil, de la longuer et la largeur de l'objet
  // densité = d
  // L = longueur
  // l = largeur
  // NL = nombre de ligne sur la longueur
  // Nl = nombre de ligne sur la largeur
  // ep = épaisseur du fil
  // d = ( (NL/l) + (Nl/L) )*ep
  // pas = (l² + L²)*ep / (d*l*L)
  double pas = (largeur*largeur + longueur*longueur) * epaisseur_fil / ( densite * largeur * longueur );
  double nbr_ligne_longueur = longueur / pas;
  double nbr_ligne_largeur = largeur / pas;
  double abscisse;
  double ordonnee;
  LISTE* maillage = initialisation();
  int i,j;
  ELEMT courant;
  for (i=0; i < nbr_ligne_longueur; i++){
    abscisse = minPoint.x + i*pas;
    for (j = 0; j < nbr_ligne_largeur; j++){
      ordonnee = minPoint.y + j*pas;
      courant.p.x = abscisse;
      courant.p.y = ordonnee;
      // attention "dedans" ne marche que pour une liste perimetre trié dans l'ordre, donc à virer si besoin.
      if (dedans(perimetre, courant.p, origine) == 1){
        push_head(maillage, courant.p, courant.vecteur);
      }
    }
  }
  return maillage;
}

LISTE* hexagone(double distance, POINT depart){
  LISTE* hexagone = initialisation();
  POINT p = depart;
  VECTEUR vecteur;
  push_head(hexagone, p, vecteur);
  p.x = p.x + distance;
  push_head(hexagone, p, vecteur);
  p.x = p.x + distance / 2;
  p.y = p.y + distance / 2;
  push_head(hexagone, p, vecteur);
  p.x = p.x - distance / 2;
  p.y = p.y + distance / 2;
  push_head(hexagone, p, vecteur);
  p.x = p.x - distance;
  push_head(hexagone, p, vecteur);
  p.x = p.x - distance / 2;
  p.y = p.y - distance / 2;
  push_head(hexagone, p, vecteur);
  return hexagone;
}

LISTE* empile_hexagone(LISTE* colonne, double distance){
  POINT p_hexagone = colonne->premier->p;
  p_hexagone.x = p_hexagone.x + distance / 2;
  p_hexagone.y = p_hexagone.y + distance / 2;
  LISTE* hexagone_nouveau = hexagone(distance, p_hexagone);
  concatene_liste(colonne, hexagone_nouveau);
  colonne = listeSansDoublon(colonne);
  return colonne;
}

LISTE* colonne_hexagone(LISTE* colonne, int nbre_hexagones, double distance){
  int i;
  for (i = 0; i < nbre_hexagones; i++){
    colonne = empile_hexagone(colonne, distance);
  }
  return colonne;
}

// LISTE* maillage_nid_abeille(LISTE* perimetre, double densite, double epaisseur_fil, int nbr_couche,POINT minPoint, POINT maxPoint){
//   LISTE* maillage = initialisation();
//   maillage =
//   // renvoie la liste du mailage des nids d'abeille
//   // on va concaténer des listes de colonne d'hexagone
//   return maillage;
// }
