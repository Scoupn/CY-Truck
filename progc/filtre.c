#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 5000

struct Statistique {
    int id;
    float min;
    float max;
    float somme;
    int count;
    float moyenne;
    float difference;
};

int main() {
    FILE *input = fopen("temp/calcul_s.csv", "r");
    if (input == NULL) { 
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrée calcul_s.csv\n");
        return 1;
    }

    FILE *output = fopen("temp/filtre_s.csv", "w+");
    if (output == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de sortie filtre_s.csv\n");
        fclose(input);
        return 1;
    }

    // Variables pour gérer dynamiquement la mémoire
    int max_id = -1;
    struct Statistique *stats = NULL;

    char line[TAILLE];
    while (fgets(line, sizeof(line), input)) {
        int id; 
        float value;
        if (sscanf(line, "%d;%f", &id, &value) != 2) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne : %s", line);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        // Vérifier si l'identifiant est dans la plage attendue
        if (id >= 0) {
            // Mettre à jour le plus grand identifiant rencontré
            if (id > max_id) {
                max_id = id;
            }

            // Réallouer dynamiquement la mémoire si nécessaire
            stats = realloc(stats, (max_id + 1) * sizeof(struct Statistique));

            // Initialiser à zéro si l'élément est nouvellement alloué
            if (stats[id].count == 0) {
                stats[id].id = id;
                stats[id].min = value;
                stats[id].max = value;
                stats[id].somme = value;
                stats[id].count = 1;
            } else {
                // Mettre à jour les statistiques
                if (value < stats[id].min) {
                    stats[id].min = value;
                }
                if (value > stats[id].max) {
                    stats[id].max = value;
                }
                stats[id].somme += value;
                stats[id].count++;
            }
        }
    }

    for (int i = 0; i <= max_id; i++) {
        if (stats[i].count > 0) {
            stats[i].moyenne = (float)stats[i].somme / stats[i].count;
            stats[i].difference = (float)stats[i].max - (float)stats[i].min;
            fprintf(output, "%d;%.3f;%.2f;%.3f;%.3f\n", stats[i].id, stats[i].min, stats[i].moyenne, stats[i].max, stats[i].difference);
        }
    }

    // Libérer la mémoire allouée dynamiquement
    free(stats);



    fclose(input);
    fclose(output);

    if (remove("temp/calcul_s.csv") != 0) {
        printf("Erreur lors de la suppression du fichier temp/calcul_s.csv.\n");
        return 1;
    }
    printf("\nLe fichier temp/calcul_s.csv a été supprimé avec succès.\n");
   

    return 0;
}
