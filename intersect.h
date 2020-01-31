#include <stdio.h>
#include <stdlib.h>


typedef struct {double x; double y; double z;} POINT;

typedef struct {double a; double b; double c;} VECTEUR;

typedef struct {POINT p1; POINT p2; POINT p3; VECTEUR vecteur;} TRIANGLE;

//fonction qui prends une matrice de coordonnees et une côte en argument
//renvoie la liste des points d'intersections entre le plan z et l'objet
//(format [[P1,P2,P3],...,[P3n,,P3n+1,P3n+2]])
POINT** intersect(TRIANGLE* matrice, int* pnligne, double cote);

double min(double z1, double z2, double z3);

double max(double z1, double z2, double z3);

//renvoie 1 si le segment entre z1 et z2 intersecte le plan
int segment_intersecte(double cote,double z1, double z2);

POINT* perimetre_Marche_Jarvis(POINT** liste_surface_z,int* pnligne);
