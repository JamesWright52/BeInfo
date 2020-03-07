#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "intersect.h"
#include "listeSlicer.h"
#include "fonction.h"
#include "perimetre.h"

/* Programme principal */

int main (){
 //initialisation
 int nbligne = 0;
 double hauteur = 0.;
 double longueur_max;
 POINT Pmin;
 LISTE* listePointIntersecte;
 FILE* ftxt;
 printf("Entrez la hauteur de la surface :");
 scanf("%lf",&hauteur);
 //ouverture du fichier stl
 ftxt = fopen("./fichier_stl/Cube.stl", "rt");

 //on vérifie que le fichier s'ouvre bien
 if (ftxt == NULL) {
   puts("Ouverture fichier texte impossible\n");
   return -1;
 }
//on compte le nombre de triangle pour connaitre le nombre de ligne
nombreTriangle(ftxt ,&nbligne);

//on créé une matrice dont chaque ligne contiendra le vecteur normal et les 3 points du triangle
TRIANGLE * donneeSTL = alloueTriangle(nbligne);

printf("\n \n#########################################################################################################\n");
printf("\n");
printf ("Nombre de case est %d \n \n", nbligne);

//on récupère les données du fichier STL dans la matrice
extractionDonneeFichierSTL(ftxt,donneeSTL);

//affichage de la matrice récupérée
//affiche ( donneeSTL , &nbligne);
//printf("\n");

//printf ("Le point min est :");
//printfPoint (minPointTableau(donneeSTL,&nbligne));
Pmin = minPointTableau(donneeSTL,&nbligne);

//printf ("Le point max est :");
//printfPoint (maxPointTableau(donneeSTL,&nbligne));

//printf ("La longueur max est :");
longueur_max = longueur_max_objet(donneeSTL,&nbligne);
//printf("%lf\n",longueur_max);
//printf("\n");

//on place l'objet dans l'espace arbitrairement -> le plus proche de l'origine dans le cadran x,y,z positifs (tare)
tareTableau ( donneeSTL , &nbligne, Pmin);
affiche ( donneeSTL , &nbligne);
printf("\n");

listePointIntersecte = intersect(donneeSTL, &nbligne, hauteur);

//listePointIntersecte->premier == NULL ? printf("Liste : Liste vide!\n") : printListe((*listePointIntersecte).premier);
listePointIntersecte = listeSansDoublon(listePointIntersecte);
if (listePointIntersecte->premier == NULL){ printf("Liste : Liste vide!\n"); }
else {
  (listePointIntersecte = perimetre_Marche_Jarvis(listePointIntersecte, longueur_max));
}
printListe(listePointIntersecte->premier);

efface(listePointIntersecte);
freeTriangle(donneeSTL);
fclose(ftxt);
printf("\n \n#########################################################################################################");
return 1;
 }
