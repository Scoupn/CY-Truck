#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"



// Crée un nouveau nœud pour les routes ID et initialise les données
AvlE *creerAvlE(int e) {
  AvlE *pnew = malloc(sizeof(AvlE));
  if (pnew == NULL) {
    exit(1);
  }
  pnew->element = e;
  pnew->fd = NULL;
  pnew->fg = NULL;
  pnew->equilibre = 0;
  return pnew;
}

// Crée un nouveau nœud pour une ville avec son nom et initialise les données
Avl *creerAvl(char* n, int route) {
  Avl *pnew = malloc(sizeof(Avl));
  if (pnew == NULL) {
    exit(1);
  }
  strcpy(pnew->nom, n);
  pnew->totalVisites = 1;
  pnew->Visites_D = 0;
  pnew->b = creerAvlE(route);
  pnew->fd = NULL;
  pnew->fg = NULL;
  pnew->equilibre = 0;
  return pnew;
}

// Crée un nouveau nœud pour une ville de départ avec son nom et initialise les données
Avl *creerAvlD(char* n, int route) {
  Avl *pnew = malloc(sizeof(Avl));
  if (pnew == NULL) {
    exit(1);
  }
  strcpy(pnew->nom, n);
  pnew->totalVisites = 1;
  pnew->Visites_D = 1;
  pnew->b = creerAvlE(route);
  pnew->fd = NULL;
  pnew->fg = NULL;
  pnew->equilibre = 0;
  return pnew;
}

// Fonction de recherche d'un entier dans un arbre AVL
int recherche(AvlE* a, int e) {
    if (a == NULL)
        return 0; // L'élément n'est pas trouvé

    if (e == a->element)
        return 1; // L'élément est trouvé

    if (e < a->element)
        return recherche(a->fg, e);

    return recherche(a->fd, e);
}

// Fonctions pour effectuer les rotations dans l'arbre AVL
Avl *rotationGauche(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  //Effectue la rotation
  pivot = a->fd;
  a->fd = pivot->fg;
  pivot->fg = a;
  //Met a jour l'équlibre
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - max(eq_pivot, 0) - 1;
  pivot->equilibre = min2(eq_a - 2, eq_a + eq_pivot - 2, eq_pivot - 1);
  a = pivot;
  return a;
}

Avl *rotationDroite(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  pivot = a->fg;
  a->fg = pivot->fd;
  pivot->fd = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - min(eq_pivot, 0) + 1;
  pivot->equilibre = max2(eq_a + 2, eq_a + eq_pivot + 2, eq_pivot + 1);
  a = pivot;
  return a;
}

Avl *DoubleRG(Avl *a) {
  a->fd = rotationDroite(a->fd);
  return rotationGauche(a);
}

Avl *DoubleRD(Avl *a) {
  a->fg = rotationGauche(a->fg);
  return rotationDroite(a);
}

// Fonction pour maj l'équilibre d'un nœud dans l'arbre
Avl *equilibreAVL(Avl* a) {
  if (a->equilibre >= 2) {
    if (a->fd->equilibre >= 0) {
      return rotationGauche(a);
    } 
    else {
      return DoubleRG(a);
    }
  } 
  else if (a->equilibre <= -2) {
    if (a->fg->equilibre <= 0) {
      return rotationDroite(a);
    } 
    else {
      return DoubleRD(a);
    }
  }
  return a;
}

// Fonctions pour effectuer les rotations dans l'arbre AVL
AvlE *rotationGaucheE(AvlE *a) {
  int eq_pivot;
  int eq_a;
  AvlE *pivot;
  //Effectue la rotation
  pivot = a->fd;
  a->fd = pivot->fg;
  pivot->fg = a;
  //Met a jour l'équlibre
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - max(eq_pivot, 0) - 1;
  pivot->equilibre = min2(eq_a - 2, eq_a + eq_pivot - 2, eq_pivot - 1);
  a = pivot;
  return a;
}

AvlE *rotationDroiteE(AvlE *a) {
  int eq_pivot;
  int eq_a;
  AvlE *pivot;
  pivot = a->fg;
  a->fg = pivot->fd;
  pivot->fd = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - min(eq_pivot, 0) + 1;
  pivot->equilibre = max2(eq_a + 2, eq_a + eq_pivot + 2, eq_pivot + 1);
  a = pivot;
  return a;
}

AvlE *DoubleRGE(AvlE *a) {
  a->fd = rotationDroiteE(a->fd);
  return rotationGaucheE(a);
}

AvlE *DoubleRDE(AvlE *a) {
  a->fg = rotationGaucheE(a->fg);
  return rotationDroiteE(a);
}

// Fonction pour maj l'équilibre d'un nœud dans l'arbre
AvlE *equilibreAVLE(AvlE *a) {
  if (a->equilibre >= 2) {
    if (a->fd->equilibre >= 0) {
      return rotationGaucheE(a);
    } 
    else {
      return DoubleRGE(a);
    }
  } 
  else if (a->equilibre <= -2) {
    if (a->fg->equilibre <= 0) {
      return rotationDroiteE(a);
    } 
    else {
      return DoubleRDE(a);
    }
  }
  return a;
}

// Insère dans l'AVL des ROUTE ID
AvlE *insererVilleE(AvlE *a, int e, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvlE(e);
  } 
  else if (e < a->element) {
    a->fg = insererVilleE(a->fg, e, h);
    *h = -*h;
  } 
  else if (e > a->element) {
    a->fd = insererVilleE(a->fd, e, h);
  } 
  else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVLE(a);
    if (a->equilibre == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}


// Insère dans l'AVL des villes
Avl *insererVille(Avl *a, char* nom, int route, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvl(nom, route);
  } 
  else if (strcmp(nom, a->nom) < 0) {
    a->fg = insererVille(a->fg, nom, route, h);
    *h = -*h;
  } 
  else if (strcmp(nom, a->nom) > 0) {
    a->fd = insererVille(a->fd, nom, route, h);
  } 
  else {
    *h = 0;
    if(recherche(a->b, route) == 0){
    	int* eq = malloc(sizeof(int));
    	a->b = insererVilleE(a->b, route, eq);
    	a->totalVisites ++;
    	free(eq);
    }
    return a;
  }
  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVL(a);
    if (a->equilibre == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}

// Insère dans l'AVL des villes de départs
Avl *insererVilleD(Avl *a, char* nom, int route, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvlD(nom, route);
  } 
  else if (strcmp(nom, a->nom) < 0) {
    a->fg = insererVilleD(a->fg, nom, route, h);
    *h = -*h;
  } 
  else if (strcmp(nom, a->nom) > 0) {
    a->fd = insererVilleD(a->fd, nom, route, h);
  } 
  else {
    *h = 0;
    if(recherche(a->b, route) == 0){
    	int* eq = malloc(sizeof(int));
    	a->b = insererVilleE(a->b, route, eq);
    	a->totalVisites ++;
    	free(eq);
    }
    a->Visites_D ++;
    return a;
  }
  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVL(a);
    if (a->equilibre == 0) {
      *h = 0;
    } 
    else {
      *h = 1;
    }
  }
  return a;
}