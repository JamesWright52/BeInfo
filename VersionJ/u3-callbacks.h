// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;

void BoutonPlusH (Fl_Widget* w, void* data);
void BoutonMoinsH (Fl_Widget* w, void* data);
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void BoutonSTLCB(Fl_Widget* w, void* data);

void CurseurCBhauteur ( Fl_Widget* w, void* data );

void MenuOptionsCB( Fl_Widget* w, void* data );
void ChampSaisieNumDimFilCB( Fl_Widget* w, void* data );
void ChampSaisieNumNbContour( Fl_Widget* w, void* data );



#endif // _u3_callbacks_h
