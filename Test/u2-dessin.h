// u2-dessin.h
// Sentinelle d'inclusion
#ifndef _u2_dessin_h
#define _u2_dessin_h
#include"u4-fonctions.h"

// Declaration des sous-programmes
void Clear ();
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data ) ;
void TracerObjet2dCB();
void tracerContour (LISTE * listePointIntersect);
void TracerLigne( ELEMT * debut , ELEMT * fin);
void TracerSurface ( LISTE * liste); /*permet de tracer une surface pleine entre les elements de la liste.
La liste doit etre composé de triangle (ensemble de droit points mis les uns après les autres).*/
void TracerMaillage(int ** maillage);

#endif // _u2_dessin_h
