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
- **`simulation2.hpp` / `simulation2.cpp`** : logique principale de simulation (version(s) différentes).
- **`coord.hpp` / `coord.cpp`** : gestion des coordonnées sur la grille.
- **`affichage.cpp`** : fonctions d’affichage (console et/ou graphique).
- **`test.cpp`** : fichiers de test utilisant `doctest.h`.
- **`makefile`** : script de compilation avec `make`.


## Prérequis

- **Compilateur C++** compatible C++11 ou plus récent (par exemple `g++` ou `clang++`).
- **make** installé (sur Windows, via MinGW, MSYS2 ou WSL par exemple).
- **Bibliothèqe imagemagick** installé (commande sudo apt install imagemagick).

## Compilation
Depuis la racine du projet :
- `make affichage`

produit un fichier `movie.gif` représentant la simulation et exécute également les tests.



