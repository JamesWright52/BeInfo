int Not_In_Im_F = -1;
  for(intj=0;j<m;j++)
    head_F[j]=Not_In_Im_F; //    initialement, les listes

//    des antécédents sont vides

for(int i=0;i<n;i++)
  j=F[i],next_F[i]=head_F[j],head_F[j]=i;
//    chaînage amont

for (int i=head_F[j];i!=Not_In_Im_F;i=next_F[i])
  { assert(F(i)==j);
//    j doit être dans l’image de i
//    ... votre code
}

class Mesh { public:
int nv,nt; //    nb de sommet, nb de triangle
int (* nu)[3]; //    connectivité
int(* c)[3]; //    coordonnées de sommet
int operator()(int i,int j) const {
return
nu[i][j]);}
Mesh(const char * filename); //    lecture d’un maillage
}


template <class T> inline void Exchange (T& a,T& b) {T c=a;a=b;b=c

ConstructionArete(const Mesh & Th, int (* arete)[2],int &nbe)
{
  int SommetDesAretes[3][2] = { {0,1},{1,2},{2,0}};
  nbe = 0; //    nombre d’arête;
  for(int t=0;t<Th.nt;t++)
    for (int et=0;et<3;et++) {
      int i= Th(t,SommetDesAretes[et][0]);
      int j= Th(t,SommetDesAretes[et][1]);
      if (j < i) Exchange(i,j) //    on oriente l’arête
      bool existe =false;//    l’arête n’existe pas a priori
        for (int e=0;e<nbe;e++) //   pour les arêtes existantes
          if (arete[e][0] == i && arete[e][1] == j)
            {existe=true;break;} //    l’arête est déjà construite
      if (!existe) //    nouvelle arête
        arete[nbe][0]=i,arete[nbe++][1]=j;}
  }


ConstructionArete(const Mesh & Th,int (* arete)[2],int &nbe, int nbex) {
  int SommetDesAretes[3][2] = { {0,1},{1,2},{2,0}};
  int end_list=-1;
  int * head_minv = new int [Th.nv];
  int * next_edge =new int [nbex];
  for (int i =0;i<Th.nv;i++)
    head_minv[i]=end_list; //   liste vide
  nbe = 0; //    nombre d’arête;
  for (int t=0;t<Th.nt;t++)
    for (int et=0;et<3;et++) {
        int i= Th(t,SommetDesAretes[et][0]); //    premier sommet;
        int j= Th(t,SommetDesAretes[et][1]); //    second sommet;
        if (j < i) Exchange(i,j) //    on oriente l’arête
        bool existe = false; //    l’arête n’existe pas a priori
          for (int e=head_minv[i];e!=end_list;e = next_edge[e] ) //    on parcourt les arêtes déjà construites
            if ( arete[e][1] == j) //    l’arête est déjàconstruite
              {existe=true;break;} //    stop
          if (!existe) { //    nouvelle arête
            assert(nbe < nbex);
            arete[nbe][0]=i,arete[nbe][1]=j; //    génération des chaînages
            next_edge[nbe]=head_minv[i],head_minv[i]=nbe++;}
          }
  delete []  head_minv;
  delete []  next_edge;
}

int end_list=-1;
int *head_s = new int [Th.nv];
int *next_p = new int [Th.nt*3];
int i,j,k,p;
for (i=0;i<Th.nv;i++)
  head_s[i] = end_list;
for (k=0;k<Th.nt;k++) //    forall triangles
  for (j=0;j<3;j++) {
    p = 3*k+j;
    i = Th(k,j);
    next_p[p]=head_s[i];
    head_s[i]= p;}
//Utilisation : parcours de tous les triangles ayant le sommet numéro i
  for (int p=head_s[i]; p!=end_list; p=next_p[p])
  { int k=p/3,j = p % 3;
    assert( i == Th(k,j));
//    votre code
}

#include "MatMorse.hpp"
MatriceMorseSymetrique::MatriceMorseSymetrique(const Mesh & Th)
{
  int color=0, * mark;
  int i,j,jt,k,p,t;
  n = m = Th.nv;
  mark = new int [n];
  //    construction optimisée de l’image réciproque de Th(k,j)
  int end_list=-1,*head_s,*next_p;
  head_s = new int [Th.nv];
  next_p = new int [Th.nt*3];
  p=0;
  for (i=0;i<Th.nv;i++)
    head_s[i] = end_list;
  for (k=0;k<Th.nt;k++)
    for (j=0;j<3;j++)
      next_p[p]=head_s[i=Th(k,j)], head_s[i]=p++;
//    initialisation du tableau de couleur
  for (j=0;j<Th.nv;j++)
    mark[j]=color;
  color++;
//   1) calcul du nombre de coefficients a priori non-nuls de la matrice
  nbcoef = 0;
  for (i=0; i<n; i++,color++,nbcoef++)
    for (p=head_s[i],t=p/3; p!=end_list; t=(p=next_p[p])/3)
      for (jt=0; jt< 3; jt++ )
if ( i <= (j=Th(t,jt) )  && (mark[j]!= color))
  mark[j]=color,nbcoef++;
//    nouveau coefficient => marquage + ajout
//    2) allocations mémoires
  ligne.set(new int [n+1],n+1);
  colonne.set(new int [ nbcoef],nbcoef);
  a.set(new double [nbcoef],nbcoef);
//    3) constructions des deux tableaux ligne et colonne
  ligne[0] = -1;
  nbcoef =0;
  for (i=0; i<n; ligne[++i]=nbcoef, color++)
    for (p=head_s[i],t=p/3; p!=end_list; t=(p=next_p[p])/3)
      for (jt=0; jt< 3; jt++ )
        if ( i <= (j=Th(t,jt))  && (mark[j]!= color))
  mark[j]=color, colonne[nbcoef++]=j;
//    nouveau coefficient => marquage + ajout //    4) tri des lignes par index de colonne
  for (i=0; i<n; i++)
    HeapSort(colonne + ligne[i] + 1 ,ligne[i+1] - ligne[i]); //    nettoyage
  delete [] head_s;
  delete [] next_p;
}


template<class T>
void HeapSort(T *c,long n) {
  c-; //    because fortran version aray begin at 1 in the routine
  register long m,j,r,i;
  register T crit;
  if ( n <= 1) return;
  m = n/2 + 1;
  r = n;
  while (1) {
    if (m <= 1 ) {
      crit = c[r];
      c[r-] = c[1];
    if ( r == 1 ) { c[1]=crit;return;}
    } else crit = c[-m];
    j=m;
    while (1) {
      i=j;
      j=2*j;
      if(j>r) {c[i]=crit;break;}
      if ((j<r) && c[j] < c[j+1])) j++;
      if (crit < c[j]) c[i]=c[j];
      else {c[i]=crit;break;}
    }
  }
}





