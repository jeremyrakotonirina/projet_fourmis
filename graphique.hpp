#ifndef GRAPHIQUE_HPP
#define GRAPHIQUE_HPP
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
#include "simulation2.hpp"

void dessinerGrille(Grille g, vector<Fourmi> tabF);

#endif