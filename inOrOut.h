#ifndef INOROUT_H
#define INOROUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listeSlicer.h"

LISTE* liste_interieur(LISTE* perimetre, double x_plateau, double y_plateau);

double ** plateau(double x, double y);

void destructeur(int ** p, double x_plateau);

int xinter(POINT m_courant, POINT point_bord_1, POINT point_bord_2);

double nombredinter(LISTE* perimetre);


#endif
