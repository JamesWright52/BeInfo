#ifndef INOROUT_H
#define INOROUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"

POINT** plateau(double x, double y);

int xinter(POINT m_courant, POINT point_bord_1, POINT point_bord_2);

int nombre_inter_2par2(LISTE* perimetre, POINT m_courant, POINT origne);

int nombre_inter_triee(LISTE* perimetre, POINT m_courant,POINT origine);

void destructeur(POINT** p, double x_plateau);

int dedans(LISTE* perimetre, POINT plateau_ij, POINT origine);

LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau, POINT origine);


#endif