#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
namespace bamg {
using namespace std ;


template <class R,class RR>
class P2 {
public:
  R x,y ;
  P2 () :x(0),y(0) {} ;
  P2 (R a,R b) :x(a),y(b) {}
  P2<R,RR>  operator+(const P2<R,RR> & cc) const
                  {return P2<R,RR>(x+cc.x,y+cc.y) ;}
P2<R,RR>    operator-(const P2<R,RR> & cc) const
                  {return P2<R,RR>(x-cc.x,y-cc.y) ;}
P2<R,RR>    operator-() const{return P2<R,RR>(-x,-y) ;}
RR    operator,(const P2<R,RR> & cc) const    //produit scalaire
                  {return (RR) x* (RR) cc.x+(RR) y* (RR) cc.y ;}
P2<R,RR> operator*(R cc) const
                  {return P2<R,RR>(x*cc,y*cc) ;}
P2<R,RR> operator/(R cc) const
                    {return P2<R,RR>(x/cc,y/cc) ;}
P2<R,RR> operator+=(const P2<R,RR> & cc)
                    {x += cc.x ;y += cc.y ;return *this ;}
P2<R,RR> operator/=(const R r)
                    {x /= r ;y /= r ;return *this ;}
P2<R,RR> operator*=(const R r)
                    {x *= r ;y *= r ;return *this ;}
P2<R,RR> operator-=(const P2<R,RR> & cc)
                    {x -= cc.x ;y -= cc.y ;return *this ;}
};

template <class R,class RR>
inline RR Det(const P2<R,RR> x,const P2<R,RR> y) {
  return (RR) x.x * (RR) y.y - (RR) x.y * (RR) y.x ;}

template <class R,class RR>
inline RR Area2 (const P2<R,RR> a,const P2<R,RR> b,const P2<R,RR> c) {
  return Det(b-a,c-a) ;}

template <class R,class RR>
inline ostream& operator «(ostream& f, const P2<R,RR> & c)
    { f « c.x « "   " « c.y « ’ ’ ; return f ; }
}


#include <cassert>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>

#include "R2.hpp"

namespace bamg {
using namespace std ;

template<class T> inline T Min (const T &a, const T &b)
            {return a < b? a : b;}
template<class T> inline T Max (const T &a, const T & b)
            {return a > b? a : b;}
template<class T> inline T Abs (const T &a) {return a <0? -a : a;}
template<class T> inline double Norme (const T &a) {return sqrt(a*a);}

template<class T> inline void Exchange (T& a,T& b) {T c=a ;a=b ;b=c ;}

// définition des types pour les coordonnées
typedef double R ;
typedef int Icoor1 ;  //type d’une coordonnée entière
typedef double Icoor2 ;  // type des produits de coordonnées entière
const Icoor1 MaxICoor = 8388608 ; // max de coordonnées entières 2 23 pour
// ne pas avoir d’erreur d’arrondi
const Icoor2 MaxICoor22 // MaxICoor22 plus gros produit de coordonnées
            = Icoor2(2)*Icoor2(MaxICoor) * Icoor2(MaxICoor) ; //entières
typedef P2<Icoor1,Icoor2> I2 ; // points à coordonnées entières
typedef P2<R,R> R2 ; //points à coordonnées réelles
//Gestion des erreurs
inline void MeshError(int Err){
  cerr « " Fatal error in the meshgenerator " « Err « endl ;
  exit(1) ; }
inline int BinaryRand(){  // OuiNon aléatoire
  const long HalfRandMax = RAND_MAX/2 ;
  return rand() <HalfRandMax ;
}

// déterminant entier du triangle a, b, c
Icoor2 inline det(const I2 &a,const I2 & b,const I2 &c)
{
  Icoor2 bax = b.x - a.x ,bay = b.y - a.y ;
  Icoor2 cax = c.x - a.x ,cay = c.y - a.y ;
  return bax*cay - bay*cax ;}

// définition des numérotations dans un triangle
static const short VerticesOfTriangularEdge[3][2] = {{1,2},{2,0},{0,1}} ;
static const short EdgesVertexTriangle[3][2] = {{1,2},{2,0},{0,1}} ;
static const short OppositeVertex[3] = {0,1,2} ;
static const short OppositeEdge[3] = {0,1,2} ;
static const short NextEdge[3] = {1,2,0} ;
static const short PreviousEdge[3] = {2,0,1} ;
static const short NextVertex[3] = {1,2,0} ;
static const short PreviousVertex[3] = {2,0,1} ;

class Triangles ; // Le maillages (les triangles)
class Triangle ;  //un triangle


//  /////////////////////////////////////////////////////////////////////////
class Vertex {public:
I2 i ;  //  allow to use i.x, and i.y in long int
R2 r ;  //  allow to use r.x, and r.y in double
R h;  //  Mesh size
int Label ;

Triangle * t ;  //  un triangle t contenant le sommet

short vint ;  // numéro du sommet dans le triangle t
operator  I2  () const {return i ;} //  cast en coor. entières
operator const R2 & () const {return r ;} // cast en coor. réelles
int DelaunayOptim(int = 1) ;  //  optimisation Delaunay autour

friend ostream& operator «(ostream& f, const  Vertex & v)
        {f « "(" « v.i « "," « v.r « ")" ; return f ;}
};

//  /////////////////////////////////////////////////////////////////////////
class TriangleAdjacent {
public:
  Triangle * t ;  //  le triangle
  int a ; //  le numéro de l’arête
  TriangleAdjacent(Triangle * tt,int aa): t(tt),a(aa &3) {} ;
  TriangleAdjacent() {} ;

