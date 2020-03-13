#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "inOrOut.h"
#include "listeSlicer.h"

// Définition de la structure HEXAG = hexagone, avec les coordonnées du premier point en bas à gauche et sa dimension.
typedef struct hexagone {
	POINT bas_gauche;
  double cote;
} HEXAG ;

struct maillage{
  char rectiligne, abeille;
};
struct maillage mail;

double** faux_main();

// Renvoie la liste des points à tracer pour avoir un quadrillage rectiligne comme maillage.
LISTE* motif_rectiligne(LISTE* perimetre, double densite, double epaisseur_fil, POINT minPoint, POINT maxPoint, POINT origine);

// Permet de construire une liste avec les coordonnées de chaque point d'un hexagone.
LISTE* hexagone(double distance, POINT depart);

// Empile un nouvel hexagone au-dessus du précédent.
LISTE* empile_hexagone(LISTE* colonne, double distance);

// Crée une pile d'hexagone pour remplir verticalement l'intérieur de la pièce.
LISTE* colonne_hexagone(LISTE* colonne, int nbre_hexagones, double distance);

// Renvoie la liste des points à tracer pour avoir un maillage en nid d'abeille.
LISTE* maillage_nid_abeille(LISTE* perimetre, double densite, double epaisseur_fil, int nbr_couche,POINT minPoint, POINT maxPoint);

#endif
