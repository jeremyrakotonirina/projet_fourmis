#ifndef COORD_HPP
#define COORD_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

const int TAILLEGRILLE = 50;
const int NBCOLONIE = 2 ;

class Coord{
	public:
	Coord(int lig, int col); //Constructeur
	//Getters
	int get_line() const;
	int get_col() const;
	
	private:
	pair<int, int> coordonnees;
};



ostream &operator<<(ostream &out, Coord C);

bool operator==(Coord C1, Coord C2);

bool operator !=(Coord C1, Coord C2);


class EnsCoord{
	public:
	EnsCoord(vector<Coord> v);
	bool contient(Coord C) const;
	void ajoute(Coord C);
	void supprime(Coord C);
	bool estVide() const; //Renvoie true si un EnsCord est vide.
	int taille() const; //Renvoie la taille d'un EnsCord (en commençant à 0)
	Coord ieme(int n) const; //Renvoie le ieme élément
	Coord choixHasard() const; //renvoie un élément au hasard dans C
	
	
	private:
	vector<Coord> EnsembleCord;
	int position(Coord C) const; //renvoie le dernier indice de C dans EnsembleCord
};

ostream &operator<<(ostream &out, EnsCoord C); //surcharge d'affichage

EnsCoord voisines(Coord c); //prend en paramètre une coordonnée c et retourne un EnsCoord des voisines de c

#endif