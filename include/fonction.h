#ifndef STL_H
#define STL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Définition de la structure POINT avec les coordonnées x, y et z.
typedef struct
{
  double x;
  double y;
  double z;
} POINT;

// Définition de la structure VECTEUR.
typedef struct
{
  double a;
  double b;
  double c;
} VECTEUR;


typedef struct
{
  VECTEUR vecteur;
  POINT p1;
  POINT p2;
  POINT p3;
} TRIANGLE;

TRIANGLE * alloueTriangle(int n);
void nombreTriangle(FILE* ftxt, int * pnbligne);
void affiche(TRIANGLE * adresse, int * pnbligne);;
void printfTriangle(TRIANGLE elmt);
POINT maxPointTableau( TRIANGLE * adresse , int * pnbligne);
POINT minPointTableau( TRIANGLE * adresse , int * pnbligne);
double longueur_max_objet(TRIANGLE * adresse , int * pnbligne);
void extractionDonneeFichierSTL (FILE* ftxt, TRIANGLE * adresse);
void printfPoint ( POINT point);
void freeTriangle ( TRIANGLE * adresse);
void tareTableau (TRIANGLE * adresse , int * pnbligne, POINT Pmin);

#endif
