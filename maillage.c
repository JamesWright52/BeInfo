

#include <stdio.h>

//densité, type de maillage, dimension fixe du plateau

struct maillage{
  char rectiligne, abeille;
};
struct maillage mail;


double** main(){
  scanf("%d",&mail);
  if (mail == 1){   //1= rectiligne
    maillage  = motif_rectiligne();
  }
  else {
    maillage = motif_abeille();
  }

}


double** motif_rectiligne(){
  double** maille

  if (0.5 < densite &&  densite <= 1){
    if (0.5 < densite && densite <= 0.75){
      // 1 trait plein sur 3
    }
    else {
      // 1 trait plein sur 2
    }
  }
  else (0 <= densite && densite <= 0.5){
    if (0 <= densite && densite <= 0.25){
      // 1 trait plein sur 5

    }
    else {
      // 1 trait plein sur 4

    }
  }

}

double** motif_abeille(){
  double** maille
}
