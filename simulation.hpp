#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "coord.hpp"
#include "fourmis.hpp"
#include "places.hpp"
#include "grille.hpp"
#include "colonie.hpp"


bool contientSucreVoisins(Grille g, Fourmi f);//Renvoit si una case voisine de celle de f contient du Sucre
bool contientNidVoisins(Grille g, Fourmi f, Colonie c);
bool plusProcheNidVoisins(Grille g, Fourmi f, Colonie c);//Retourne vrai si une voisine de la case où se trouve f est plus proche du nid que elle même.
bool estSurUnePiste(Grille g, Fourmi f, Colonie c);

void comportementFourmis(Grille &g, vector<Fourmi> tabF, Colonie &c); //Règles du comportement des fourmis

#endif