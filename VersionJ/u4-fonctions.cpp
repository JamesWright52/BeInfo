// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <time.h>       // time
#include <string.h>
#include <assert.h>
#include <math.h>
    // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include<stdio.h>
#include"u4-fonctions.h"
#include "u1-interface.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;


/*________________________________________________________________________________________________________________________*/
// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));


    // Initialisations des donnees a effectuer ici
    gDonnees.densiteMaillage = 0.10;
    gInterface.CurseurDensite->value( gDonnees.densiteMaillage) ;

    gDonnees.nbLignePerimetre = 1 ;
    gInterface.ChampSaisieNumNbContour->value( gDonnees.nbLignePerimetre ) ;

    gDonnees.hauteur = 1;
    gInterface.CurseurHauteur->value( gDonnees.hauteur);

    gDonnees.typeAffichage = 0;
    gDonnees.listeSurface = initialisation();



    //test comme au compilo
    FILE* ftxt;//ouverture du fichier test
    ftxt = fopen("PontCylindre.stl", "rt");
    if (ftxt == NULL) {
        puts("Ouverture fichier texte impossible\n");
    }
    //definition de la matrice de triangle
    int nbligne = 0;
    nombreTriangle(ftxt ,&nbligne);
    gDonnees.nbligne = nbligne;
    printf("%d \n", gDonnees.nbligne);
    TRIANGLE * mat = alloueTriangle(nbligne);
    extractionDonneeFichierSTL(ftxt,&nbligne,mat);

    //tarage et mise en donné de la matrice
    POINT_P Pmin;
    Pmin = minPointTableau(mat,&nbligne);
    tareTableau ( mat , &nbligne,Pmin);
    gDonnees.donneesSTL = mat;
    //affiche(gDonnees.donneesSTL,&(gDonnees.nbligne));

    //extraction des maxima et minima de l'objet
    POINT_P Pmax;
    Pmax = maxPointTableau(mat,&nbligne);
    gDonnees.rapportEchelle = ((DIM_INTERFACE - 20))/(int)max (Pmax.x,Pmax.y,Pmax.z);
    gDonnees.tailleObjet = sqrt( pow(Pmax.x-Pmin.x,2)+ pow(Pmax.y-Pmin.y,2)+ pow(Pmax.z-Pmin.z,2));


    gInterface.CurseurHauteur->bounds( 0, max (Pmax.x,Pmax.y,Pmax.z) ) ;

    gDonnees.dimFil = 0.04;
    gInterface.ChampSaisieNumDimFil->value(0.04) ;



    //affiche ( mat , &nbligne);
    printf("\n");
    printf("\n");




    fclose(ftxt);
    // Exemple son
    // JouerSon("media/r2d2.mp3");
}
/*________________________________________________________________________________________________________________________*/
/*________________________________________________________________________________________________________________________*/
// Fonctions utilitaires
TRIANGLE * alloueTriangle(int n) /*alloue l'espace mémoire pour stocker une matrice de triangle*/
{
  TRIANGLE * adresse;
  adresse = (TRIANGLE*)calloc(n,sizeof(*adresse));
  if (adresse == NULL) return NULL;
  else {
    return adresse;
  }
}

void freeTriangle ( TRIANGLE * adresse)
{
  if (adresse == NULL) {
    printf ("Free ne peut pas libérer NULL \n");
}
free(adresse);
}

void nombreTriangle(FILE* ftxt, int * pnbligne) /* Calcul le nombre de triangle que contient un fichier Stl*/
{
  fseek ( ftxt,sizeof (int),SEEK_SET);
  char a [10];
  char b [10];
  float x;
  float y;
  float z;
  char chaine [1000]; /*chaine de caractère temporaire pour extraire les données*/
  while ( NULL != fgets(chaine , 1000 ,ftxt)) /* tant qu'on n'est pas à la fin du fichier fgets renvoie qqch de non NULL*/
  {
    if (5 == sscanf(chaine ,"%s %s %f %f %f \n" , a , b , &x,&y , &z)) /*Structure de la ligne type "vecteur" d'un fichier Stl*/
    {
      *pnbligne = *pnbligne + 1; /* Compteur*/
    }
  }
}

