// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
#include <math.h>
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
// Exemple d'evenement : clic souris
if ( Fl::event() == FL_PUSH ){
  printf( "Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y() );
}
}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ){
    // Definition des variables
    int Touche;
    // Recuperation de la touche clavier activee
    Touche = Fl::event_key();
    // Traitement de la touche
    switch (Touche){
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            break;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break;
    }
}

void BoutonQuitterCB(Fl_Widget* w, void* data){
    // Fin du programme
    exit(0);
}

void BoutonSTLCB(Fl_Widget* w, void* data){
    char* NomFichier;
    NomFichier = fl_file_chooser("Choisissez un fichier", "*.stl", NULL ) ;

    FILE * ftxt;
    ftxt = fopen(NomFichier, "rt");
    if (ftxt == NULL) {
        puts("Ouverture fichier texte impossible\n");
        fl_message("Ouverture du fichier Stl impossible");
    }
    else {
        gDonnees.fichierstl = ftxt;
        ReInitialiserDonnees();
        ActualiserInterface();
        gInterface.ZoneDessin->redraw() ;
    }
}

void BoutonMoinsH (Fl_Widget* w, void* data){
    float p = 1;
    int i = 0;
    for(i = 0; i < PRECISION; i++){
        p = p * 10;
    }
    gDonnees.hauteur = gDonnees.hauteur - 1/p;
    if (gDonnees.hauteur <= 0){
        gDonnees.hauteur = 0.0;
    }
    gInterface.CurseurHauteur->value(gDonnees.hauteur);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw();
}

void BoutonPlusH (Fl_Widget* w, void* data){
    float p = 1;
    for(int i = 0; i < PRECISION; i++){
        p = p * 10;
    }
    gDonnees.hauteur = gDonnees.hauteur + 1/p;
    if (gDonnees.hauteur >= gDonnees.Pmax.z){
        gDonnees.hauteur = gDonnees.Pmax.z;
    }
    gInterface.CurseurHauteur->value(gDonnees.hauteur);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw() ;
}

void CurseurCBhauteur ( Fl_Widget* w, void* data ){
    gDonnees.hauteur = gInterface.CurseurHauteur->value();
    ActualiserInterface();
    gInterface.ZoneDessin->redraw();
}


void MenuOptionsCB( Fl_Widget* w, void* data ){
    gDonnees.typeAffichage =  gInterface.MenuOptions->value();
}

void MenuOptionsFilCB( Fl_Widget* w, void* data ){
     gDonnees.dimFil =  1 + gInterface.MenuOptionsFil->value();
     ActualiserInterface();
     gInterface.ZoneDessin->redraw();
}


void ChampSaisieNumNbContour( Fl_Widget* w, void* data ){
    float nbContour;
    nbContour = gInterface.ChampSaisieNumNbContour->value() ;
    if (round(nbContour) == nbContour){
        if (nbContour > 0 && nbContour <= 10){
            gDonnees.nbLignePerimetre = nbContour;
            ActualiserInterface();
            gInterface.ZoneDessin->redraw() ;
        }
        else {
            fl_message("Rentrez un entier entre 1 et 10");
        }
    }
    else {
        fl_message("Rentrez un ENTIER");
    }
}


void BoutonMoinsD (Fl_Widget* w, void* data){
    float p = 1;
    int i = 0;
    for(i = 0; i < PRECISION + 1; i++){
        p = p * 10;
    }
    gDonnees.densiteMaillage = gDonnees.densiteMaillage - 1/p;
    if (gDonnees.densiteMaillage<=0){
        gDonnees.densiteMaillage = 0.0;
    }
    gInterface.CurseurDensite->value(gDonnees.densiteMaillage);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw();
}

void BoutonPlusD (Fl_Widget* w, void* data){
    float p = 1;
    for(int i = 0; i<PRECISION + 1; i++){
        p = p * 10;
    }
    gDonnees.densiteMaillage = gDonnees.densiteMaillage + 1/p;
    if (gDonnees.densiteMaillage >= 1.0){
        gDonnees.densiteMaillage = 1.0;
    }
    gInterface.CurseurDensite->value(gDonnees.densiteMaillage);
    ActualiserInterface();
    gInterface.ZoneDessin->redraw();
}

void CurseurCBDensite ( Fl_Widget* w, void* data ){
    gDonnees.densiteMaillage = gInterface.CurseurDensite->value();
    ActualiserInterface();
    gInterface.ZoneDessin->redraw() ;
}
