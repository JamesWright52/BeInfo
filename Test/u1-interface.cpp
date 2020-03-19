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
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    //Bouton curseur
    gInterface.ChampTxt = new Fl_Output( 15, 290, 130, 30, "") ; //position et taille de la zone de texte
    gInterface.ChampTxt->value( "    Hauteur (cm)" ) ; //remplissage de la zone de texte
    gInterface.CurseurHauteur = new Fl_Value_Slider( 150, 290, 130, 30, "") ;//placement du curseur
    gInterface.CurseurHauteur->type( FL_HORIZONTAL ) ;
    gInterface.CurseurHauteur->align( FL_ALIGN_LEFT ) ;
    gInterface.CurseurHauteur->callback( CurseurCBhauteur, NULL ) ;//association avec la fonction
    gInterface.CurseurHauteur->precision(PRECISION);              //gestion de la précision du curseur
    gInterface.BoutonPlusHauteur = new Fl_Button(280, 290, 15, 15, "+") ;//petit bouton qui permet d'augmenter finnement la hauteur
    gInterface.BoutonPlusHauteur->callback( BoutonPlusH, NULL ) ;
    gInterface.BoutonMoinsHauteur = new Fl_Button(280, 306, 15, 15, "-") ;//petit bouton qui permet de diminuer finnement la hauteur
    gInterface.BoutonMoinsHauteur->callback( BoutonMoinsH, NULL ) ;

    //Bouton curseur
    gInterface.ChampTxt = new Fl_Output( 15, 330, 130, 30, "") ;
    gInterface.ChampTxt->value( " Densite Maillage" ) ;
    gInterface.CurseurDensite = new Fl_Value_Slider( 150, 330, 130, 30, "") ;
    gInterface.CurseurDensite->type( FL_HORIZONTAL ) ;
    gInterface.CurseurDensite->align( FL_ALIGN_LEFT ) ;
    gInterface.CurseurDensite->callback( CurseurCBDensite, NULL ) ;
    gInterface.CurseurDensite->precision(PRECISION);
    gInterface.CurseurDensite->bounds( 0, 1) ;
    gInterface.BoutonPlusDensite = new Fl_Button(280, 330, 15, 15, "+") ;//petit bouton qui permet d'augmenter finnement la hauteur
    gInterface.BoutonPlusDensite->callback( BoutonPlusD, NULL ) ;
    gInterface.BoutonMoinsDensite = new Fl_Button(280, 346, 15, 15, "-") ;//petit bouton qui permet de diminuer finnement la hauteur
    gInterface.BoutonMoinsDensite->callback( BoutonMoinsD, NULL ) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(100, Y_MAX - 40, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation du bouton choix fichier stl
    gInterface.BoutonFichier = new Fl_Button(75, 20, 150, 20, "Choix du fichier") ;
    gInterface.BoutonFichier->callback( BoutonSTLCB, NULL ) ;

    // Choix multiple type d'interface
    gInterface.ChampTxt = new Fl_Output( 15, 200, 130, 20, "") ;
    gInterface.ChampTxt->value( "        Affichage" ) ;
    gInterface.MenuOptions = new Fl_Choice( 150, 200, 100, 20, "") ;
    gInterface.MenuOptions->add( "Item1", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item2", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item3", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Item4", "", MenuOptionsCB ) ;

    // Choix multiple type d'interface
    gInterface.ChampTxt = new Fl_Output( 15, 230, 130, 20, "") ;
    gInterface.ChampTxt->value( "        Maillage" ) ;
    gInterface.MenuOptions = new Fl_Choice( 150, 230, 100, 20, "") ;
    gInterface.MenuOptions->add( "Filet", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Nid d'abeille", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Cercle", "", MenuOptionsCB ) ;
    gInterface.MenuOptions->add( "Zigzag", "", MenuOptionsCB ) ;

    // Saisi taille du fil
    gInterface.ChampTxt = new Fl_Output( 15, 400, 130, 20, "") ;
    gInterface.ChampTxt->value( "Diametre fil" ) ;
    gInterface.MenuOptionsFil = new Fl_Choice( 150, 400, 100, 20, "") ;
    gInterface.MenuOptionsFil->add( "0.4mm", "", MenuOptionsFilCB ) ;
    gInterface.MenuOptionsFil->add( "0.8mm", "", MenuOptionsFilCB ) ;
    gInterface.MenuOptionsFil->add( "1.2mm", "", MenuOptionsFilCB ) ;
    gInterface.MenuOptionsFil->add( "1.5mm", "", MenuOptionsFilCB ) ;

    // Saisi nb de ligne de perimetre
    gInterface.ChampTxt = new Fl_Output( 15, 260, 130, 20, "") ;
    gInterface.ChampTxt->value( "Nombre Contours" ) ;
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
