// main.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // NULL
// Librairies fltk
#include <FL/Fl.H>      // fl::run
#include <FL/fl_draw.H>      // fl_push_clip et fl_pop_clip
// Programmes locaux
#include "main.h"
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Declaration des sous-programmes
void CycleCB( void* ) ;

// Programme Principal
int main (int argc, char ** argv){
    //Creation de l'interface
    CreerInterface() ;
    // Récupération d'un fichier stl vide pour avoir une interface initiale
    InitialiserDonnees() ;
    // Initialisation des curseurs de l'interface
    ReInitialiserDonnees();

    //Initialisation du logiciel
    ActualiserInterface(); // On affiche les donnees sur l'interface
    gInterface.ZoneDessin->redraw() ; // On redessine la zone de dessin

    // Armement de la fonction cyclique
    //Fl::add_timeout(DUREE_CYCLE, CycleCB, NULL ) ;

    // Lancer la boucle de gestion des evenements
    return Fl::run();
}

// Fonction cyclique
void CycleCB( void* )
{
    // Appel de la fonction TraiterCycleCB ( u3-callbacks )
    //TraiterCycleCB() ;

    // Rearmement de la fonction cyclique
    Fl::add_timeout(DUREE_CYCLE, CycleCB, NULL ) ;
}





///////////////////////////////////////////////////////////////////////////////////////////////
// Classe et methodes DrawingArea : a considerer comme une librairie fournie, NE PAS MODIFIER//
///////////////////////////////////////////////////////////////////////////////////////////////
DrawingArea::DrawingArea(int X,int Y,int W,int H)
: Fl_Widget(X,Y,W,H)
{
    _draw_callback_function = NULL ;
    _draw_callback_data = NULL ;

    _mouse_callback_function = NULL ;
    _mouse_callback_data = NULL ;

    _keyboard_callback_function = NULL ;
    _keyboard_callback_data = NULL ;
}

// Methode draw_callback
void DrawingArea::draw_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _draw_callback_function = Function ;
    _draw_callback_data = Data ;
}

// Methode mouse_callback
void DrawingArea::mouse_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _mouse_callback_function = Function ;
    _mouse_callback_data = Data ;
}

// Methode keyboard_callback
void DrawingArea::keyboard_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _keyboard_callback_function = Function ;
    _keyboard_callback_data = Data ;
}

// Methode de dessin de la zone de dessin
void DrawingArea::draw()
{
    fl_push_clip(this->x(), this->y(), this->w(), this->h()) ;
    if ( _draw_callback_function != NULL )
        (* _draw_callback_function ) ( this, _draw_callback_data ) ;
    fl_pop_clip() ;
}

// Methode de gestion des evenements dans la zone de dessin
int DrawingArea::handle(int event)
{
    switch(event)
    {
        case FL_PUSH :
        case FL_RELEASE :
        case FL_DRAG :
             if ( _mouse_callback_function != NULL )
                (* _mouse_callback_function ) ( this, _mouse_callback_data ) ;
            return 1 ;
            break ;
        case FL_ENTER :
            return 1 ;
            break ;
        case FL_MOVE :
             if ( _mouse_callback_function != NULL )
                (* _mouse_callback_function ) ( this, _mouse_callback_data ) ;
            return 1 ;
            break ;

        case FL_KEYBOARD:
             if ( _keyboard_callback_function != NULL )
                (* _keyboard_callback_function ) ( this, _keyboard_callback_data ) ;
            return 1 ;
            break ;

        case FL_FOCUS:
            return 1 ;
            break ;

        default:
            return Fl_Widget::handle(event);
    }
}

////////////////////////////////////////
// Fin classe et methodes DrawingArea //
////////////////////////////////////////
