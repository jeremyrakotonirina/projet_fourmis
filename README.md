# Projet de simulation de fourmis

Ce projet est une **simulation de colonie de fourmis** écrite en C++.  
Il met en scène des fourmis se déplaçant sur une grille, interagissant avec leur environnement (grille, colonie, lieux, etc.) pour modéliser un comportement collectif.

## Structure du projet

Les principaux fichiers sont :

- **`fourmis.hpp` / `fourmis.cpp`** : définition et implémentation des fourmis.
- **`colonie.hpp` / `colonie.cpp`** : gestion de la colonie.
- **`grille.hpp` / `grille.cpp`** : représentation de la grille de simulation.
- **`places.hpp` / `places.cpp`** : gestion des différents lieux de la simulation.
- **`graphique.hpp` / `graphique.cpp`** : affichage graphique ou gestion de la sortie visuelle.
- **`simulation.hpp` / `simulation.cpp` / `simulation2.hpp` / `simulation2.cpp`** : logique principale de simulation (version(s) différentes).
- **`coord.hpp` / `coord.cpp`** : gestion des coordonnées sur la grille.
- **`affichage.cpp`** : fonctions d’affichage (console et/ou graphique).
- **`test.cpp`** : fichiers de test utilisant `doctest.h`.
- **`makefile`** : script de compilation avec `make`.

## Prérequis

- **Compilateur C++** compatible C++11 ou plus récent (par exemple `g++` ou `clang++`).
- **make** installé (sur Windows, via MinGW, MSYS2 ou WSL par exemple).
- **Bibliothèqe imagemagick** installé (commande sudo apt install imagemagick).

Compilation
Depuis la racine du projet (là où se trouve le makefile) :

### Dépendances de test - doctest (fichier unique doctest.h) est déjà inclus dans le projet, aucune installation externe n’est nécessaire. ## Structure du projet Les principaux fichiers sont : fourmis.hpp / fourmis.cpp (définition et comportement des fourmis), colonie.hpp / colonie.cpp (gestion de la colonie), grille.hpp / grille.cpp (représentation de la grille de simulation), places.hpp / places.cpp (gestion des différents lieux : nourriture, nid, etc.), graphique.hpp / graphique.cpp (gestion de la sortie graphique / génération des .ppm), simulation2.hpp / simulation2.cpp (logique principale de simulation), coord.hpp / coord.cpp (gestion des coordonnées), affichage.cpp (lancement de la simulation / affichage), test.cpp (tests unitaires avec doctest), doctest.h (bibliothèque de test), makefile (script de compilation). ## Compilation Depuis la racine du projet (là où se trouve le makefile) : ### Construire les tests make tests → produit un exécutable tests (ou tests.exe). ### Construire l’exécutable de simulation / affichage make affichage → produit un exécutable affichage (ou affichage.exe). Remarque : selon la version de ton makefile, la cible affichage peut ou non lancer automatiquement ./affichage et convert. Si tu ne veux pas d’exécution automatique, commente ou supprime ces lignes dans le makefile. ### Nettoyage make clean → supprime les fichiers objets (*.o), les exécutables listés dans EXEC_FILES (tests, affichage), ainsi que movie.gif et les images img* si la cible clean les gère. ## Exécution ### Lancer les tests Sous Linux : ./tests ; sous Windows / PowerShell : .\tests.exe. Les tests utilisent doctest et affichent un récapitulatif (nombre de cas de test, assertions, etc.). ### Lancer la simulation Une fois affichage compilé : sous Linux ./affichage, sous Windows / PowerShell .\affichage.exe. La simulation génère une série d’images imgXXXX.ppm dans le répertoire courant et peut, selon le makefile, être suivie d’un appel à convert pour produire movie.gif. Tu peux ensuite ouvrir les *.ppm dans une visionneuse compatible ou ouvrir movie.gif pour voir l’animation de la colonie. ## Génération manuelle du gif (optionnelle) Si ImageMagick est installé, tu peux créer le gif à partir des images *.ppm générées avec : convert -scale 300 -delay 10 img*.ppm movie.gif. -scale 300 redimensionne les images (modifiable) et -delay 10 règle le délai entre les images. Pour nettoyer les images intermédiaires : sous Linux rm img*, sous PowerShell del img*. ## Utilisation et paramètres Le comportement détaillé (taille de la grille, nombre de fourmis, durée de la simulation, etc.) est défini principalement dans simulation2.cpp, graphique.cpp et affichage.cpp. Tu peux documenter ici les constantes / paramètres que tu modifies souvent (par exemple TAILLE_GRILLE, NB_FOURMIS, nombre d’itérations, etc.). ## Organisation du code - Modularité : chaque composant (fourmis, colonie, grille, lieux, etc.) possède ses propres fichiers *.hpp / *.cpp. - Tests unitaires : test.cpp + doctest.h assurent la non-régression du noyau de simulation. ## Améliorations possibles - Rendre la taille de la grille, le nombre de fourmis et la durée de la simulation configurables via un fichier ou des arguments de ligne de commande. - Ajouter une interface graphique temps réel (par exemple avec SDL, SFML, Qt). - Produire des statistiques et graphiques (chemins, densité de nourriture, etc.). - Optimiser la génération des images/gifs pour de grandes simulations. ## Auteur(s) Ton nom / vos noms, contact ou lien GitHub si souhaité.
