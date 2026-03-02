#ifndef PLACES_HPP
#define PLACES_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "coord.hpp"
#include "fourmis.hpp"
#include "colonie.hpp"

class Place{
	public:
	//Constructeur
	Place(Coord C);
	Place();
	
	//Getters
	Coord coord() const; 
	int pheroSucre(Colonie c) const;
	float pheroNid(Colonie c) const;
	int numeroFourmi() const; 
	
	//Méthodes
	bool contientSucre() const;
	bool contientNid() const;
	bool estSurUnePiste(Colonie c) const; //la place se trouve sur une piste vers du sucre, càd qu'il y a du phéronome de sucre de la colonie
	bool contientFourmi() const; 
	bool estVide() const; //renvoie vrai si la place ne contient ni sucre, ni élément de nid, ni fourmi.

	
	void poseSucre();
	void enleveSucre();
	void poseNid(Colonie c); //transforme en élément de nid
	void poseFourmi(Fourmi f);
	void enleveFourmi(Fourmi f);
	void posePheroNid(float intensite, Colonie c);
	void posePheroSucre(Colonie c); //avec l'intensité maximale
	void diminuePheroSucre(); //diminue de -5
	
	private:
	//Attributs
	Coord coords;
	array<int, NBCOLONIE> phSucre; //phSucre[0] ça retourne le phSucre de la colonie 0, ... 1 
	int sucre; //nombre de bloc de sucre à l'intérieur de la place
	array<float, NBCOLONIE> phNid;
	bool caseNid; //si c'est un élément de nid
	int numFourmi; // numéro de fourmi sur la place et -1 s'il n'y en a pas
};

void deplaceFourmi(Fourmi f, Place &p1, Place &p2); //déplace de p1 vers p2

bool estPlusProcheNid(Place p1, Place p2, Colonie c); //retourne vrai si p1 est plus proche du nid que p2




#endif