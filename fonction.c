#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"fonction.h"

TRIANGLE * alloueTriangle(int n) /*alloue l'espace mémoire pour stocker une matrice de triangle*/
{
  TRIANGLE * adresse;
  adresse = calloc(n,sizeof(*adresse));
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

void extractionDonneeFichierSTL (FILE* ftxt, TRIANGLE * adresse)
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
      adresse [i].vecteur.a = x;
      adresse [i].vecteur.b = y;
      adresse [i].vecteur.c = z;
      i = i + 1; /* pour passer à la ligne suivante de la matrice*/
    }
    else if (4 == sscanf(chaine ,"%s %f %f %f \n" , a ,&x,&y , &z)) /*Structure de la ligne type "point" d'un fichier Stl*/
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
            j = j+1;
            k = k+1;
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

void printfPoint ( POINT point)
{
  printf( "%f  ",  point.x );
  printf( "%f  ",  point.y );
  printf( "%f  \n",  point.z );
}

POINT minPointTableau( TRIANGLE * adresse , int * pnbligne)
{
  POINT Pmin ;
  Pmin.x = adresse[0].p1.x;
  Pmin.y = adresse[0].p1.y;
  Pmin.z = adresse[0].p1.z;

  for (int i = 0; i < *pnbligne ;i++)
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

POINT maxPointTableau( TRIANGLE * adresse , int * pnbligne)
{
  POINT Pmax ;
  Pmax.x = adresse[0].p1.x;
  Pmax.y = adresse[0].p1.y;
  Pmax.z = adresse[0].p1.z;

  for (int i = 0; i < *pnbligne ;i++)
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

void tareTableau (TRIANGLE * adresse , int * pnbligne, POINT Pmin)
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