  operator Triangle * () const  {return t ;}
  operator Triangle & () const  {return *t ;}
  operator int() const  {return a ;}
  TriangleAdjacent operator-()
      { a= PreviousEdge[a] ;
        return *this ;}
inline TriangleAdjacent Adj() const ;
inline void SetAdj2(const TriangleAdjacent& , int =0) ;
inline Vertex * EdgeVertex(const int &) const ;
inline Vertex * OppositeVertex() const ;
inline Icoor2 & det() const ;
inline int Locked() const ;
inline int GetAllFlag_UnSwap() const ;
inline void SetLock() ;
friend ostream& operator «(ostream& f, const TriangleAdjacent & ta)
      {f « "{" « ta.t « "," « ((int) ta.a) « "}" ;
      return f ;}
};  //  end of Vertex class
//  ///////////////////////////////////////////////////////////////////////
class Triangle {
  friend class TriangleAdjacent ;
private:  //  les arêtes sont opposées à un sommet
Vertex * ns [3] ; //  les 3 sommets
Triangle * at [3] ; //  nu triangle adjacent
short aa[3] ; //  les n o des arêtes dans le triangle (mod 4)
//  on utilise aussi aa[i] pour marquer l’arête i (i=0,1,2)
//  si (aa[i] & 4 ) => arête bloquée (lock) marque de type 0
//  si (aa[i] & 2 n+2 => arête marquée de type n (n=0..7)
//  la marque de type 1 était pour déja basculé (markunswap)
//  (aa[i] & 1020 ) l’ensemble des marques
//  1020 = 1111111100 (en binaire)
//  ----------------------------------



public:
  Icoor2 det ;  //  det. du triangle (2 fois l’aire des coor. entières)
bool NonDegenere() const {return ns[0] && ns[1] && ns[2] ;}
Triangle() {}
inline void Set(const Triangle &,const Triangles &,Triangles &) ;
inline int In(Vertex *v) const
        { return ns[0]==v || ns[1]==v || ns[2]==v ;}
const Vertex & operator[](int i) const {return *ns[i] ;} ;
Vertex & operator[](int i)  {return *ns[i] ;} ;
const Vertex * operator()(int i) const {return ns[i] ;} ;
Vertex * & operator()(int i)  {return ns[i] ;} ;
TriangleAdjacent Adj(int i) const //  triangle adjacent + arête
          { return TriangleAdjacent(at[i],aa[i]&3);} ;
Triangle * TriangleAdj(int i) const
          {return at[i&3] ;}  //  triangle adjacent + arête
short  NuEdgeTriangleAdj(int i) const
          {return aa[i&3]&3 ;}  // ° de l’arête adj. dans adj tria

void SetAdjAdj(short a)
        { a &= 3 ;
          Triangle *tt=at[a] ;
          aa [a] &= 1015 ;  //    supprime les marques sauf « swap »
                            //        (1015 == 1111110111 en binaire)
          register short aatt = aa[a] & 3 ;
          if(tt){
            tt->at[aatt]=this ;
            tt->aa[aatt]=a + (aa[a] & 1020 ) ;}}  //  copie toutes les marques
void SetAdj2(short a,Triangle *t,short aat)
        { at[a]=t ;aa[a]=aat ;
          if(t) {t->at[aat]=this ;t->aa[aat]=a ;}}
void SetTriangleContainingTheVertex()
        { if (ns[0]) (ns[0]->t=this,ns[0]->vint=0) ;
          if (ns[1]) (ns[1]->t=this,ns[1]->vint=1) ;
          if (ns[2]) (ns[2]->t=this,ns[2]->vint=2) ;}
int DelaunaySwap(short a) ; //  bascule le quadrilataire formé avec
  // le triangle adj en a si il est non Delaunay
int DelaunayOptim(short a) ;  //  Met tous les quad. contenant
// le sommet a du triangle Delaunay
int Locked(int a)const  //retourne si l’arête est frontière
        { return aa[a]&4 ;}   // (plus d'échange d'arête)
void SetLocked(int a){    //mark l’arête comme frontière (lock)
        Triangle * t = at[a] ;
        t->aa[aa[a] & 3] |=4 ;
        aa[a] |= 4 ;}
};  //----- Fin de la class Triangle -------
//  ///////////////////////////////////////////////////////////////////////

class Triangles {
  public:
    int nbvx,nbtx ; //nombre max de sommets, de triangles
    int nbv,nbt ; //nb sommet, de triangles,
    int nbiv,nbtf ; //nb de triangle dégénéré (arête du bord)
    int NbOfSwapTriangle,NbUnSwap ;
    Vertex * vertices ; //tableau des sommets
    R2 pmin,pmax ;  //  extrema
    R coefIcoor ; //coef pour les coor. entière

    Triangle * triangles ;  //end of variable
    Triangles(int i) ;  //constructeur
    ~Triangles() ;
    void SetIntCoor() ; //  construction des coor. entières
    void RandomInit() ; //construction des sommets aléatoirement

//sauce C++
    const Vertex & operator() (int i) const
              { return vertices[i] ;} ;
    Vertex & operator()(int i)
              { return vertices[i] ;} ;
    const Triangle & operator[] (int i) const
              { return triangles[i] ;} ;
    Triangle & operator[](int i)
              { return triangles[i] ;} ;
//transformation des coordonnées ...
    I2 toI2(const R2 & P) const {
      return I2( (Icoor1) (coefIcoor*(P.x-pmin.x))
                ,(Icoor1) (coefIcoor*(P.y-pmin.y)) ) ;}
    R2 toR2(const I2 & P) const {
            return R2( (double) P.x/coefIcoor+pmin.x,
                        (double) P.y/coefIcoor+pmin.y) ;}
//ajoute sommet à un triangle

