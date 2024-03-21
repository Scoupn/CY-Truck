#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 5000
// Structure pour stocker les informations sur une ville
typedef struct avl {
  int id;
  float dist_min;
  float dist_max;
  float dist_moy;
  float diff;
  struct avl *fd;
  struct avl *fg;
  int equilibre;
} Avl;

// Crée un nouveau nœud pour une ville avec son nom et initialise les données
Avl *creerAvl(int id, float diff, float max, float min, float moy) {
  Avl *pnew = malloc(sizeof(Avl));
  if (pnew == NULL) {
    exit(1);
  }
  pnew->id = id;
  pnew->dist_max = max;
  pnew->dist_min = min;
  pnew->dist_moy = moy;
  pnew->diff = diff;
  pnew->equilibre = 0; 
  pnew->fg = NULL;
  pnew->fd = NULL;
  return pnew;
}

// Fonction utilitaire pour retourner le maximum entre deux entiers
int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

// Fonction utilitaire pour retourner le minimum entre deux entiers
int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

// Fonction utilitaire pour retourner le minimum entre trois entiers
int min2(int a, int b, int c) {
  return min(min(a, b), c);
}

// Fonction utilitaire pour retourner le maximum entre trois entiers
int max2(int a, int b, int c) {
  return max(max(a, b), c);
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
Avl *equilibreAVL(Avl *a) {
  if (a->equilibre >= 2) {
    if (a->fd->equilibre >= 0) {
      return rotationGauche(a);
    } else {
      return DoubleRG(a);
    }
  } else if (a->equilibre <= -2) {
    if (a->fg->equilibre <= 0) {
      return rotationDroite(a);
    } else {
      return DoubleRD(a);
    }
  }
  return a;
}

Avl *insertionAVL(Avl *a, int id, float diff, float max, float min, float moy, int *h) {
    if (a == NULL) {
        *h = 1;
        return creerAvl(id, diff, max, min, moy);
    } else if (diff < a->diff) {
        a->fg = insertionAVL(a->fg, id, diff, max, min, moy, h);
        *h = -*h;
    } else if (diff > a->diff) {
        a->fd = insertionAVL(a->fd, id, diff, max, min, moy, h);
    } else if (diff == 0) {
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

void extrairecol5(Avl* *a, FILE *fichier) {
    if (a == NULL || fichier == NULL) {
        fprintf(stderr, "Erreur : Pointeur NULL passé à la fonction .\n");
        return;
    }

    char ligne[TAILLE];
    int h;
    int id;
    float mini, moy, maxi;
    int i = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, "\n");
        int colonne = 1;

        while (token != NULL) {
            char *token2 = strtok(token, ";");

            while (token2 != NULL) {
                if (colonne == 1) {
                    id = atoi(token2);
                } else if (colonne == 2) {
                    mini = atof(token2);
                } else if (colonne == 3) {
                    moy = atof(token2);
                } else if (colonne == 4) {
                    maxi = atof(token2);
                } else if (colonne == 5) {
                    float diff = atof(token2);
                    i++;
                    *a = insertionAVL(*a, id, diff, maxi, mini, moy, &h);
                }

                token2 = strtok(NULL, ";");
                colonne++;
            }

            token = strtok(NULL, "\n");
        }
    }
}

void parcoursDecroissant(Avl *a, FILE *fichierSortie, int *i, const int lim) {
    if (a == NULL || fichierSortie == NULL || i == NULL) {
        return;
    }

    if (*i <= lim) {
        parcoursDecroissant(a->fd, fichierSortie, i, lim);
        if (*i <= lim) {
            fprintf(fichierSortie, "%d;%d;%f;%f;%f;%f\n", *i, a->id, a->dist_min, a->dist_moy, a->dist_max, a->diff);
            (*i)++;
        }
        parcoursDecroissant(a->fg, fichierSortie, i, lim);
    }
}

void FreeAVL(Avl *a) {
    if (a != NULL) {
        FreeAVL(a->fg);
        FreeAVL(a->fd);
        free(a);
    }
}

int main() {
    FILE *fichier1, *fichier2;
    Avl* a = NULL;

    fichier1 = fopen("temp/filtre_s.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    fichier2 = fopen("temp/resultat_s.csv", "w");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        fclose(fichier1);
        return 1;
    }

    extrairecol5(&a, fichier1);

    int compteur = 1;
    parcoursDecroissant(a, fichier2, &compteur, 50);

    fclose(fichier1);
    fclose(fichier2);

    FreeAVL(a);

    return 0;
}
