#ifndef INOROUT_H
#define INOROUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"

double minim(double P1, double P2);

double maxim(double P1, double P2);

POINT** plateau(double x, double y);

int inter_OM(POINT m_courant, POINT point_bord_1, POINT point_bord_2);

int nombredinter(LISTE* perimetre, POINT m_courant);

void destructeur(POINT** p, double x_plateau);

int dedans(LISTE* perimetre, POINT** tab_plateau);

LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau);


#endif
