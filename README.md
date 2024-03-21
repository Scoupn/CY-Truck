# CY-TRUCK

Notre projet a pour objectif de gerer un fichier en automatisant des opérations impossibles a effectuer manuellement pour un humain. Il est nécéssaire en prérequis d'avoir installé 
```bash
gcc
gnuplot
```
## INFORMATIONS

 - [La description de tous les traitements](#la-description-de-tous-les-traitements)
 - [Les commandes pour la compilation](#Les-commandes-pour-la-compilation)  
 - [La présentation des dossiers du projet ](#La-présentation-des-dossiers-du-projet)

## La description de tous les traitements

- **TRAITEMENT D1** : Les 10 conducteurs avec le plus de trajets.
- **TRAITEMENT D2** : Les 10 conducteurs avec la plus grande distance parcourue.
- **TRAITEMENT L**  :    Les 10 trajets les plus longs.
- **TRAITEMENT T** : Les 10 villes avec les plus traversées.
- **TRAITEMENT S** : Statistiques sur les étapes.
## Les commandes pour la compilation

Afin de compiler les differents traitement: 

- Compilez une premiere fois le programme en utilisant la commande suivante `./script.sh data/data.csv`, Après avoir fait cela on peut donc compiler le programme en ajoutant cette fois ci l'option correspondant au traitement de son choix.  
`./script.sh data/data.csv -d1` pour le traitement d1  
`./script.sh data/data.csv -d2` pour le traitement d2  
`./script.sh data/data.csv -l` pour le traitement L  
`./script.sh data/data.csv -t` pour le traitement T  
`./script.sh data/data.csv -S` pour le traitement S  
`./script.sh data/data.csv -h` pour une documentation d'aide sur les fonctionnalités          
Le graphique correspondant au traitement executé s'ouvrira dans une fenetre après l'execution d'une de ces commandes  
Attention, pour les traitements t et s il est nécéssaire d'entrer dans le dossier progc puis executer le make en écrivant simplemant make dans le terminal avant d'executer le script comme précédemment.


## La présentation des dossiers du projet

Le projet est divisé en 4 dossiers  

 - Le dossier temp stocke les resultats écrits des traitementd
 - le dossier progc stocke les programmes C
 - le dossier demo  stocke les résultat chiffrés des traitements
 - le dossier images stocke les graphiques générés par les traitements