void extractionDonneeFichierSTL (FILE* ftxt , int * pnbligne , TRIANGLE * adresse)
{
  fseek ( ftxt,sizeof (int),SEEK_SET);
  char a [10];
  char b [10];
  float x;
  float y;
  float z;
  int i = 0 ;
  int j = 0;
  int k = 0;
  char chaine [1000]; /*chaine de caractère temporaire pour extraire les données de taille 1000 pour être sur elle soit trop grande*/
  while ( NULL != fgets(chaine , 1000 ,ftxt)) /* tant qu'on n'est pas à la fin du fichier fgets renvoie qqch de non NULL*/
  {
      if (5 == sscanf(chaine ,"%s %s %f %f %f \n" , a , b , &x,&y , &z)) /*Structure de la ligne type "vecteur" d'un fichier Stl*/
    {
      adresse[j].vecteur.a = x;
      adresse[j].vecteur.b = y;
      adresse[j].vecteur.c = z;
    }

    if (4 == sscanf(chaine ,"%s %f %f %f \n" , a ,&x,&y , &z)) /*Structure de la ligne type "point" d'un fichier Stl*/
    {
      if (k % 3 == 0)
      {
        adresse [j].p1.x = x; /* (int) (j/3) pour rester sur la même ligne 3 coup de suite : il y a 3 pts par triangle*/
        adresse [j].p1.y = y;
        adresse [j].p1.z = z;
        k = k+1;
      }

        else if (k % 3 == 1)
        {
          adresse [j].p2.x = x;
          adresse [j].p2.y = y;
          adresse [j].p2.z = z;
          k = k+1;
        }

           else if (k % 3 == 2)
          {
            adresse [j].p3.x = x;
            adresse [j].p3.y = y;
            adresse [j].p3.z = z;

            if ( j < *pnbligne && k < *pnbligne*3)
            {
              j = j+1;
              k = k+1;
          }

          }


    }
  }
}

void affiche(TRIANGLE * adresse, int * pnbligne)
{
  int i;
  for (i = 0 ; i < *pnbligne; i++)
  {
    printfTriangle(adresse [i]);
  }
}

void printfTriangle (TRIANGLE elmt)
{
  printf( "%f  ",  elmt.vecteur.a );
  printf( "%f  ",  elmt.vecteur.b );
  printf( "%f  |",  elmt.vecteur.c );
  printf( "%f  ",  elmt.p1.x );
  printf( "%f  ",  elmt.p1.y );
  printf( "%f  |",  elmt.p1.z );
  printf( "%f  ",  elmt.p2.x );
  printf( "%f  ",  elmt.p2.y );
  printf( "%f  |",  elmt.p2.z );
  printf( "%f  ",  elmt.p3.x );
  printf( "%f  ",  elmt.p3.y );
  printf( "%f  \n",  elmt.p3.z );
}

void printfPoint ( POINT_P point)
{
  printf( "%f  ",  point.x );
  printf( "%f  ",  point.y );
  printf( "%f  \n",  point.z );
}

void printfVecteur ( VECTEUR vect)
{
  printf( "%f  ",  vect.a );
  printf( "%f  ",  vect.b );
  printf( "%f  \n",  vect.c );
}

