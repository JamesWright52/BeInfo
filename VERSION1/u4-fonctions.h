// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Definition des constantes
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise

    //le triangle est intersecté par le p
/*________________________________________________________________________________________________________________________*/

// Declaration des donnees du projet
typedef struct coordonnees
{
  double x;
  double y;
  double z;
} POINT_P;

typedef struct vect
{
  double a;
  double b;
  double c;
} VECTEUR;


typedef struct
{
  VECTEUR vecteur;
  POINT_P p1;
  POINT_P p2;
  POINT_P p3;
} TRIANGLE;

typedef struct elemListe {
	POINT_P p;
	VECTEUR vecteur;
	struct elemListe * suivant ;
} ELEMT ;

typedef struct Liste{
	ELEMT *premier;
} LISTE;


/*________________________________________________________________________________________________________________________*/

//.h des fonctions

/*alloue l'espace mémoire pour stocker une matrice de triangle*/
TRIANGLE * alloueTriangle(int n);
void freeTriangle ( TRIANGLE * adresse);

/* Calcul le nombre de triangle que contient un fichier Stl*/
void nombreTriangle(FILE* ftxt, int * pnbligne);
void affiche(TRIANGLE * adresse, int * pnbligne);;
void printfTriangle(TRIANGLE elmt);
POINT_P maxPointTableau( TRIANGLE * adresse , int * pnbligne);
POINT_P minPointTableau( TRIANGLE * adresse , int * pnbligne);
void extractionDonneeFichierSTL (FILE* ftxt , int * pnbligne , TRIANGLE * adresse);
void printfPoint ( POINT_P point);
void printfVecteur ( VECTEUR vect);
void tareTableau (TRIANGLE * adresse , int * pnbligne, POINT_P Pmin);

//fonction pour les listes
//initialisation du début de la liste chainée avec un point (0,0,0)
LISTE* initialisation();

/* Insertion en début de liste */
void push_head(LISTE* liste, POINT_P nouveauPoint, VECTEUR vecteur);

//enlève le premier élément de la liste
void remove_head(LISTE* liste);

/* Suppression de la liste" */
void efface(LISTE* liste);



/* Procedure d'affichage de la liste */
void printListe(ELEMT * ptr0);

LISTE* intersect(TRIANGLE* matrice, int* pnligne, double cote, LISTE* intersection,LISTE * listeSurface);

double min(double z1, double z2, double z3);

double max(double z1, double z2, double z3);

//renvoie 1 si le segment entre z1 et z2 intersecte le plan
int segment_intersecte(double cote,double z1, double z2);

//Compte le nb de points en double
int compteOccurence(LISTE* liste, POINT_P point);

//compte le nb d'elemt de la liste
int compteNbPoint (LISTE* liste);

//vérifie si deux ELMT sont égaux
ELEMT * egaliteElemt (ELEMT * elemt1 , ELEMT * elemt2);

//somme deux vecteurs normes
VECTEUR sommeNormalise( VECTEUR v1 , VECTEUR v2);

//test si le point est déjà dans la liste: si c'est le cas fusion des vecteurs normaux
void fusionPoint(ELEMT * elmt, LISTE *liste);

LISTE* listeSansDoublon(LISTE* liste);



/*________________________________________________________________________________________________________________________*/

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    int rapportEchelle;
    float dimFil;
    LISTE * listePointIntersect;
    LISTE * listeSurface;
    TRIANGLE * donneesSTL;
    int nbligne;
    float densiteMaillage;
    int nbLignePerimetre;
    float hauteur;
    float typeAffichage;
// Variables du projet a definir ici
};

extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;

// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
