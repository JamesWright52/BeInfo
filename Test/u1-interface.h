// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Output.H>

// Definition des constantes
#define X_ZONE  300    // X de la zone des paramètres (hors zone de dessin)
#define Y_ZONE  10     // Y de la zone des paramètres (hors zone de dessin)
#define L_ZONE  680    // Largeur de la zone de dessin
#define H_ZONE  680    // Hauteur de la zone de dessin
#define X_MAX  1000    // Largeur de la fenêtre graphique
#define Y_MAX  700     // Hauteur de la fenêtre graphique
#define DIM_INTERFACE 560
#define PRECISION 1    //Précision des curseurs de hauteur des surfaces et de densité du maillage

// Declaration des objets de l'interface
struct Interface {
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Button*          BoutonQuitter ;
    Fl_Button*          BoutonFichier ;
    Fl_Button*          BoutonPlusHauteur;
    Fl_Button*          BoutonMoinsHauteur;
    Fl_Button*          BoutonPlusDensite;
    Fl_Button*          BoutonMoinsDensite;
    Fl_Value_Slider*    CurseurHauteur ;
    Fl_Value_Slider*    CurseurDensite ;
    Fl_Choice*          MenuOptions ;
    Fl_Choice*          MenuOptionsFil ;
    Fl_Value_Input*     ChampSaisieNumNbContour;
    Fl_Output*          ChampTxt ;
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;


// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();

#endif // _u1_interface_h
