#ifndef SIMULATION2_HPP
#define SIMULATION2_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm>

using namespace std;

#include "coord.hpp"
#include "fourmis.hpp"
#include "places.hpp"
#include "grille.hpp"
#include "colonie.hpp"

void ajoutSucre(Grille &g);
bool contientSucreVoisins(Grille g, Fourmi f);//Renvoit si una case voisine de celle de f contient du Sucre
bool contientNidVoisins(Grille g, Fourmi f, Colonie c);
bool plusProcheNidVoisins(Grille g, Fourmi f, Colonie c);//Retourne vrai si une voisine de la case où se trouve f est plus proche du nid que elle même.
bool estSurUnePiste(Grille g, Fourmi f, Colonie c);
//void Ennemis(Grille &g, vector<Fourmi> &tabF); //"Tuer" Les voisines, en ce cas ne tue qu'une seule voisine si deux fourmis ennemies se rencontrent
void comportementFourmis(Grille &g, vector<Fourmi> &tabF); //Règles du comportement des fourmis


#endif