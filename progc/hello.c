#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autre.h"
#include "arbre.h"

#define TAILLE_VILLE 35
#define MAX_VILLES 10



// Parcours l'arbre pour récupérer les 10 villes avec le plus de visites
void parcoursPrefixe(Avl *racine, Avl** topVilles, int *nbVilles) {
    if (racine != NULL) {
        parcoursPrefixe(racine->fg, topVilles, nbVilles);

        if (*nbVilles < MAX_VILLES) {
            topVilles[(*nbVilles)++] = racine;
        } else {
            int minVisites = topVilles[0]->totalVisites;
            int minIndex = 0;

            for (int i = 1; i < MAX_VILLES; i++) {
                if (topVilles[i]->totalVisites < minVisites) {
                    minVisites = topVilles[i]->totalVisites;
                    minIndex = i;
                }
            }

            if (racine->totalVisites > minVisites) {
                topVilles[minIndex] = racine;
            }
        }

        parcoursPrefixe(racine->fd, topVilles, nbVilles);
    }
}
int comparerVilles(const void *a, const void *b) {
    const Avl *villeA = *(const Avl **)a;
    const Avl *villeB = *(const Avl **)b;
    return strcmp(villeA->nom, villeB->nom);
}

int main() {
	FILE *fichier;
	Avl *racine = NULL;
	int *h = malloc(sizeof(int));
	char ligne[1024];

  fichier = fopen("../data/data.csv", "r");
  if (fichier == NULL) {
      perror("Erreur lors de l'ouverture du fichier");
      return EXIT_FAILURE;
  }

  while (fgets(ligne, sizeof(ligne), fichier)) {
      char *token;
      char *colonnes[5];
      int colonne = 0;
      token = strtok(ligne, ";");
      while (token != NULL && colonne < 5) {
          colonnes[colonne++] = token;
          token = strtok(NULL, ";");
      }
      
      
      int route = atoi(colonnes[0]);  
      if (atoi(colonnes[1]) == 1 && colonne >= 3) {
          char *villeDepart = colonnes[2];

          if (strlen(villeDepart) < TAILLE_VILLE) {
              racine = insererVilleD(racine, villeDepart, route, h);
          }
       }

       if (colonne >= 4) {
          char *ville = colonnes[3];

          if (strlen(ville) < TAILLE_VILLE) {
              racine = insererVille(racine, ville, route, h);
          }
       }
   }

    fclose(fichier);

    Avl *topVilles[MAX_VILLES];
    int nbVillesTop = 0;

    parcoursPrefixe(racine, topVilles, &nbVillesTop);

    qsort(topVilles, nbVillesTop, sizeof(Avl *), comparerVilles);

    for (int i = 0; i < nbVillesTop && i < MAX_VILLES; i++) {
        printf("%s;%d;%d\n", topVilles[i]->nom, topVilles[i]->totalVisites, topVilles[i]->Visites_D);
    }
    
    free(h);
    free(racine);

    return EXIT_SUCCESS;
}
