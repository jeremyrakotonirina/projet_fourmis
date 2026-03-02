#ifndef FOURMIS_HPP
#define FOURMIS_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include "coord.hpp"

using namespace std;

class Fourmi{
	public:
	Fourmi(int indice, Coord C, int clan);
	int  num() const;
	int colo() const;
	Coord coord() const;
	bool memeColonie(Fourmi f1) const; //s'ils sont de la même colonie
	bool porteSucre() const;
	void prendSucre();
	void poseSucre();
	void deplace(Coord C);
	
	private:
	int numero;
	Coord coordonnees;
	bool sucre;
	int colonie;
};

vector<Fourmi> creeTabFourmis(EnsCoord ec, int clan); 

#endif