    void Add( Vertex & s,Triangle * t,Icoor2 * =0) ;
    void Insert() ; //insère tous les sommets
    Triangle * FindTriangleContening(const I2 & B, // recherche le triangle
                                    Icoor2 dete[3], // contenant le sommet
                                    Triangle *tstart) const ;//partant de tstart

    void ReMakeTriangleContainingTheVertex();

    int Number(const Triangle & t) const { return &t - triangles ;}
    int Number(const Triangle * t) const { return t - triangles ;}
    int Number(const Vertex & t) const { return &t - vertices ;}
    int Number(const Vertex * t) const { return t - vertices ;}
private:
    void PreInit(int) ;
};
//  End Class Triangles
//  ///////////////////////////////////////////////////////////////////////
inline Triangles::Triangles(int i) {PreInit(i) ;}
//  ///////////////////////////////////////////////////////////////////////
inline void TriangleAdjacent::SetAdj2(const TriangleAdjacent & ta, int l )
{ //  set du triangle adjacent
  if(t) {
    t->at[a]=ta.t ;
    t->aa[a]=ta.a|l ;}
  if(ta.t) {
    ta.t->at[ta.a] = t ;
    ta.t->aa[ta.a] = a| l ;
  }
}
//  l’arête Locked est telle Lock (frontière)
inline int TriangleAdjacent::Locked() const
{ return t->aa[a] &4 ;}
//récupération des tous les flag (Lock)
inline int TriangleAdjacent::GetAllFlag_UnSwap() const
//donne tous
{ return t->aa[a] & 1012 ;}
//les marque sauf MarkUnSwap
//Construit l’ Adjacent
inline TriangleAdjacent TriangleAdjacent::Adj() const
{ return t->Adj(a) ;}
//sommet de l’arête
inline Vertex * TriangleAdjacent::EdgeVertex(const int & i) const
{return t->ns[VerticesOfTriangularEdge[a][i]]; }
//sommet opposé à l’arête
inline Vertex * TriangleAdjacent::OppositeVertex() const
{return t->ns[bamg::OppositeVertex[a]]; }
//det du triangle
inline Icoor2 & TriangleAdjacent::det() const
{ return t->det ;}
//Construit l’adjacent
inline TriangleAdjacent Adj(const TriangleAdjacent & a)
{ return a.Adj() ;}

//Adjacence suivante dans le triangle
inline TriangleAdjacent Next(const TriangleAdjacent & ta)
{ return TriangleAdjacent(ta.t,NextEdge[ta.a]);}
//Adjacence précédente dans le triangle
inline TriangleAdjacent Previous(const TriangleAdjacent & ta)
{ return TriangleAdjacent(ta.t,PreviousEdge[ta.a]);}
//Optimisation de Delaunay
int inline Vertex::DelaunayOptim(int i)
{
  int ret=0 ;
  if ( t && (vint >= 0 ) && (vint <3) )
    {
      ret = t->DelaunayOptim(vint) ;
      if( !i)
        {
          t =0 ;
//pour supprimer les optimisation future
          vint= 0 ; }
    }
  return ret ;
}
//calcul de det du triangle a,b,c
Icoor2 inline det(const Vertex & a,const Vertex & b,const Vertex & c)
{
  register Icoor2 bax = b.i.x - a.i.x ,bay = b.i.y - a.i.y ;
  register Icoor2 cax = c.i.x - a.i.x ,cay = c.i.y - a.i.y ;
  return bax*cay - bay*cax ;}
//la fonction qui fait l’échange sans aucun test
void swap(Triangle *t1,short a1,
          Triangle *t2,short a2,
          Vertex *s1,Vertex *s2,Icoor2 det1,Icoor2 det2) ;
//la fonction qui fait une échange pour le forçage de la frontière
int SwapForForcingEdge(Vertex * & pva ,Vertex * & pvb ,
                        TriangleAdjacent & tt1,Icoor2 & dets1,
                        Icoor2 & detsa,Icoor2 & detsb, int & nbswap) ;
//la fonction qui force l’arête a,b dans le maillage
int ForceEdge(Vertex &a, Vertex & b,TriangleAdjacent & taret) ;
//la fonction qui marque l’arête comme lock (frontière)
inline void TriangleAdjacent::SetLock(){ t->SetLocked(a) ;}
}


