
#include <stdio.h>
#include <math.h>
#include <stdlib>

double xinter(...);
int nombredinter(...);
double max(double xc, double xd);
double min(double xc, double xd);
double ** plateau(int n, intm);
void destructeur(int ** p, int n);

double main(){ int a,b,i,j;
  int ** plat;
  // récupérer la valeur de la densité à partir de l'interface graphique
  plat = plateau(200,200,d);
  for (i=0; i<200; i++);
    for (j=0; j<b; j++);
      plat[i][j] = i + j;

  destructeur(plat, 200);

}

double max(double xc, double xd){
  if ( (xc - xd) >= 0){
    return xc;
  }
  else {
    return xd;
  }
}

double min(double xc, double xd){
  if ( (xc - xd) >= 0){
    return xd;
  }
  else {
    return xc;
  }
}

// tableau 2D (matrice) avec tous les points du plateau
// plateau d'impression de 200*200 mm
// pas entre chaque point de 1 mm variable en fonction de la densité choisi par l'utilisateur

double ** plateau(int n = 200, int m = 200, double d) { int i,j;
  int ** p;
  p = calloc(n, sizeof(*p));
  if (p == NULL) return NULL;
  else
    for (i = 0; i < n; i++){
      p[i] = calloc(m, sizeof(**p));
      if (p[i] == NULL) return NULL
    }
  return p;
}

void destructeur(int ** p, 200){
  int i;
  for  ( i = 0; i < 200; i++) free(p[i]);
  free(p);
}


int nombredinter( liste des x inter){
  int compt = 0;
  for (i = 0; i < /*len(liste des x inter*/); i++){
    // xi = x[i]
    if ( xi <= xa && min(xc, xd) <= xi <= max(xc, xd)){
      compt += 1;
    }
  }
}

double xinter(point a, point b, point c, point d){
  double xa, ya, xb = 0, yb = 0, xc, yc, xd, yd, xi, yi, a1, a2, b1, b2;
  // création d'une liste x inter
  // lecture des coordonnées
  for (/*balayage des points du plateau*/){
    xa = x[i];
    ya = y[i];
    for (/*balayage dans l'ordre du contour de la pièce*/){
      xc = x[i];
      xd = x[i+1];
      yc = y[i];
      yd = y[i+1];

      a1 = (ya - yb)/(xa - xb);
      b1 = (ya - a1*xa);
      a2 = (yc - yd)/(xc - xd);
      b2 = (yc - a2*xc);

      if ( (a1 - a2) != 0 ) {
        xi = (b2 - b1)/(a1 - a2);
        // ajouter la coordonnée à une liste x inter
      }
    }
  }
}
