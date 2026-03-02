#ifndef GRILLE_HPP
#define GRILLE_HPP
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
#include "colonie.hpp"

class Grille{
	public:
	Grille(); //Constructeur
	
	Place chargePlace(Coord C) const; //getter
	void rangePlace(Place p); //setter
	void linearisePheroNid(); //distribue les phéronomes de nid en fonction de là où y a le nid
	void diminuePheroSucre();
	
	private:
	array<array<Place, TAILLEGRILLE>, TAILLEGRILLE> grille;
};

void placeNid(Grille &g, EnsCoord ec, Colonie c); //place des nids à toutes les places de coordonnées présentes dans ec

void placeSucre(Grille &g, EnsCoord ec); //place du sucre à toutes les places de coordonnées présentes dans ec

void placeFourmis(Grille &g, vector<Fourmi> tabF); //place toutes les fourmis de tabF dans la grille g

EnsCoord peutSeDeplacer(Grille g, Fourmi f); //Retourne les cases voisines de la f où elle peut se déplacer

ostringstream afficherGrille(Grille g, vector<Fourmi> tabF);
Grille initialiseGrille(vector<Fourmi> tabF, EnsCoord ElemSucre, vector<EnsCoord> ElemNid); //charge une grille vide, l’initialise en plaçant les fourmis, le sucre et le nid, puis elle linéarise les phéromones de nid et transmet le grille en résultat.
Grille initialiseGrille2(); //initialise une grille déjà faite, comme dans le pdf du projet

void integrite(vector <Fourmi> tabF, Grille g); //vérifie l'intégrité de la modélisation à chaque tour d'itératioon
void deplacerAleatoirement(Grille &g, vector<Fourmi> &tabF);
ostream &operator<<(ostream &out, Grille g);

void deplacerFourmi(Grille &g, Fourmi &f, Place p1, Place p2);

EnsCoord peutSeDeplacer(Grille g, Fourmi f); //Retourne les cases voisines de la f où elle peut se déplacer

#endif