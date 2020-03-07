#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <stdio.h>
#include <stdlib.h>

struct maillage{
  char rectiligne, abeille;
};
struct maillage mail;

double** faux_main();

double** motif_rectiligne();

double** motif_abeille();


#endif
