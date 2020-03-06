// u1-interface.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface ;

// CreerInterface
void CreerInterface()
{
    // Creation de la fenetre principale
    gInterface.Fenetre = new Fl_Double_Window(X_MAX,Y_MAX);
    gInterface.Fenetre->label("3D Printer") ;
    gInterface.Fenetre->begin() ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    //Bouton curseur
    //gInterface.ChampTxt->color( FL_BLUE) ;
    gInterface.ChampTxt = new Fl_Output( 25, 290, 100, 30, "") ;
    gInterface.ChampTxt->value( "Hauteur (cm)" ) ;
    gInterface.CurseurHauteur = new Fl_Value_Slider( 150, 290, 130, 30, "") ;
    gInterface.CurseurHauteur->type( FL_HORIZONTAL ) ;
    gInterface.CurseurHauteur->align( FL_ALIGN_LEFT ) ;
    gInterface.CurseurHauteur->callback( CurseurCBhauteur, NULL ) ;
    gInterface.CurseurHauteur->precision(PRECISION);
    gInterface.BoutonPlusHauteur = new Fl_Button(280, 290, 15, 15, "+") ;
    gInterface.BoutonPlusHauteur->callback( BoutonPlusH, NULL ) ;
    gInterface.BoutonMoinsHauteur = new Fl_Button(280, 306, 15, 15, "-") ;
    gInterface.BoutonMoinsHauteur->callback( BoutonMoinsH, NULL ) ;

    //Bouton curseur
    gInterface.ChampTxt = new Fl_Output( 25, 330, 115, 30, "") ;
    gInterface.ChampTxt->value( "Densite Maillage" ) ;
    gInterface.CurseurDensite = new Fl_Value_Slider( 150, 330, 130, 30, "") ;
    gInterface.CurseurDensite->type( FL_HORIZONTAL ) ;
    gInterface.CurseurDensite->align( FL_ALIGN_LEFT ) ;
    gInterface.CurseurDensite->callback( CurseurCBhauteur, NULL ) ;
    gInterface.CurseurDensite->bounds( 0, 1) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(100, Y_MAX - 40, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation du bouton choix fichier stl
    gInterface.BoutonFichier = new Fl_Button(75, 20, 150, 20, "Choix du fihier") ;
    gInterface.BoutonFichier->callback( BoutonSTLCB, NULL ) ;


    // Choix multiple type d'interface
    gInterface.ChampTxt = new Fl_Output( 25, 200, 75, 20, "") ;
    gInterface.ChampTxt->value( "Affichage" ) ;
    gInterface.MenuOptions = new Fl_Choice( 150, 200, 100, 20, "") ;
    gInterface.MenuOptions->add( "Item1", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item2", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item3", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item4", "", MenuOptionsCB ) ;

    // Choix multiple type d'interface
    gInterface.ChampTxt = new Fl_Output( 25, 230, 75, 20, "") ;
    gInterface.ChampTxt->value( "Maillage" ) ;
    gInterface.MenuOptions = new Fl_Choice( 150, 230, 100, 20, "") ;
    gInterface.MenuOptions->add( "Item1", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item2", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item3", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item4", "", MenuOptionsCB ) ;

    // Saisi taille du fil
    gInterface.ChampTxt = new Fl_Output( 25, 400, 100, 20, "") ;
    gInterface.ChampTxt->value( "Diametre fil" ) ;
    gInterface.ChampSaisieNumDimFil = new Fl_Value_Input( 150, 400, 100, 20, "" ) ;
    gInterface.ChampSaisieNumDimFil->when( FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED ) ;
    gInterface.ChampSaisieNumDimFil->callback(ChampSaisieNumDimFilCB, NULL) ;

    // Saisi nb de ligne de perimetre
    gInterface.ChampTxt = new Fl_Output( 25, 260, 115, 20, "") ;
    gInterface.ChampTxt->value( "Nombre Contour" ) ;
    gInterface.ChampSaisieNumNbContour = new Fl_Value_Input(150, 260, 100, 20, "" ) ;
    gInterface.ChampSaisieNumNbContour->when( FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED ) ;
    gInterface.ChampSaisieNumNbContour->callback(ChampSaisieNumNbContour, NULL) ;

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{

}
