
#include "autre.h"

// Structure pour stocker le ROUTE ID
typedef struct avl_e {
	int element;
	struct avl_e *fd;
  struct avl_e *fg;
  int equilibre;
} AvlE;

// Structure pour stocker les informations sur une ville
typedef struct avl {
  int totalVisites;
  int Visites_D;
  char nom[50];
  AvlE* b;
  struct avl *fd;
  struct avl *fg;
  int equilibre;
} Avl;

Avl *rotationGauche(Avl *a);

Avl *rotationDroite(Avl *a);

int recherche(AvlE* a, int e); 

Avl *creerAvlD(char* n, int route);

Avl *DoubleRG(Avl *a);

Avl *DoubleRD(Avl *a);

Avl *equilibreAVL(Avl *a);

AvlE *creerAvlE(int e);

AvlE *rotationGaucheE(AvlE *a);

AvlE *rotationDroiteE(AvlE *a);

AvlE *DoubleRGE(AvlE *a);

AvlE *equilibreAVLE(AvlE *a);

AvlE *DoubleRDE(AvlE *a);

AvlE *insererVilleE(AvlE *a, int e, int *h);

Avl *insererVille(Avl *a, char* nom, int route, int *h);

Avl *insererVilleD(Avl *a, char* nom, int route, int *h);
