#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "inOrOut.h"
#include "listeSlicer.h"

typedef struct hexagone {
	POINT bas_gauche;
  double cote;
} HEXAG ;

struct maillage{
  char rectiligne, abeille;
};
struct maillage mail;

double** faux_main();

LISTE* motif_rectiligne(LISTE* perimetre, double densite, double epaisseur_fil, POINT minPoint, POINT maxPoint, POINT origine);

LISTE* hexagone(double distance, POINT depart);

LISTE* empile_hexagone(LISTE* colonne, double distance);

LISTE* colonne_hexagone(LISTE* colonne, int nbre_hexagones, double distance);

LISTE* maillage_nid_abeille(LISTE* perimetre, double densite, double epaisseur_fil, int nbr_couche,POINT minPoint, POINT maxPoint);

#endif
