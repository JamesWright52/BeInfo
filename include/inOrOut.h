#ifndef INOROUT_H
#define INOROUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"

// déclaration des fonctions pour inOrOut.c

// création d'un tableau de pixel représentant le plateau d'impression.
POINT** plateau(double x, double y);

// permet de calculer l'abscisse du point d'intersection entre le segment [origine_point courant] et un segment constituant un bord de la pièce.
int xinter(POINT m_courant, POINT point_bord_1, POINT point_bord_2);

// permet de compter le nombre d'intersection entre l'origine_point courant et tous les bords de la pièce, lorsque les points du bord sont 2 par 2.
int nombre_inter_2par2(LISTE* perimetre, POINT m_courant, POINT origne);

// permet de compter le nombre d'intersection entre l'origine_point courant et tous les bords de la pièce, lorsque les points du bords sont triés dans l'ordre du parcours de la pièce.
int nombre_inter_triee(LISTE* perimetre, POINT m_courant,POINT origine);

// vide la mémoire allouée à un tableau de points.
void destructeur(POINT** p, double x_plateau);

// teste tous les points du plateau d'impression pour déterminer si ils sont à l'intérieur ou à l'extérieur de la pièce.
int dedans(LISTE* perimetre, POINT plateau_ij, POINT origine);

// mets les points internes à l'objet dans une liste
LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau, POINT origine);


#endif
