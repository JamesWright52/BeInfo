// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>      // cin, cout, ...
#include <math.h>
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;


// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_WHITE);  //fond de la zone de dessin en blanc
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE); //affichage de la zone de dessin

    //on trace le cadrillage de la zone de dessin en gris
    fl_color(FL_GRAY);
    int i;
    //on trace les lignes du cadrillage
    for (i = 0 ; 10*i< H_ZONE ; i++)
        {
        fl_rectf(X_ZONE, Y_ZONE + 10*i, L_ZONE , 1);
        }
    //on trace les colonnes du cadrillage
    for (i = 0 ; 10*i< L_ZONE ; i++)
        {
        fl_rectf(X_ZONE + 10*i, Y_ZONE , 1 , H_ZONE);
    }

    // on trace les axes x et y
    fl_color(FL_CYAN);
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 45, 2, 40);
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 7, 40, 2);
    fl_polygon( X_ZONE + 2 , Y_ZONE + H_ZONE - 45, X_ZONE + 11, Y_ZONE + H_ZONE - 45, X_ZONE + 6 ,Y_ZONE + H_ZONE - 55); //flèche ordonnée
    fl_draw( "y", X_ZONE + 15, Y_ZONE + H_ZONE - 40 );
    fl_polygon( X_ZONE + 45 , Y_ZONE + H_ZONE - 3, X_ZONE + 45, Y_ZONE + H_ZONE - 11, X_ZONE + 55 ,Y_ZONE + H_ZONE - 6); //flèche abscisse
    fl_draw( "x", X_ZONE + 45, Y_ZONE + H_ZONE - 15);

    TracerObjet2dCB();
}

void TracerObjet2dCB(){
    //reinitialisation des listes
    efface( gDonnees.listePointIntersect ) ;
    efface (gDonnees.listeSurface) ;
    gDonnees.listePointIntersect = initialisation();
    gDonnees.listeSurface = initialisation();

    //calcul des nouvelles coordonnees
    gDonnees.listePointIntersect = intersect(gDonnees.donneesSTL, &(gDonnees.nbligne), gDonnees.hauteur,gDonnees.listePointIntersect, gDonnees.listeSurface);
    ELEMT* suivant = (gDonnees.listePointIntersect)->premier;
    // redimensionnement de l'objet par rapport à la fenêtre graphique
    while(suivant != NULL){
      suivant->p.x = suivant->p.x * gDonnees.rapportEchelle;
      suivant->p.y = suivant->p.y * gDonnees.rapportEchelle;
      suivant->p.z = suivant->p.z * gDonnees.rapportEchelle;
      suivant = suivant->suivant;
    }

    //tracer le maillage
    // definition du point de référence pour calculer les intersections.
    //il doit se trouver hors de l'objet (dont tous les points sont dans le cadran x/y positifs ou nuls)
    POINT_P reference;
    reference.x = -1;
    reference.y = -1;
    reference.z = -1;

    int**maille = maillage_interieur( maillage(gDonnees.densiteMaillage,gDonnees.dimFil), gDonnees.listePointIntersect,reference);
    TracerMaillage(maille);

    //trace la figure
    TracerSurface(gDonnees.listeSurface);
    tracerContour(gDonnees.listePointIntersect);

    /*fl_color(FL_RED);
    fl_pie(-10 + X_ZONE +30 , 300 + Y_ZONE + 10, 3 , 3 , 0 , 360 );
    POINT_P ptest;
    ptest.x = 394-X_ZONE - 30;
    ptest.y = 60-Y_ZONE -10;
    ptest.z = 0;
    fl_pie(ptest.x + X_ZONE + 30,ptest.y + Y_ZONE + 10, 3 , 3 , 0 , 360 );
    POINT_P orig;
    orig.x = -10;
    orig.y = 300;
    orig.z = 0;
    int nbIntersect = dedans(gDonnees.listePointIntersect,ptest,orig);
    printf("nbintersction = %d\n", nbIntersect);*/
}

void tracerContour (LISTE * listePointIntersect){
    ELEMT* elemt1 = listePointIntersect->premier; // premier elmt de la liste de point
    ELEMT* elemtfin;//deuximeme elmt
    // parcours de tout les elmts de la liste
    while (elemt1 != NULL){
        //on trace la ligne entre les deux points
        elemtfin = elemt1->suivant;
        TracerLigne(elemt1 , elemtfin);
        elemt1 = elemtfin->suivant;
    }
}

void TracerLigne( ELEMT * debut , ELEMT * fin ){
    VECTEUR vect = debut->vecteur;
    float norme = sqrt( (fin->p.y - debut->p.y) * (fin->p.y - debut->p.y) + (fin->p.x - debut->p.x) * (fin->p.x - debut->p.x));
    fl_color(FL_BLACK);
    fl_line_style(FL_SOLID, 1);
    float rapportDecallage;
    rapportDecallage = 1/((vect.a*vect.a) + (vect.b*vect.b));

    int compteurContour = 0;
    while (compteurContour  < gDonnees.nbLignePerimetre*gDonnees.dimFil){
        int decallagex =  compteurContour * rapportDecallage * vect.a;
        int decallagey =  compteurContour * rapportDecallage * vect.b;
        fl_line(X_ZONE + 30 + floor(debut->p.x) - floor((decallagex + fabs(decallagex))/2) - ceil((decallagex - fabs(decallagex))/2),
                Y_ZONE + 10 + floor(debut->p.y) - floor((decallagey + fabs(decallagey))/2) - ceil((decallagey - fabs(decallagey))/2) ,
                X_ZONE + 30 + floor(fin->p.x) - floor((decallagex + fabs(decallagex))/2) - ceil((decallagex - fabs(decallagex))/2) ,
                Y_ZONE + 10 + floor(fin->p.y) - floor((decallagey + fabs(decallagey))/2) - ceil((decallagey - fabs(decallagey))/2));
        compteurContour = compteurContour + 1;
    }
}

void TracerSurface ( LISTE * liste)
{
    fl_color(FL_BLUE);
    ELEMT * parcours = liste->premier; //elemt qui va parcourir les valeurs de la liste
    //initialisation des sommets � tracer
    POINT_P sommet1;
    POINT_P sommet2;
    POINT_P sommet3;

    //tant que la liste n'est pas parcourue entierement on trace les surfaces
    while (parcours != NULL){
        //on donne les valeurs au différents sommets
        sommet1 = parcours->p;
        parcours = parcours->suivant;
        sommet2 = parcours->p;
        parcours = parcours->suivant;
        sommet3 = parcours->p;
        parcours = parcours->suivant;
        //on trace la surface
        fl_polygon(X_ZONE + 30 + floor(sommet1.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet1.y * gDonnees.rapportEchelle),
                   X_ZONE + 30 + floor(sommet2.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet2.y * gDonnees.rapportEchelle),
                   X_ZONE + 30 + floor(sommet3.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet3.y * gDonnees.rapportEchelle));
    }
}

void TracerMaillage(int ** maillage){
    int ligne = 0;
    int colonne = 0;
    fl_color(FL_BLACK); // change la couleur
    for (ligne = 0 ; ligne < L_OBJET; ligne++){
        for (colonne = 0;colonne < H_OBJET; colonne++){
                if (maillage[ligne][colonne] == 1){
                    fl_point(ligne + 30 + X_ZONE, colonne + 10 + Y_ZONE);
                }
        }
    }
}
