// u2-dessin.h
// Sentinelle d'inclusion
#ifndef _u2_dessin_h
#define _u2_dessin_h
#include"u4-fonctions.h"

#define L_OBJET  650
#define H_OBJET  670

// Declaration des sous-programmes
void Clear ();

void ZoneDessinDessinerCB( Fl_Widget* widget, void* data ) ;

void TracerObjet2dCB();

void tracerContour (LISTE * listePointIntersect);

void TracerLigne( ELEMT * debut , ELEMT * fin);

/*permet de tracer une surface pleine entre les elements de la liste.
La liste doit etre composé de triangle (trois points et un vecteur).*/
void TracerSurface ( LISTE * liste);

void TracerMaillage(int ** maillage);

#endif // _u2_dessin_h