#include "Mesh.hpp"
using namespace std ;
namespace bamg {
  int verbosity=10 ;
//  niveau d’impression
// /////////////////////////////////////////////////////////////////////////
void swap(Triangle *t1,short a1,
          Triangle *t2,short a2,
          Vertex *s1,Vertex *s2,Icoor2 det1,Icoor2 det2)
{
//swap
//-----------------------------------------
//les 2 numéro de l arête dans les 2 triangles
//

-----------------------------------------
int as1 = NextEdge[a1] ;
int as2 = NextEdge[a2] ;
//int ap1 = PreviousEdge[a1] ;
//int ap2 = PreviousEdge[a2] ;
(*t1)(VerticesOfTriangularEdge[a1][1]) = s2 ;
//avant sb
(*t2)(VerticesOfTriangularEdge[a2][1]) = s1 ;
//avant sa
//mise a jour des 2 adjacences externes
TriangleAdjacent taas1 = t1->Adj(as1), taas2 = t2->Adj(as2),
  tas1(t1,as1), tas2(t2,as2), ta1(t1,a1), ta2(t2,a2) ;
//externe haut gauche
taas1.SetAdj2(ta2,taas1.GetAllFlag_UnSwap());
//externe bas droite
taas2.SetAdj2(ta1, taas2.GetAllFlag_UnSwap()) ;
//interne
tas1.SetAdj2(tas2) ;

t1->det = det1 ;
t2->det = det2 ;

t1->SetTriangleContainingTheVertex();
t2->SetTriangleContainingTheVertex();
}
//end swap
//  /////////////////////////////////////////////////////////////////////////
int SwapForForcingEdge(Vertex * & pva ,Vertex * & pvb ,
                        TriangleAdjacent & tt1,Icoor2 & dets1,
                        Icoor2 & detsa,Icoor2 & detsb, int & NbSwap)
{                       //l’arête ta coupe l’arête pva, pvb de cas apres le swap
//sa coupe toujours
//on cherche l’arête suivante on suppose que detsa > 0 et detsb < 0
//attention la routine échange pva et pvb
if(tt1.Locked()) return 0 ;
//frontiere croise
TriangleAdjacent tt2 = Adj(tt1) ;
Triangle *t1=tt1,*t2=tt2 ;
//les 2 triangles adjacent
short a1=tt1,a2=tt2 ;
//les 2 numéros de l’arête dans les 2 triangles
assert ( a1 >= 0 && a1 < 3 ) ;
Vertex & sa= (* t1)[VerticesOfTriangularEdge[a1][0]];
//Vertex & sb= (*t1)[VerticesOfTriangularEdge[a1][1]];
Vertex & s1= (*t1)[OppositeVertex[a1]] ;
Vertex & s2= (*t2)[OppositeVertex[a2]] ;

Icoor2 dets2 = det(*pva,*pvb,s2) ;
Icoor2 det1=t1->det , det2=t2->det ;
Icoor2 detT = det1+det2 ;
assert((det1>0 ) && (det2 > 0)) ;
assert ( (detsa < 0) && (detsb >0) ) ; //[a,b] coupe la droite va,bb
Icoor2 ndet1 = bamg::det(s1,sa,s2) ;
Icoor2 ndet2 = detT - ndet1 ;

int ToSwap =0 ;
//pas de échange
if ((ndet1 >0) && (ndet2 >0))
  {
//on peut échanger
    if ((dets1 <=0 && dets2 <=0) || (dets2 >=0 && detsb >=0))
      ToSwap =1 ;
    else
//échange aléatoire
      if (BinaryRand())
        ToSwap =2 ;
  }
if (ToSwap) NbSwap++,
              bamg::swap(t1,a1,t2,a2,&s1,&s2,ndet1,ndet2);
int ret=1 ;
if (dets2 < 0) //haut
  dets1 = ToSwap ? dets1 : detsa ;
  detsa = dets2 ;
  tt1 = Previous(tt2) ;}
else if (dets2 > 0){//bas
  dets1 = ToSwap ? dets1 : detsb ;
  detsb = dets2 ;
  if( !ToSwap) tt1 = Next(tt2) ;
}
else {//changement de sens
  ret = -1 ;
  Exchange(pva,pvb) ;
  Exchange(detsa,detsb) ;
  Exchange(dets1,dets2) ;
  Exchange(tt1,tt2) ;
  dets1=-dets1 ;
  dets2=-dets2 ;
  detsa=-detsa ;
  detsb=-detsb ;
  if (ToSwap)
    if (dets2 < 0) {//haut
      dets1 = (ToSwap ? dets1 : detsa) ;
      detsa = dets2 ;
      tt1 = Previous(tt2) ;}
    else if (dets2 > 0){//bas
      dets1 = (ToSwap ? dets1 : detsb) ;
      detsb = dets2 ;
      if( !ToSwap) tt1 = Next(tt2) ;
    }
    else {//on a enfin fini le forçage
      tt1 = Next(tt2) ;
      ret =0 ;}
  }
  return ret ;
}
// /////////////////////////////////////////////////////////////////////////
int ForceEdge(Vertex &a, Vertex & b,TriangleAdjacent & taret)
{
  int NbSwap =0 ;
  assert(a.t && b.t) ;
  int k=0 ;
  taret=TriangleAdjacent(0,0) ;
//les 2 sommets sont dans le maillage
//erreur
TriangleAdjacent tta(a.t,EdgesVertexTriangle[a.vint][0]);
Vertex *v1, *v2 = tta.EdgeVertex(0),*vbegin =v2 ;
//on tourne autour du sommet a dans le sens trigo.
Icoor2 det2 = v2 ? det(*v2,a,b): -1 , det1 ;
if(v2)
//cas normal
  det2 = det(*v2,a,b) ;
else {
//pas de chance sommet ∞, au suivant
  tta= Previous(Adj(tta)) ;
  v2 = tta.EdgeVertex(0) ;
  vbegin =v2 ;
  assert(v2) ;
  det2 = det(*v2,a,b) ;
}
while (v2 != &b) {
  TriangleAdjacent tc = Previous(Adj(tta)) ;
  v1 = v2 ;
  v2 = tc.EdgeVertex(0) ;
  det1 = det2 ;
  det2 = v2 ? det(*v2,a,b): det2 ;
  if((det1 < 0) && (det2 >0)) {
//on essaye de forcé l’arête
    Vertex * va = &a, *vb = &b ;
    tc = Previous(tc) ;
    assert ( v1 && v2) ;
    Icoor2 detss = 0,l=0,ks ;
    while ((ks=SwapForForcingEdge( va, vb, tc, detss, det1,det2,NbSwap)))
      if(l++ > 1000000) {
        cerr « " Loop in forcing Egde AB" « endl ;
        MeshError(990) ;
      }
    Vertex *aa = tc.EdgeVertex(0), *bb = tc.EdgeVertex(1) ;
    if (( aa == &a ) && (bb == &b) || (bb == &a ) && (aa == &b)) {
      tc.SetLock() ;
      a.DelaunayOptim(1) ;
      b.DelaunayOptim(1) ;
      taret = tc ;
      return NbSwap ;
    }
  }
  tta = tc ;
  assert(k++<2000) ;
  if ( vbegin == v2 ) return -1 ;
//erreur la frontière est croisée
  }
tta.SetLock() ;
taret=tta ;
a.DelaunayOptim(1) ;
b.DelaunayOptim(1) ;
return NbSwap ;
}
// /////////////////////////////////////////////////////////////////////////
int Triangle::DelaunaySwap(short a){
  if(a/4 !=0) return 0 ;
//arête lock
  Triangle *t1=this,*t2=at[a] ;
//les 2 triangles adjacents
  short a1=a,a2=aa[a] ;
//les 2 numéros de l’arête dans les 2 triangles
  if(a2/4 !=0) return 0 ;
//arête lock
  Vertex *sa=t1->ns[VerticesOfTriangularEdge[a1][0]];
  Vertex *sb=t1->ns[VerticesOfTriangularEdge[a1][1]];
  Vertex *s1=t1->ns[OppositeVertex[a1]];
  Vertex *s2=t2->ns[OppositeVertex[a2]];

  Icoor2 det1=t1->det , det2=t2->det ;
  Icoor2 detT = det1+det2 ;
  Icoor2 detA = Abs(det1) + Abs(det2) ;
  Icoor2 detMin = Min(det1,det2) ;

  int OnSwap = 0 ;
//si 2 triangles infini (bord) => detT = -2 ;
if (sa == 0) {
//les deux triangles sont frontières
  det2=bamg::det(s2->i,sb->i,s1->i);
  OnSwap = det2 >0 ;}
else if (sb == 0) {
// les deux triangles sont frontières
  det1=bamg::det(s1->i,sa->i,s2->i);
  OnSwap = det1 >0 ;}
else if(( s1 != 0) && (s2 != 0) ) {
  det1 = bamg::det(s1->i,sa->i,s2->i);
  det2 = detT - det1 ;
  OnSwap = (Abs(det1) + Abs(det2)) < detA ;
Icoor2 detMinNew=Min(det1,det2) ;
if ( ! OnSwap &&(detMinNew>0)) {
  OnSwap = detMin ==0 ;
  if ( ! OnSwap) {
    while (1)
      {
//critère de Delaunay pure isotrope
        Icoor2 xb1 = sb->i.x - s1->i.x,
          x21 = s2->i.x - s1->i.x,

          yb1 = sb->i.y - s1->i.y,
          y21 = s2->i.y - s1->i.y,
          xba = sb->i.x - sa->i.x,
          x2a = s2->i.x - sa->i.x,
          yba = sb->i.y - sa->i.y,
          y2a = s2->i.y - sa->i.y ;
        double
          cosb12 = double(xb1*x21 + yb1*y21),
          cosba2 = double(xba*x2a + yba*y2a) ,
          sinb12 = double(det2),
          sinba2 = double(t2->det) ;
        OnSwap = ((double) cosb12 * (double) sinba2)
          < ((double) cosba2 * (double) sinb12) ;
        break ;
      }
    }
  }
//OnSwap
//( ! OnSwap &&(det1 > 0) && (det2 > 0) )


}
  if( OnSwap )
    bamg::swap(t1,a1,t2,a2,s1,s2,det1,det2);
  return OnSwap ;
}
// /////////////////////////////////////////////////////////////////////////
void Triangles::Add( Vertex & s,Triangle * t, Icoor2 * det3)
{
//-----------------------------

  Triangle * tt[3] ;
//les 3 nouveaux Triangles
  Vertex &s0 = (* t)[0], &s1=(* t)[1], &s2=(* t)[2] ;
  Icoor2 det3local[3] ;
  int infv = &s0 ? (( &s1 ? ( &s2 ? -1 : 2) : 1 )) : 0 ;
  int nbd0 =0 ;
  int izerodet=-1,iedge ;//izerodet = arête contenant le sommet s
  Icoor2 detOld = t->det ;
  if ( ( infv <0 ) && (detOld <0) || ( infv >=0 ) && (detOld >0) )
    {
      cerr « " infv " « infv « " det = " « detOld « endl ;
      MeshError(3) ;
      //il y a des sommets confondus
    }
  if ( !det3) {
    det3 = det3local ;
//alloc
    if ( infv<0 ) {
      det3[0]=bamg::det(s ,s1,s2) ;
      det3[1]=bamg::det(s0,s ,s2) ;
      det3[2]=bamg::det(s0,s1,s ) ;}
    else {
//one of &s1 &s2 &s0 is NULL so (&si || &sj) <=> !&sk
      det3[0]= &s0 ? -1 : bamg::det(s ,s1,s2) ;
      det3[1]= &s1 ? -1 : bamg::det(s0,s ,s2) ;
      det3[2]= &s2 ? -1 : bamg::det(s0,s1,s ) ;}}
  if ( !det3[0]) izerodet=0,nbd0++ ;
  if ( !det3[1]) izerodet=1,nbd0++ ;
  if ( !det3[2]) izerodet=2,nbd0++ ;
  if (nbd0 >0 )//s est sur une ou des arêtes
    if (nbd0 == 1) {
      iedge = OppositeEdge[izerodet] ;
      TriangleAdjacent ta = t->Adj(iedge) ;
//le point est sur une arête
//si l’arête est frontière on ajoute le point dans la partie externe
      if ( t->det >=0) {
        if ((( Triangle *) ta)->det < 0 ) {
//triangle interne
//add in outside triangle
          Add(s,( Triangle *) ta) ;
          return ;}
      }}
    else {
      cerr « " bug " « nbd0 «endl ;
      cerr « " Bug double points in " « endl ;
      MeshError(5) ;}
tt[0]= t ;
tt[1]= &triangles[nbt++] ;
tt[2]= &triangles[nbt++] ;
if (nbt>nbtx) {
  cerr « " No enougth triangles " « endl ;
  MeshError(999) ; //pas assez de triangle
}
*tt[1]= *tt[2]= *t ;
(* tt[0])(OppositeVertex[0])=&s;


(* tt[1])(OppositeVertex[1])=&s;
(* tt[2])(OppositeVertex[2])=&s;
tt[0]->det=det3[0] ;
tt[1]->det=det3[1] ;
tt[2]->det=det3[2] ;
//mise à jour des adj. des triangles externe
tt[0]->SetAdjAdj(0) ;
tt[1]->SetAdjAdj(1) ;
tt[2]->SetAdjAdj(2) ;
//mise à jour des adj. des 3 triangle interne
const int i0 = 0 ;
const int i1= NextEdge[i0] ;
const int i2 = PreviousEdge[i0] ;
tt[i0]->SetAdj2(i2,tt[i2],i0) ;
tt[i1]->SetAdj2(i0,tt[i0],i1) ;
tt[i2]->SetAdj2(i1,tt[i1],i2) ;
tt[0]->SetTriangleContainingTheVertex();
tt[1]->SetTriangleContainingTheVertex();
tt[2]->SetTriangleContainingTheVertex();
//échange si le point s est sur une arête
if(izerodet>=0) {
  int rswap =tt[izerodet]->DelaunaySwap(iedge);
  if ( !rswap)
    {
      cout « " Pb swap the point s is on a edge =>swap " « iedge « endl ;
      MeshError(98) ;
    }
  }
}
// /////////////////////////////////////////////////////////////////////////
void Triangles::Insert()
{
  NbUnSwap=0 ;
  if (verbosity>2)
    cout « " - Insert initial " « nbv « " vertices " « endl ;
  SetIntCoor() ;
  int i ;
  Vertex** ordre=new (Vertex* [nbvx]) ;
  for (i=0 ;i<nbv ;i++)
    ordre[i]= &vertices[i] ;
//construction d’un ordre aléatoire
  const int PrimeNumber= (nbv % 567890621L) ? 567890629L : 567890621L ;
  int k3 = rand()%nbv ;
  for (int is3=0 ; is3<nbv ; is3++)

    ordre[is3]= &vertices[k3 = (k3 + PrimeNumber)% nbv] ;
  for (i=2 ; det( ordre[0]->i, ordre[1]->i, ordre[i]->i ) == 0 ;)
    if ( ++i >= nbv) {
      cerr « " All the vertices are aline " « endl ;
      MeshError(998) ; }
//échange i et 2 dans ordre afin
//que les 3 premiers sommets ne soit pas alignés
  Exchange( ordre[2], ordre[i]) ;
//on ajoute un point à l’infini pour construire le maillage
//afin d’avoir une définition simple des arêtes frontières


  nbt = 2 ;
//on construit un maillage trival formé d’une arête et de 2 triangles

//construit avec le 2 arêtes orientéess
  Vertex * v0=ordre[0], *v1=ordre[1] ;
  triangles[0](0) = 0 ;
  triangles[0](1) = v0 ;
  triangles[0](2) = v1 ; // sommet pour infini (la frontière)
  triangles[1](0) = 0 ;
  triangles[1](2) = v0 ;
  triangles[1](1) = v1 ; // sommet pour infini (la frontière)
  const int e0 = OppositeEdge[0] ;
  const int e1 = NextEdge[e0] ;
  const int e2 = PreviousEdge[e0] ;
  triangles[0].SetAdj2(e0, &triangles[1] ,e0) ;
  triangles[0].SetAdj2(e1, &triangles[1] ,e2) ;
  triangles[0].SetAdj2(e2, &triangles[1] ,e1) ;
  triangles[0].det = -1 ;
  triangles[1].det = -1 ;

//faux triangles
//faux triangles
  triangles[0].SetTriangleContainingTheVertex();
  triangles[1].SetTriangleContainingTheVertex();
  nbtf = 2 ;
//ici, il y a deux triangles frontières invalide
//----- on ajoute les sommets un à un -------
  int NbSwap=0 ;
  if (verbosity>3) cout « " - Begin of insertion process " « endl ;
  Triangle * tcvi=triangles ;
  for (int icount=2 ; icount<nbv ; icount++)
    {
      Vertex *vi = ordre[icount] ;
      Icoor2 dete[3] ;
      tcvi = FindTriangleContening(vi->i,dete,tcvi);
      Add(*vi,tcvi,dete) ;
      NbSwap += vi->DelaunayOptim(1) ;
    }
//fin de boucle en icount


  if (verbosity>3)
    cout « " NbSwap of insertion " « NbSwap
        « " NbSwap/Nbv " « (float) NbSwap / (float) nbv
        « " NbUnSwap " « NbUnSwap « " Nb UnSwap/Nbv "
        « (float)NbUnSwap /(float) nbv
        «endl ;
  NbUnSwap = 0 ;
  delete [] ordre ;
  }
