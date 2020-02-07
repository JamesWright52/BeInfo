#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "intersect.h"
#include "listeSlicer.h"
#include "fonction.h"

/* Programme principal */

int main (){
 //initialisation
 int nbligne = 0;
 double hauteur = 0.;
 POINT Pmin;
 LISTE* listePointIntersecte;
 FILE* ftxt;

 //ouverture du fichier stl
 ftxt = fopen("Cube.stl", "rt");

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
affiche ( donneeSTL , &nbligne);
printf("\n");

printf ("Le point min est :");
printfPoint (minPointTableau(donneeSTL,&nbligne));
Pmin = minPointTableau(donneeSTL,&nbligne);

printf ("Le point max est :");
printfPoint (maxPointTableau(donneeSTL,&nbligne));
printf("\n");

//on place l'objet dans l'espace arbitrairement -> le plus proche de l'origine dans le cadran x,y,z positifs (tare)
tareTableau ( donneeSTL , &nbligne,Pmin);
affiche ( donneeSTL , &nbligne);
printf("\n");

listePointIntersecte = intersect(donneeSTL, &nbligne, hauteur);
printListe((*listePointIntersecte).premier);
printf("\n");

listeSansDoublon(listePointIntersecte);
printf("oui");
printListe((*listePointIntersecte).premier);

efface(listePointIntersecte);
freeTriangle(donneeSTL);
fclose(ftxt);
printf("\n \n#########################################################################################################");
return 1;
 }
