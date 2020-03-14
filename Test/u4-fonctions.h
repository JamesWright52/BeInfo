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

typedef struct hexagone {
	POINT_P bas_gauche;
  double cote;
} HEXAG ;

typedef struct maillage{
  char rectiligne, abeille;
}MAIL;


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
void push_head(LISTE* liste, POINT_P nouveauPoint, VECTEUR vecteur);/* Insertion en début de liste */
void remove_head(LISTE* liste);//enlève le premier élément de la liste
void efface(LISTE* liste);/* Suppression de la liste" */
void concatene_liste(LISTE* liste, LISTE* listeconca);
void printListe(ELEMT * ptr0);/* Procedure d'affichage de la liste */

//fonction calcul sur les listes
LISTE* intersect(TRIANGLE* matrice, int* pnligne, double cote, LISTE* intersection,LISTE * listeSurface);
double min(double z1, double z2, double z3);
double max(double z1, double z2, double z3);
int segment_intersecte(double cote,double z1, double z2);//renvoie 1 si le segment entre z1 et z2 intersecte le plan
int compteOccurence(LISTE* liste, POINT_P point);//Compte le nb de points en double
int compteNbPoint (LISTE* liste);//compte le nb d'elemt de la liste
ELEMT * egaliteElemt (ELEMT * elemt1 , ELEMT * elemt2);//vérifie si deux ELMT sont égaux
VECTEUR sommeNormalise( VECTEUR v1 , VECTEUR v2);//somme deux vecteurs normes
void fusionPoint(ELEMT * elmt, LISTE *liste);//test si le point est déjà dans la liste: si c'est le cas fusion des vecteurs normaux
LISTE* listeSansDoublon(LISTE* liste);

int** maillage( double densite, int epaisseur_fil);
int** plateau_int(double x, double y);
int ** maillage_cadrillage(int** cadrillage, LISTE* perimetre, POINT_P origine);
int dedans(LISTE* perimetre, POINT_P plateau_ij, POINT_P origine);
int nombre_inter_2par2(LISTE* perimetre, POINT_P m_courant, POINT_P origine);
double minim(double P1, double P2);
double maxim(double P1, double P2);
int inter_OM(POINT_P m_courant, POINT_P origine, POINT_P point_bord_1, POINT_P point_bord_2);

/*________________________________________________________________________________________________________________________*/

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    FILE * fichierstl;
    float rapportEchelle;
    int dimFil;
    POINT_P Pmax;
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
void ReInitialiserDonnees() ;

// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