//  /////////////////////////////////////////////////////////////////////////
void Triangles::RandomInit()
{
  nbv = nbvx ;
  for (int i = 0 ; i < nbv ; i++)
    {
      vertices[i].r.x= rand() ;
      vertices[i].r.y= rand() ;
      vertices[i].Label = 0 ;
    }
}
// /////////////////////////////////////////////////////////////////////////
Triangles::~Triangles()
{
  if(vertices) delete [] vertices ;
  if(triangles) delete [] triangles ;
    PreInit(0) ;
//  met to les sommets à zèro
}
// /////////////////////////////////////////////////////////////////////////
void Triangles::SetIntCoor()
{
  pmin = vertices[0].r ;
  pmax = vertices[0].r ;
// recherche des extrema des sommets pmin,pmax
  int i ;
  for (i=0 ;i<nbv ;i++) {
    pmin.x = Min(pmin.x,vertices[i].r.x) ;
    pmin.y = Min(pmin.y,vertices[i].r.y) ;
    pmax.x = Max(pmax.x,vertices[i].r.x) ;
    pmax.y = Max(pmax.y,vertices[i].r.y) ;
  }
  R2 DD = (pmax-pmin)*0.05 ;
  pmin = pmin-DD ;
  pmax = pmax+DD ;
  coefIcoor= (MaxICoor)/(Max(pmax.x-pmin.x,pmax.y-pmin.y));
  assert(coefIcoor >0) ;
//génération des coordonnées entières

  for (i=0 ;i<nbv ;i++) {
    vertices[i].i = toI2(vertices[i].r) ;
  }
//calcule des determinants si nécessaire
  int Nberr=0 ;
  for (i=0 ;i<nbt ;i++)
    {
      Vertex & v0 = triangles[i][0] ;
      Vertex & v1 = triangles[i][1] ;
      Vertex & v2 = triangles[i][2] ;
      if ( &v0 && &v1 && &v2 )
//un bon triangle ;
        {
          triangles[i].det= det(v0,v1,v2) ;
          if (triangles[i].det <=0 && Nberr++ <10)
            {
              if(Nberr==1)
                cerr « "+++ Fatal Error "
                    « "(SetInCoor) Error : area of Triangle < 0\n" ;
            }
          }
        else
          triangles[i].det= -1 ;
//le triangle est dégénéré ;
      }
    if (Nberr) MeshError(899) ;
  }
