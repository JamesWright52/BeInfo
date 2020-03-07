#include <stdio.h>
#include <stdlib.h>
#include "inOrOut.h"
#include "maillage.h"
#include "listeSlicer.h"


//densité, type de maillage, dimension fixe du plateau

double** faux_main(){
  scanf("%d",&mail);
  if (mail == 1){   //1= rectiligne
    maillage  = motif_rectiligne();
  }
  else {
    maillage = motif_abeille();
  }
}


LISTE* motif_rectiligne(LISTE* perimetre, double densite, double epaisseur_fil, int nbr_couche,POINT minPoint, POINT maxPOINT){
  double pas = densite/epaisseur_fil;
  double abscisse = minPoint.x;
  LISTE* maillage= initialisation();
  ELEMT courant;
  if((perimetre->premier->p).z % (epaisseur_fil*nbr_couche) == 0){//verticale
    for (abscisse; abscisse < maxPoint.x; abscisse += pas*(maxPoint.x-minPoint.x)){
      for (ordonnee; ordonnee < maxPoint.y; ordonnee += (epaisseur_fil + nbr_couche)*(maxPoint.y-minPoint.y)){
        courant.p.x = abscisse;
        courant.p.y = ordonnee;
        if (dedans(perimetre, courant.p) == 1){
          push_head(maillage, courant.p, courant.vecteur);
        }
      }
    }
  }
  else{//horizontale
    for (ordonnee; ordonnee < maxPoint.y; ordonnee += pas*(maxPoint.y-minPoint.y)){
      for (abscisse; abscisse < maxPoint.x; abscisse += (epaisseur_fil + nbr_couche)*(maxPoint.x-minPoint.x)){
          courant.p.x = abscisse;
          courant.p.y = ordonnee;
          if (dedans(perimetre, courant.p) == 1){
            push_head(maillage, courant.p, courant.vecteur);
          }
        }
      }
    }
  }
  return maillage;
}


//   if (0.5 < densite &&  densite <= 1){
//     if (0.5 < densite && densite <= 0.75){
//       // 1 trait plein sur 3
//     }
//     else {
//       // 1 trait plein sur 2
//     }
//   }
//   else (0 <= densite && densite <= 0.5){
//     if (0 <= densite && densite <= 0.25){
//       // 1 trait plein sur 5
//
//     }
//     else {
//       // 1 trait plein sur 4
//
//     }
//   }
//
// }

double** motif_abeille(){
  double** maille
}
