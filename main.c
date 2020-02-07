#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "intersect.h"
#include "listeSlicer.h"
#include "fonction.h"

/* Programme principal */

int main (){
 FILE* ftxt;
 ftxt = fopen("Cube.stl", "rt");
 if (ftxt == NULL) {
   puts("Ouverture fichier texte impossible\n");
   return -1;
 }
int nbligne = 0;
nombreTriangle(ftxt ,&nbligne);
TRIANGLE * mat = alloueTriangle(nbligne);
POINT Pmin;

printf ("Nombre de case est %d \n", nbligne);

extractionDonneeFichierSTL(ftxt,mat);
affiche ( mat , &nbligne);

printfPoint (minPointTableau(mat,&nbligne));
Pmin = minPointTableau(mat,&nbligne);
printfPoint (maxPointTableau(mat,&nbligne));

tareTableau ( mat , &nbligne,Pmin);
affiche ( mat , &nbligne);

freeTriangle(mat);
fclose(ftxt);

 return 1;
 }
