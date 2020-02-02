#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "intersect.h"
#include "listeSlicer.h"
#include "conversion_stl_en_tableau_triangle.h"

/* Programme principal */
int main(void) {
  FILE* ftxt;
  ftxt = fopen("Cube.stl", "rt");
  if (ftxt == NULL) {
    puts("Ouverture fichier texte impossible\n");
    return -1;
  }
 int pnbligne;
 nombreTriangle(ftxt ,&pnbligne);
 printf ("Nombre de case est %d \n", pnbligne);


 TRIANGLE * mat = alloueTriangle(pnbligne);
 extractionDonneeFichierSTL(ftxt,&pnbligne,mat);
 affiche ( mat , &pnbligne);
 printfPoint (minPointTableau(mat,&pnbligne));
 printfPoint (maxPointTableau(mat,&pnbligne));

 freeTriangle(mat);
 fclose(ftxt);

  return 1;
}
