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
    fl_color(FL_CYAN);

    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 45, 2, 40);// on trace les deux axes x et y
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 7, 40, 2);
    fl_polygon( X_ZONE + 2 , Y_ZONE + H_ZONE - 45, X_ZONE + 11, Y_ZONE + H_ZONE - 45, X_ZONE + 6 ,Y_ZONE + H_ZONE - 55);
    fl_draw( "y", X_ZONE + 15, Y_ZONE + H_ZONE - 40 );
    fl_polygon( X_ZONE + 45 , Y_ZONE + H_ZONE - 3, X_ZONE + 45, Y_ZONE + H_ZONE - 11, X_ZONE + 55 ,Y_ZONE + H_ZONE - 6);
    fl_draw( "x", X_ZONE + 45, Y_ZONE + H_ZONE - 15);

    TracerObjet2dCB();
}



void TracerObjet2dCB()
{
    //reinitialisation des listes
    efface( gDonnees.listePointIntersect ) ;
    efface (gDonnees.listeSurface) ;
    gDonnees.listePointIntersect = initialisation();
    gDonnees.listeSurface = initialisation();

    //calcul des nouvelles coordonnees
    gDonnees.listePointIntersect = intersect(gDonnees.donneesSTL, &(gDonnees.nbligne), gDonnees.hauteur,gDonnees.listePointIntersect, gDonnees.listeSurface);


    //tracer le maillage
    POINT_P p; /* definition du point d'origine pour calculer les intesrsections ( pas en (0,0) car pb si objet commence en (0,0)
                    et pb de pente infini si "trop pres" (= 1/2 pixel) d'un bord de l'objet)*/
    p.x = -10.0;
    p.y = 300.0;
    p.z = 0;
    int**maille = maillage_cadrillage( maillage(gDonnees.densiteMaillage,gDonnees.dimFil), gDonnees.listePointIntersect,p);
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

void tracerContour (LISTE * listePointIntersect)
{
    ELEMT* elemt1 = listePointIntersect->premier; // premier elmt de la liste de point
    ELEMT* elemtfin;//deuximeme elmt


    while (elemt1 != NULL)// parcours de tout les elmts de la liste
    {
        //on trace la ligne entre les deux points
        elemtfin = elemt1->suivant;
        TracerLigne(elemt1 , elemtfin);
        elemt1 = elemtfin->suivant;
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

    fl_line_style( FL_SOLID, 1);
    float rapportDecallage;
    rapportDecallage = 1/((vect.a*vect.a) + (vect.b*vect.b));

    int compteurContour = 0;
    while (compteurContour  < gDonnees.nbLignePerimetre*gDonnees.dimFil)
    {
        int decallagex =  compteurContour * rapportDecallage * vect.a;
        int decallagey =  compteurContour * rapportDecallage * vect.b;
        fl_line(X_ZONE + 30 + floor((*debut).p.x *gDonnees.rapportEchelle) - floor((decallagex + fabs(decallagex))/2) - ceil((decallagex - fabs(decallagex))/2),
                Y_ZONE + 10 + floor((*debut).p.y *gDonnees.rapportEchelle) - floor((decallagey + fabs(decallagey))/2) - ceil((decallagey - fabs(decallagey))/2) ,
                X_ZONE + 30 + floor((*fin).p.x *gDonnees.rapportEchelle) - floor((decallagex + fabs(decallagex))/2) - ceil((decallagex - fabs(decallagex))/2) ,
                Y_ZONE + 10 + floor((*fin).p.y *gDonnees.rapportEchelle) - floor((decallagey + fabs(decallagey))/2) - ceil((decallagey - fabs(decallagey))/2));
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
        fl_polygon(X_ZONE + 30 + floor(sommet1.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet1.y * gDonnees.rapportEchelle),
                   X_ZONE + 30 + floor(sommet2.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet2.y * gDonnees.rapportEchelle),
                   X_ZONE + 30 + floor(sommet3.x * gDonnees.rapportEchelle),Y_ZONE + 10 + floor(sommet3.y * gDonnees.rapportEchelle));
    }

}


void TracerMaillage(int ** maillage)
{
    int ligne = 0;
    int colonne = 0;
    fl_color(FL_BLACK); // change la couleur
    for (ligne = 0 ; ligne < 650; ligne++)
    {
        for (colonne = 0;colonne < 670 ; colonne++)
        {
                if (maillage[ligne][colonne] == 1)
                {
                    fl_point(ligne + 30 + X_ZONE, colonne + 10 + Y_ZONE);
                }

        }
    }
}

