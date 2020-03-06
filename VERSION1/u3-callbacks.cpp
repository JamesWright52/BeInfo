// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// TraiterCycle
void TraiterCycleCB()
{
    // Trace pour bien montrer que la fonction est appelee cycliquement
    // printf(""Appel de TraiterCycleCB");

    // Traitements cycliques a placer ici :
    // ...

    // On redessine la zone

    // Code a activer en cas de probleme pour saisir les evenements du clavier
    // Probleme : si les evenements du clavier ne sont pas bien pris en compte pour agir sur la zone de dessin.
    // Solution : On ramene systematiquement le focus des evenements sur la zone de dessin
    // Attention, cela peut perturber certains elements d'interface comme des champs de saisie texte ou numerique

    // Fl::focus(gInterface.ZoneDessin);

    // Fin code a activer en cas de probleme
}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    // Exemple d'evenement : clic souris
    if ( Fl::event() == FL_PUSH )
    {
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());

        // Actions suite a un clic souris a placer ici :
        // ...

    }

}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data )
{
    // Definition des variables
    int Touche ;

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
    }
}

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    // Fin du programme
    freeTriangle(gDonnees.donneesSTL);
    exit(0) ;
}

void BoutonSTLCB(Fl_Widget* w, void* data)
{
    const char* NomFichier ;
    NomFichier = fl_file_chooser("Choisissez un fichier", "*.stl", NULL ) ;

}

void BoutonMoinsH (Fl_Widget* w, void* data)
{
    float p = 1;
    int i = 0;
    for(i = 0; i < PRECISION; i++)
    {
        p = p * 10;
    }
    gDonnees.hauteur = gDonnees.hauteur - 1/p;
    gInterface.CurseurHauteur->value(gDonnees.hauteur);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw() ;
}

void BoutonPlusH (Fl_Widget* w, void* data)
{
    float p = 1;
    for(int i = 0; i<PRECISION; i++)
    {
        p = p * 10;
    }
    gDonnees.hauteur = gDonnees.hauteur + 1/p;
    gInterface.CurseurHauteur->value(gDonnees.hauteur);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw() ;
}

void CurseurCBhauteur ( Fl_Widget* w, void* data )
{
    gDonnees.hauteur = gInterface.CurseurHauteur->value() ;
    ActualiserInterface();
    gInterface.ZoneDessin->redraw() ;
}


void MenuOptionsCB( Fl_Widget* w, void* data )
{
    gDonnees.typeAffichage =  gInterface.MenuOptions->value() ;
}

void ChampSaisieNumDimFilCB( Fl_Widget* w, void* data )
{
     gDonnees.dimFil =  gInterface.ChampSaisieNumDimFil->value() ;
     ActualiserInterface();
     gInterface.ZoneDessin->redraw() ;
}


void ChampSaisieNumNbContour( Fl_Widget* w, void* data )
{
     gDonnees.nbLignePerimetre =  gInterface.ChampSaisieNumNbContour->value() ;
     ActualiserInterface();
     gInterface.ZoneDessin->redraw() ;
}