// /////////////////////////////////////////////////////////////////////////
int Triangle::DelaunayOptim(short i)
{

//nous tournons dans le sens trigonométrique
  int NbSwap =0 ;
  Triangle *t = this ;
  int k=0,j =OppositeEdge[i] ;
  int jp = PreviousEdge[j] ;
//initialise tp, jp avec l’arête précédente de j
  Triangle *tp= at[jp] ;
  jp = aa[jp]&3 ;
  do {
    while (t->DelaunaySwap(j))
      {
        NbSwap++ ;
        assert(k++<20000) ;
        t= tp->at[jp] ;
        j= NextEdge[tp->aa[jp]&3] ;
      }
//on a fini ce triangle
    tp = t ;
    jp = NextEdge[j] ;
    t= tp->at[jp] ;
    j= NextEdge[tp->aa[jp]&3] ;


  } while( t != this) ;
  return NbSwap ;
}

// /////////////////////////////////////////////////////////////////////////
void Triangles::PreInit(int inbvx)
{
//fonction d’initialisation -------------------------
//-------------------------------------------
  srand(19999999) ;
  NbOfSwapTriangle =0 ;
  nbiv=0 ;
  nbv=0 ;
  nbvx=inbvx ;
  nbt=0 ;
  nbtx=2*inbvx-2 ;
  if (inbvx) {
    vertices=new Vertex[nbvx] ;
    assert(vertices) ;
    triangles=new Triangle[nbtx] ;
    assert(triangles) ;}
  else {
    vertices=0 ;
    triangles=0 ;
    nbtx=0 ;
  }
}
// /////////////////////////////////////////////////////////////////////////
Triangle * Triangles::FindTriangleContening(const I2 & B,
                                            Icoor2 dete[3],
                                            Triangle *tstart) const
{
//entrée: B
//sortie: t
//sortie : dete[3]
//t triangle et s0, s1, s2 le sommet de t
//dete[3] = det(B,s1,s2) , det(s0,B,s2), det(s0,s1,B)
//avec det(a, b, c) = −1 si l’un des 3 sommet a,b,c est NULL (infini)
Triangle * t=0 ;
int j,jp,jn,jj ;
t=tstart ;
assert(t>= triangles && t < triangles+nbt) ;
Icoor2 detop ;
int kkkk =0 ;
//nombre de triangle testé
while ( t->det < 0)
  {//le triangle initial est externe (une arête frontière)
    int k0=(*t)(0) ? (( (*t)(1) ? ( (*t)(2) ? -1 : 2) : 1 )) : 0 ;
    assert(k0>=0) ;
//k0 the NULL vertex
    int k1=NextVertex[k0],k2=PreviousVertex[k0];
    dete[k0]=det(B,(*t)[k1],(*t)[k2]);
    dete[k1]=dete[k2]=-1 ;
    if (dete[k0] > 0)
//B n’est pas dans le domaine
      return t ;
    t = t->TriangleAdj(OppositeEdge[k0]);
    assert(kkkk++ < 2) ;

  }
jj=0 ;
detop = det(*(*t)(VerticesOfTriangularEdge[jj][0]),
            *(*t)(VerticesOfTriangularEdge[jj][1]),B);
while(t->det > 0 )
  {
    assert( kkkk++ < 2000 ) ;
    j= OppositeVertex[jj] ;
    dete[j] = detop ;
    jn = NextVertex[j] ;
    jp = PreviousVertex[j] ;
    dete[jp]= det(*(*t)(j),*(*t)(jn),B) ;
    dete[jn] = t->det-dete[j] -dete[jp] ;
    int k=0,ii[3] ;
    if (dete[0] < 0 ) ii[k++]=0 ;
    if (dete[1] < 0 ) ii[k++]=1 ;
    if (dete[2] < 0 ) ii[k++]=2 ;
//det(*b,*s1,*s2) ;
//compte le nombre k de dete < 0
//0 => on a trouvé
//1 => on va dans cet direction
//2 => deux choix, on choisi aléatoirement
    if (k==0)
      break ;
    if (k == 2 && BinaryRand())
      Exchange(ii[0],ii[1]) ;
    assert ( k < 3) ;
    TriangleAdjacent t1 = t->Adj(jj=ii[0]) ;
    if ((t1.det() < 0 ) && (k == 2))
      t1 = t->Adj(jj=ii[1]) ;
    t=t1 ;
    j=t1 ;
    detop = -dete[OppositeVertex[jj]] ;
    jj = j ;
  }
  if (t->det<0)
//triangle externe (arête frontière)
    dete[0]=dete[1]=dete[2]=-1,dete[OppositeVertex[jj]]=detop;
    return t ;
  }
}
//----- end namespace -------


