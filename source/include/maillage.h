#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "inOrOut.h"
#include "listeSlicer.h"


struct maillage{
  char rectiligne, abeille;
};
struct maillage mail;

double** faux_main();

LISTE* motif_rectiligne(LISTE* perimetre, double densite, double epaisseur_fil, int nbr_couche,POINT minPoint, POINT maxPOINT);

double** motif_abeille();


#endif
