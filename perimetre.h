#ifndef PERIMETRE_H
#define PERIMETRE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "listeSlicer.h"
#include "intersect.h"
#include <math.h>

//cherche l'élément suivant le point p0 sur le périmètre dans le sens des aiguilles d'une montre pour un périmètre convexe
//renvoie l'élément suivant et donne à theta la valeur de l'angle (Oy, (p0,psuivant))
ELEMT* chercheElemSuivant(LISTE* liste_surface_z, LISTE* perimetre, POINT p0, double* ptheta );

//prend en argument une liste de point d'une même surface de hauteur z et renvoie une liste de ces mêmes points triés dans
//l'ordre de parcourt du périmètre de cette surface
LISTE* perimetre_Marche_Jarvis(LISTE* liste_surface_z);

#endif
