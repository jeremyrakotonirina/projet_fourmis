#ifndef COLONIE_HPP
#define COLONIE_HPP
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "fourmis.hpp"
#include "coord.hpp"

class Colonie{
	public:
	//Constructeurs
	Colonie (int num);
	
	//Getters
	int id() const; //renvoie l'identifiant
	vector <Fourmi> listeF() const;
	//Méthodes
	int nbFourmis() const; //renvoie le nombre de fourmis

	Fourmi ieme(int indice) const;
	void rangeFourmi(Fourmi f); //fonction pour remplacer la fourmi, ce qui veut dire que la fourmi doit déjà être présente
	void supprimeFourmi(Fourmi f);
	void ajoutFourmi(Fourmi f);
	void ajoutSucre(); //rajoute du sucre dans le stock
	void supprSucre();
	void ajoutNid(EnsCoord ec); //ajoute les positions de nid
	bool naissance(); //s'il y a plus de 10 stocks de sucre
	bool presenceNid(Coord C); // s'il y a un élément de nid à cet endroit
	
	
	
	private:
	vector<Fourmi> tabF;
	EnsCoord positionNid;
	int stockSucre;
	int identifiant;
};

#endif
	