POINT_P minPointTableau( TRIANGLE * adresse , int * pnbligne)
{
  POINT_P Pmin ;
  Pmin.x = adresse[0].p1.x;
  Pmin.y = adresse[0].p1.y;
  Pmin.z = adresse[0].p1.z;

  int i;

  for (i = 0; i < *pnbligne ;i++)
  {
    if (Pmin.x > adresse[i].p1.x)
    {Pmin.x = adresse[i].p1.x;
    }

    if (Pmin.y > adresse[i].p1.y)
    {Pmin.y = adresse[i].p1.y;
    }

    if (Pmin.z > adresse[i].p1.z)
    {Pmin.z = adresse[i].p1.z;
    }

    if (Pmin.x > adresse[i].p2.x)
    {Pmin.x = adresse[i].p2.x;
    }

    if (Pmin.y > adresse[i].p2.y)
    {Pmin.y = adresse[i].p2.y;
    }

    if (Pmin.z > adresse[i].p2.z)
    {Pmin.z = adresse[i].p2.z;
    }

    if (Pmin.x > adresse[i].p3.x)
    {Pmin.x = adresse[i].p3.x;
    }

    if (Pmin.y > adresse[i].p3.y)
    {Pmin.y = adresse[i].p3.y;
    }

    if (Pmin.z > adresse[i].p3.z)
    {Pmin.z = adresse[i].p3.z;
    }
  }
    return Pmin ;
}

POINT_P maxPointTableau( TRIANGLE * adresse , int * pnbligne)
{
  POINT_P Pmax ;
  Pmax.x = adresse[0].p1.x;
  Pmax.y = adresse[0].p1.y;/* Calcul le nombre de triangle que contient un fichier Stl*/
  Pmax.z = adresse[0].p1.z;

  int i;

  for (i = 0; i < *pnbligne ;i++)
  {
    if (Pmax.x < adresse[i].p1.x)
    {Pmax.x = adresse[i].p1.x;
    }

    if (Pmax.y < adresse[i].p1.y)
    {Pmax.y = adresse[i].p1.y;
    }

    if (Pmax.z < adresse[i].p1.z)
    {Pmax.z = adresse[i].p1.z;
    }
    if (Pmax.x < adresse[i].p2.x)
    {Pmax.x = adresse[i].p2.x;
    }

    if (Pmax.y < adresse[i].p2.y)
    {Pmax.y = adresse[i].p2.y;
    }

    if (Pmax.z < adresse[i].p2.z)
    {Pmax.z = adresse[i].p2.z;
    }
    if (Pmax.x < adresse[i].p3.x)
    {Pmax.x = adresse[i].p3.x;
    }

    if (Pmax.y < adresse[i].p3.y)
    {Pmax.y = adresse[i].p3.y;
    }

    if (Pmax.z < adresse[i].p3.z)
    {Pmax.z = adresse[i].p3.z;
    }
  }
    return Pmax ;
}

void tareTableau (TRIANGLE * adresse , int * pnbligne, POINT_P Pmin)
{
  int i = 0;
  for (i = 0 ; i < *pnbligne ; i++)
  {
    adresse[i].p1.x = adresse[i].p1.x - Pmin.x;
    adresse[i].p1.y = adresse[i].p1.y - Pmin.y;
    adresse[i].p1.z = adresse[i].p1.z - Pmin.z;

    adresse[i].p2.x = adresse[i].p2.x - Pmin.x;
    adresse[i].p2.y = adresse[i].p2.y - Pmin.y;
    adresse[i].p2.z = adresse[i].p2.z - Pmin.z;

    adresse[i].p3.x = adresse[i].p3.x - Pmin.x;
    adresse[i].p3.y = adresse[i].p3.y - Pmin.y;
    adresse[i].p3.z = adresse[i].p3.z - Pmin.z;
  }
}

/*________________________________________________________________________________________________________________________*/
/*________________________________________________________________________________________________________________________*/


//fonction pour la manipulation de liste

