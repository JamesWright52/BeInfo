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

    //on trace le quadrillage de la zone en gris
    fl_color(FL_GRAY);
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

    // on trace les deux axes x et y
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 45, 2, 40);
    fl_rectf(X_ZONE + 5, Y_ZONE + H_ZONE - 7, 40, 2);
    fl_polygon( X_ZONE + 2 , Y_ZONE + H_ZONE - 45, X_ZONE + 11, Y_ZONE + H_ZONE - 45, X_ZONE + 6 ,Y_ZONE + H_ZONE - 55);
    fl_draw( "y", X_ZONE + 15, Y_ZONE + H_ZONE - 40 );
    fl_polygon( X_ZONE + 45 , Y_ZONE + H_ZONE - 3, X_ZONE + 45, Y_ZONE + H_ZONE - 11, X_ZONE + 55 ,Y_ZONE + H_ZONE - 6);
    fl_draw( "x", X_ZONE + 45, Y_ZONE + H_ZONE - 15);

    //On appelle la fonction qui trace l'objet
    /*gDonnees.typeAffichage = -2 si l'objet à tracer est vide
                             = -1 si il faut tout recalculer car on vient de changer d'objet
                             = 0 si on change la hauteur ( il faut quasi tout recalculer sauf le motif de la maille initial)
                             = 2 si on change la densité de maillage : seul la maille doit etre recalculer
                             = 1 si l'epaisseur des bords de l'objet est modifié : rien est à recalculer
                             */
    if (gDonnees.typeAffichage != -2)
    {
        TracerObjet2dCB();
    }
}



void TracerObjet2dCB()
{
    if (gDonnees.typeAffichage <= 0)
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
    int**maille = gDonnees.maille;

    if ( gDonnees.typeAffichage == -1)
    {
        gDonnees.maille = maillage(gDonnees.densiteMaillage,1);
    }
    // On calcul puis on trace le maillage.
    maille = maillage_cadrillage( gDonnees.maille, gDonnees.listePointIntersect,p);
    TracerMaillage(maille);

    //trace la figure
    TracerSurface(gDonnees.listeSurface);
    tracerContour(gDonnees.listePointIntersect);
    }


    if (gDonnees.typeAffichage==2)
    {
        POINT_P p; /* definition du point d'origine pour calculer les intesrsections ( pas en (0,0) car pb si objet commence en (0,0)
                    et pb de pente infini si "trop pres" (= 1/2 pixel) d'un bord de l'objet)*/
        p.x = -10.0;
        p.y = 300.0;
        p.z = 0;
        gDonnees.maille = maillage_cadrillage( maillage(gDonnees.densiteMaillage,gDonnees.dimFil), gDonnees.listePointIntersect,p);
        TracerMaillage(gDonnees.maille);
        TracerSurface(gDonnees.listeSurface);
        tracerContour(gDonnees.listePointIntersect);
    }



    if (gDonnees.typeAffichage == 1)
    {
        TracerMaillage(gDonnees.maille);
        TracerSurface(gDonnees.listeSurface);
        tracerContour(gDonnees.listePointIntersect);
    }
}

void tracerContour (LISTE * listePointIntersect)
{
    ELEMT* elemt1 = listePointIntersect->premier; // premier elmt de la liste de point
    ELEMT* elemtfin;//deuximeme elmt


    while (elemt1 != NULL)// parcours de tout les elmts de la liste deux par deux
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

    // changement de couleur (au cas où)
    fl_color(FL_BLACK);

    //on trace que des ligne de taille 1 pixel
    fl_line_style( FL_SOLID, 1);

    //Correspond au nombre de contour à tracer = dimfil * nb de contour
    int compteurContour = 0;

    while (compteurContour  < gDonnees.nbLignePerimetre*gDonnees.dimFil)
    {
        //Notation pour alléger les calculs : correspond au décalage du n'ieme segment pour qu'il vienne correctemnt s'accoler
        //au précédent.
        float rapportDecallage = 1/(vect.a * vect.a + vect.b * vect.b);
        int decallagex =  compteurContour * rapportDecallage * vect.a ;
        int decallagey =  compteurContour * rapportDecallage * vect.b;

        /*C'est là où est vériitablement tracé les contours de la figure fl_ligne(X_extremité1,Y_extrémité1,X_extremité2,Y_extremité2)
        - les deux premier terme permettent de se placer correctement dans l'interface graphique (coordonne de l'origine de l'interface graphique)
        - le premier floor : correspond au coord. du point du contour originel (les segments qui forme le contour exterieur)
        - Ensuite vient le "décalage" pour donner l'épaisseur du trait quand le compteurContour augmente
                -> il faut différencier le cas déplacement selon plus x (resp y) et selon moins x (resp y)
                -> en effet floor (-3.14) = -4 et floor (3.14) = 3 ....
                -> astuce de calcul : soit a dans R, si a>0 (a+|a|)/2 = a et (a - |a|)/2 = 0 et inversement si a est négatif.
                -> il ne reste plus que à appliquer floor au positif et ceil au négatif pour que le calcul soit correct
        */

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

    //elemt qui va parcourir les valeurs de la liste
    ELEMT * parcours = liste->premier;

    //initialisation des sommets à tracer
    POINT_P sommet1;
    POINT_P sommet2;
    POINT_P sommet3;

    while ( parcours != NULL)//tant que la liste n'est pas parcourue entierement on trace les surfaces (il y a 3n point dans la liste)
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
    fl_color(FL_BLACK);
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
