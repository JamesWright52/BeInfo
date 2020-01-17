
typedef struct {int x,y,z;} POINT

typedef struct {int a,b,c;} VECTEUR

typedef struct {POINT p, VECTEUR n;} TRIANGLE

//fonction qui prends une matrice de coordonnees et une côte en argument et renvoie la liste
//des intersections entre le plan z et l'objet

TRIANGLE** intersect(TRIANGLE** matrice, int* pnligne, double z){
  double z1, z2, z3;
  TRIANGLE** intersection = calloc(*pnbligne,sizeof(TRIANGLE**))
  for(i == 0; i < *pnligne; i++){
    if ( (z1 == z) && (z2 == z) && (z3 == z) ){
      
    }
  }
}

//definir une fonction qui prends la matrice de coordonnes et une côte en paramètre
//et renvoie tous les points du périmètre de l'objet à cette côte.
//TRIANGLE perimetreSlice()
