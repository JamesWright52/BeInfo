
typedef struct {double x,y,z;} POINT

typedef struct {int a,b,c;} VECTEUR

typedef struct {POINT p1; POINT p2; POINT p3; VECTEUR n;} TRIANGLE

//fonction qui prends une matrice de coordonnees et une côte en argument et renvoie la liste
//des intersections entre le plan z et l'objet

POINT* intersect(TRIANGLE* matrice, int* pnligne, double cote){
  double z1, z2, z3;
  VECTEUR normal
  //on créé une matrice avec 3 fois plus de lignes (vu qu'il y a 3 fois plus de points que de lignes)
  POINT* intersection = calloc(3* (*pnbligne),sizeof(POINT*))
  for(i == 0; i < *pnligne; i++){
    z1 = matrice[i].p1.z;
    z2 = matrice[i].p2.z;
    z3 = matrice[i].p3.z;
    normal = matrice[i].n;
    //le triangle est intersecté par le plan concerné sinon rien !!!!définir max et min!!!!
    if ( (cote < min(z1,z2,z3) ) || (max(z1,z2,z3) < cote) ){
        //si le triangle de la ligne i est dans le plan
        if ( (z1 == cote) && (z2 == cote) && (z3 == cote) ){
           intersection[i] = matrice[i].p1;
         }
         //sinon on calcul l'intersection du plan avecle triangle
         else {
            //deux points sont du même côté du plan : le segment formé n'intersecte pas le plan
            //définir une fonction segment_intersecte(z1,z2) qui renvoie 1 si le segment entre z1 et z2 intersecte le plan
            if segment_intersecte(z1,z2){
               // on applique les formules de géométries:
               // x = ((zi-z1)x2 -(zi-z2)x1)/(z2-z1)
               intersection[i].p.x = (cote - z1) * matrice[i].p.x
               
               }
     }
  }
}

//definir une fonction qui prends la matrice de coordonnes et une côte en paramètre
//et renvoie tous les points du périmètre de l'objet à cette côte.
//TRIANGLE perimetreSlice()