LISTE* initialisation(){
	LISTE* liste = (LISTE*) calloc(1,sizeof(*liste));
	if (liste == NULL){
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
	return liste;
}

/* Insertion en d�but de liste */
void push_head(LISTE* liste, POINT_P nouveauPoint, VECTEUR vecteur){
	ELEMT* nouveau = (ELEMT*) calloc(1,sizeof(ELEMT));
	if (nouveau == NULL || liste == NULL){exit(1);}
	nouveau->p = nouveauPoint;
	nouveau->vecteur = vecteur;
	nouveau->suivant = liste->premier;
	liste->premier = nouveau;
}


void remove_head(LISTE* liste){
	if (liste == NULL){exit(EXIT_FAILURE);}
	if (liste->premier != NULL){
		ELEMT* aSupprimer = liste->premier;
		liste->premier =liste->premier->suivant;
		free(aSupprimer);
	}
}

/* Suppression de la liste" */
void efface(LISTE* liste){
    if (liste!= NULL){
        ELEMT* p = liste->premier;
        while(p != NULL){
            ELEMT* suivant = p->suivant;
            free(p);
            p = suivant;
        free(liste);
        }
    }
}

/* Procedure d'affichage de la liste */
void printListe(ELEMT * ptr0){
	if ( NULL == ptr0 )
        {
            printf("Empty!\n");
            }

	else {printf("Liste : \n") ;
        while ( NULL != ptr0 ){
		printf("point=(%f, %f, %f,)\n", (ptr0->p).x, (ptr0->p).y, (ptr0->p).z);
		ptr0 = ptr0->suivant ;
	}}
}


/*________________________________________________________________________________________________________________________*/
/*________________________________________________________________________________________________________________________*/



double min(double z1, double z2, double z3){
  double min = z1;
  if (z2 < min){min = z2;}
  if (z3 < min){min = z3;}
  return min;
 }

double max(double z1, double z2, double z3){
  double max = z1;
  if (z2 > max){max = z2;}
  if (z3 > max){max = z3;}
  return max;
}

int segment_intersecte(double cote, double z1, double z2){
  if ( ( (z1 < cote) && (z2 > cote) ) || ( (z2 < cote) && (z1 > cote) ) ){
    return 1;
  }
  return 0;
}


LISTE* intersect(TRIANGLE* matrice, int* pnligne, double cote,LISTE* intersection,LISTE * listeSurface){

  int i;
  double z1, z2, z3, mini, maxi;
  POINT_P interpoint;
  VECTEUR normal;

  //on parcourt la matrice contenant les coordonnées des triangles ligne par ligne
  for(i = 0; i < *pnligne; i++){
    z1 = matrice[i].p1.z;
    z2 = matrice[i].p2.z;
    z3 = matrice[i].p3.z;
    mini =  min(z1,z2,z3);
    maxi =  max(z1,z2,z3);
    normal = matrice[i].vecteur;

    if (mini==maxi)
    {
        //si le triangle de la ligne i est dans le plan
        //printfTriangle(matrice[i]);

        if ( cote + gDonnees.dimFil*gDonnees.nbLignePerimetre/2 >= mini && mini >= cote - gDonnees.dimFil*gDonnees.nbLignePerimetre/2){
           push_head(listeSurface,matrice[i].p1, normal);
           push_head(listeSurface,matrice[i].p2, normal);
           push_head(listeSurface,matrice[i].p3, normal);
         }

    }


    //le triangle est intersecté par le plan concerné sinon rien
    if ( (cote >= mini) && (maxi >= cote) ){

         /*//si le plan intersecte un sommet
         else if ( (z1 == cote) && (z2 != cote) && (z3 != cote) ){ push_head(intersection, matrice[i].p1, normal); }
         else if ( (z2 == cote) && (z1 != cote) && (z3 != cote) ){ push_head(intersection, matrice[i].p2, normal); }
         else if ( (z3 == cote) && (z1 != cote) && (z2 != cote) ){ push_head(intersection, matrice[i].p3, normal); }*/

         //si le plan intersecte un côté

         if ( (z1 == cote) && (z2 == cote) && (z3 != cote) ){
           push_head(intersection, matrice[i].p1, normal);
           push_head(intersection, matrice[i].p2, normal);
           }
         else if ( (z1 == cote) && (z2 != cote) && (z3 == cote) ){
           push_head(intersection, matrice[i].p3, normal);
           push_head(intersection, matrice[i].p1, normal);
           }
         else if ( (z1 != cote) && (z2 == cote) && (z3 == cote) ){
           push_head(intersection, matrice[i].p2, normal);
           push_head(intersection, matrice[i].p3, normal);
           }

         //sinon on calcul l'intersection du plan avecle triangle
         else {
            //deux points sont du même côté du plan : le segment formé n'intersecte pas le plan
            if (segment_intersecte(cote,z1,z2) == 1){
               // on applique les formules de géométries:
               // x = ((zi-z1)x2 -(zi-z2)x1)/(z2-z1)
               interpoint.x = ( (cote - z1) * matrice[i].p2.x - (cote - z2) * matrice[i].p1.x ) / (z2-z1);
               interpoint.y = ( (cote - z1) * matrice[i].p2.y - (cote - z2) * matrice[i].p1.y ) / (z2-z1);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
            if (segment_intersecte(cote,z2,z3) == 1) {
               interpoint.x = ( (cote - z2) * matrice[i].p3.x - (cote - z3) * matrice[i].p2.x ) / (z3-z2);
               interpoint.y = ( (cote - z2) * matrice[i].p3.y - (cote - z3) * matrice[i].p2.y ) / (z3-z2);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
            if (segment_intersecte(cote,z3,z1) == 1) {
               interpoint.x = ( (cote - z3) * matrice[i].p1.x - (cote - z1) * matrice[i].p3.x ) / (z1-z3);
               interpoint.y = ( (cote - z3) * matrice[i].p1.y - (cote - z1) * matrice[i].p3.y ) / (z1-z3);
               interpoint.z = cote;
               push_head(intersection, interpoint, normal);
               }
         }
     }
  }
  return intersection;
}

int compteNbPoint (LISTE* liste)
{
    ELEMT* elementListe = liste->premier;
	int occurence = 0;
	while (NULL != elementListe->suivant){
            occurence = occurence + 1;
            elementListe = elementListe->suivant;
	}
	return occurence;
}


ELEMT * egaliteElemt (ELEMT * elemt1 , ELEMT * elemt2)
{
    POINT_P p1 = (*elemt1).p;
    POINT_P p2 = (*elemt2).p;
    if (p1.x == p2.x || p1.y == p2.y)
    {
        return elemt2;
    }
    return NULL;
}

int compteOccurence(LISTE* liste, POINT_P point){
	ELEMT* elementListe = liste->premier;
	int occurence = 0;
  int i = 0;
	while (NULL != elementListe){
		if   (   (point.x == (elementListe->p).x)
		      && (point.y == (elementListe->p).y)
				  && (point.z == (elementListe->p).z) ){
			occurence = occurence + 1;
      i = i+1;
    }
		elementListe = elementListe->suivant;
	}
	return occurence;
}

//Elimine les points en double
LISTE* listeSansDoublon(LISTE* liste){
  ELEMT* elementListe;
  LISTE* sansDoublon = initialisation();
	elementListe = liste->premier;
	while (NULL != elementListe->suivant){
    if (compteOccurence(sansDoublon, elementListe->p) == 0){
       push_head(sansDoublon, elementListe->p, elementListe->vecteur);
    }
    elementListe = elementListe->suivant;
  }
  efface(liste);
  return sansDoublon;
}

/*________________________________________________________________________________________________________________________*/
/*________________________________________________________________________________________________________________________*/

ELEMT* chercheElemSuivant(LISTE* liste_surface_z, LISTE* perimetre, POINT_P p0, double* ptheta_balaye, double distance_max){
  ELEMT* p_element_k = liste_surface_z -> premier;
  ELEMT* element_adjacent = liste_surface_z->premier;
  //on définit l'angle  theta comme l'angle (Oy,(M1,Msuivant))
  double theta_min = 360;
  double theta_entre_points = 0;
  double distance_entre_points = 0;
  double distance_min_alignes = distance_max;
  double dy = 0;//diff de y0 - yk
  double dx = 0;
  while ( NULL != p_element_k ){
    //si le point a déjà été traité, on ne le considère pas
    //printf("%lf %lf\n",p_element_k->p.x,p_element_k->p.y);
    if ( compteOccurence(perimetre,p_element_k->p) != 0){ p_element_k = p_element_k -> suivant; }
    else {
          dy = p_element_k->p.y - p0.y;
          dx = p_element_k->p.x - p0.x;
          //printf ("distance_entre_points = %lf distance_min_alignes= %lf\n", distance_entre_points, distance_min_alignes);

          //--------------------------------------------------------------------------
          //Ce bloc calcul theta entre le point fixé en entrée et le point de la liste désigné par p_element_k

          //topo sur arctangente pour l'angle considéré
          //dx>=0 et dy>0 => theta = arctan(dx/dy)        (varie de 0 à pi/2)
          //dx>=0 et dy<0 => theta = pi + arctan(dx/dy)   (varie de pi/2 à pi)
          //dx<=0 et dy<0 => theta = pi + arctan(dx/dy)   (varie de pi à 3pi/2)
          //dx<=0 et dy>0 => theta = 2pi + arctan(dx/dy)  (varie de 3pi/2 à 2pi)
          if ( (dy == 0) && (dx > 0)){
            theta_entre_points = 90;
          }
          else if ( (dy == 0) && (dx < 0)){
            theta_entre_points = 270;
          }
          else if ((dx >= 0) && (dy > 0)){
            theta_entre_points = atan( (dx)/(dy) ) * 180/M_PI;
          }
          else if ( (dy < 0) ) {
            theta_entre_points = (M_PI + atan( (dx)/(dy) )) * 180/M_PI;
          }
          else if ( (dx <= 0) && (dy > 0) ) {
            theta_entre_points = (2*M_PI + atan( (dx)/(dy) )) * 180/M_PI;
          }
          //le cas où on compare un point à lui-même
          else {
            theta_entre_points = 360;
          }

          //--------------------------------------------------------------------------
          //Ce bloc permet d'extraire l'angle le plus petit ainsi que, en cas d'alignement de plusieurs points, la distance la plus courte au point p0
          //on récupère l'angle le plus petit qui correspond à l'élément recherché
          distance_entre_points = sqrt(dx*dx + dy*dy);
          //printf("\nPoint fixé : x = %lf, y = %lf\n",p0.x, p0.y);
          //printf("Point comparé : x = %lf, y = %lf\n",p_element_k->p.x ,p_element_k->p.y);
          //printf("theta=%lf theta_min=%lf\n distance_entre_points = %lf distance_min_alignes= %lf\n-------\n",theta_entre_points, theta_min, distance_entre_points, distance_min_alignes );
          if ( theta_entre_points < theta_min ){
            theta_min = theta_entre_points;
            distance_min_alignes = distance_entre_points;

            if ( (theta_entre_points == theta_min) && (distance_entre_points <= distance_min_alignes) ){
                distance_min_alignes = distance_entre_points;
                element_adjacent = p_element_k;
            }
          }
          //--------------------------------------------------------------------------
          p_element_k = p_element_k -> suivant;
        }
          }
  *ptheta_balaye = theta_min;
  return element_adjacent;
}

LISTE* perimetre_Marche_Jarvis(LISTE* liste_surface_z, double distance_max){
  LISTE* perimetre = initialisation();
  //theta varie entre 0° et 360° dans le sens horaire
  double theta_balaye = 0;
  ELEMT* element_adjacent = liste_surface_z->premier ;
  while ( (compteOccurence(perimetre, element_adjacent->p) == 0 ) && (theta_balaye <= 360)){
    push_head(perimetre, element_adjacent->p, element_adjacent->vecteur);
    element_adjacent = chercheElemSuivant(liste_surface_z, perimetre, element_adjacent->p, &theta_balaye, distance_max);
    //printf("compteOccurence=%d theta balaye=%lf\n", compteOccurence(perimetre, element_adjacent->p),theta_balaye);

  }
  printf("liste après jarvis : ");
  printListe(perimetre->premier);
  return perimetre;
}
