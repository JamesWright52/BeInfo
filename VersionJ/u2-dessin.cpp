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
    fl_color(FL_WHITE);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    fl_color(FL_GRAY);//on trace le quadrillage de la zone en gris
    int i;
    for (i = 0 ; 10*i< H_ZONE ; i++)
        {
        fl_rectf(X_ZONE, Y_ZONE + 10*i, L_ZONE , 1);
        }

    for (i = 0 ; 10*i< L_ZONE ; i++)
        {
        fl_rectf(X_ZONE + 10*i, Y_ZONE , 1 , H_ZONE);
    }
    fl_color(FL_BLACK);

    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 45, 3, 40);// on trace les deux axes x et y
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 8, 40, 3);
    fl_polygon( X_ZONE + 2 , Y_ZONE + H_ZONE - 45, X_ZONE + 11, Y_ZONE + H_ZONE - 45, X_ZONE + 6.5 ,Y_ZONE + H_ZONE - 55);
    fl_draw( "y", X_ZONE + 15, Y_ZONE + H_ZONE - 40 );
    fl_polygon( X_ZONE + 45 , Y_ZONE + H_ZONE - 3, X_ZONE + 45, Y_ZONE + H_ZONE - 11, X_ZONE + 55 ,Y_ZONE + H_ZONE - 6.5);
    fl_draw( "x", X_ZONE + 45, Y_ZONE + H_ZONE - 15);

    TracerObjet2dCB();

}



void TracerObjet2dCB()
{
    //reinitialisation des listes
    LISTE * liste;
    efface(gDonnees.listePointIntersect);
    efface(gDonnees.listeSurface);
    gDonnees.listePointIntersect = initialisation();
    gDonnees.listeSurface = initialisation();


    //calcul des nouvelles coordonnees
    liste = intersect(gDonnees.donneesSTL, &(gDonnees.nbligne), gDonnees.hauteur,gDonnees.listePointIntersect, gDonnees.listeSurface);

    liste = listeSansDoublon(liste);
    gDonnees.listePointIntersect = perimetre_Marche_Jarvis(liste,gDonnees.tailleObjet);
    printListe(liste->premier);
    printListe(gDonnees.listePointIntersect->premier);

    //trace la figure
    TracerSurface(gDonnees.listeSurface);
    tracerContour(gDonnees.listePointIntersect);
}

void tracerContour (LISTE * listePointIntersect)
{
    ELEMT* elemt1 = listePointIntersect->premier; // premier elmt de la liste de point
    ELEMT* elemtfin;//deuximeme elmt

    if (elemt1 != NULL){
        while (elemt1->suivant != NULL)// parcours de tout les elmts de la liste
        {
            //on trace la ligne entre les deux points
            elemtfin = elemt1->suivant;
            TracerLigne(elemt1 , elemtfin);
            elemt1 = elemtfin;
        }
    TracerLigne(elemt1,listePointIntersect->premier);
}
}

void TracerLigne( ELEMT * debut , ELEMT * fin)
{
    VECTEUR vect = (*debut).vecteur;

    VECTEUR vectorthogonal;
    float norme = sqrt(((*fin).p.y - (*debut).p.y) * ((*fin).p.y - (*debut).p.y) + ((*fin).p.x - (*debut).p.x) * ((*fin).p.x - (*debut).p.x));
    vectorthogonal.a = /*-(*debut).vecteur.b;*/ ((*fin).p.x - (*debut).p.x)/norme;
    vectorthogonal.b = /*(*debut).vecteur.a;*/ ((*fin).p.y - (*debut).p.y)/ norme;
    vectorthogonal.c = 0;

    fl_color(FL_BLACK);

    fl_line_style( FL_SOLID, floor(gDonnees.dimFil*gDonnees.rapportEchelle));
    float rapportDecallage;
    rapportDecallage = floor(gDonnees.dimFil / sqrt((vect.a)*(vect.a) + (vect.b)*(vect.b))*gDonnees.rapportEchelle/2);
    printfVecteur(vect);

    int compteurContour = 0;
    while (compteurContour  < gDonnees.nbLignePerimetre)
    {
        printf(" X = %f , 30 , xgrossit = %d , -2*cc*rd*vecta-vecta*rd = %d",X_ZONE , (*debut).p.x *gDonnees.rapportEchelle, - 2*compteurContour * rapportDecallage * (vect.a /*- vectorthogonal.a*/) ,- vect.a * rapportDecallage );
        printf("%d \n",X_ZONE + 30 + (*debut).p.x *gDonnees.rapportEchelle - 2*compteurContour * rapportDecallage * (vect.a /*- vectorthogonal.a*/) - vect.a * rapportDecallage);
        fl_line(X_ZONE + 30 + (*debut).p.x *gDonnees.rapportEchelle - 2*compteurContour * rapportDecallage * (vect.a /*- vectorthogonal.a*/) - vect.a * rapportDecallage ,
                Y_ZONE + 10 + (*debut).p.y *gDonnees.rapportEchelle - 2*compteurContour * rapportDecallage * (vect.b /*- vectorthogonal.b*/) - vect.b * rapportDecallage ,
                X_ZONE + 30 + (*fin).p.x *gDonnees.rapportEchelle - 2*compteurContour * rapportDecallage * (vect.a /*+ vectorthogonal.a*/) - vect.a * rapportDecallage ,
                Y_ZONE + 10 + (*fin).p.y *gDonnees.rapportEchelle - 2*compteurContour * rapportDecallage * (vect.b /*+ vectorthogonal.b*/) - vect.b * rapportDecallage );
        compteurContour = compteurContour + 1;
    }
}


void TracerSurface ( LISTE * liste)
{
    fl_color(FL_YELLOW);
    ELEMT * parcours = liste->premier; //elemt qui va parcourir les valeurs de la liste
    //initialisation des sommets à tracer
    POINT_P sommet1;
    POINT_P sommet2;
    POINT_P sommet3;

    while ( parcours != NULL)//tant que la liste n'est pas parcourue entierement on trace les surfaces
    {
        //on donne les valeurs au diiférents sommets
        sommet1 = (*parcours).p;
        parcours = parcours->suivant;
        sommet2 = (*parcours).p;
        parcours = parcours->suivant;
        sommet3 = (*parcours).p;
        parcours = parcours->suivant;
        //on trace la surface
        fl_polygon(X_ZONE + 30 + sommet1.x * gDonnees.rapportEchelle,Y_ZONE + 10 + sommet1.y * gDonnees.rapportEchelle,
                   X_ZONE + 30 + sommet2.x * gDonnees.rapportEchelle,Y_ZONE + 10 + sommet2.y * gDonnees.rapportEchelle,
                   X_ZONE + 30 + sommet3.x * gDonnees.rapportEchelle,Y_ZONE + 10 + sommet3.y * gDonnees.rapportEchelle);
    }

}