#include <cassert>
#include <fstream>
#include <iostream>
using namespace std ;
#include "Mesh.hpp"
using namespace bamg ;

void GnuPlot(const Triangles & Th,const char *filename) {
  ofstream ff(filename) ;
  for (int k=0 ;k<Th.nbt ;k++)
    {
      const Triangle &K=Th[k] ;
      if (K.det>0)
//true triangle
      {
        for (int k=0 ;k<4 ;k++)
          ff « K[k%3].r « endl ;
        ff « endl « endl ;}
    }
  }
int main(int argc, char ** argv)
{
  int nbv = argc > 1 ? atoi(argv[1]) : 100 ;
  int na= argc > 2 ? atoi(argv[2]) : 0 ;
  int nb= argc > 3 ? atoi(argv[3]) : nbv-1 ;
  assert ( na != nb && na >=0 && nb >=0 && na < nbv && nb < nbv) ;

  Triangles Th(nbv) ;
  Th.RandomInit() ;
  Th.Insert() ;
  TriangleAdjacent ta(0,0) ;
  GnuPlot(Th,"Th0.gplot") ;
  int nbswp = ForceEdge(Th(na),Th(nb),ta) ;
  if(nbswp<0) { cerr « " -Impossible de force l’arête " « endl ;}
  else {
    cout « " Nb de swap pour force l’arete [" « na « " " « nb
« "] =" « nbswp « endl ;
    GnuPlot(Th,"Th1.gplot") ; }
  return(0) ;
}
