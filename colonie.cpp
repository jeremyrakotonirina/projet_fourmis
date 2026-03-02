#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "colonie.hpp"
#include "doctest.h"

Colonie::Colonie(int num): 
	positionNid{ {} },
	stockSucre{0},
	identifiant {num}{
	}

int Colonie::id() const{
	return identifiant;
}
vector <Fourmi> Colonie::listeF() const{
	return tabF;
}
int Colonie::nbFourmis() const{
	return tabF.size();
}

Fourmi Colonie::ieme(int indice) const{
	return tabF[indice];
}

void Colonie::rangeFourmi(Fourmi f){
	tabF[f.num()]=f;
}

void Colonie::supprimeFourmi(Fourmi f){
	tabF.erase(tabF.begin()+f.num());
}

void Colonie::ajoutFourmi(Fourmi f){
	tabF.push_back(f);
}

void Colonie::ajoutSucre(){
	stockSucre++;
}

void Colonie::supprSucre(){
	stockSucre--;
}

void Colonie::ajoutNid(EnsCoord ec){
	for (int i=0; i<ec.taille(); i++){
		positionNid.ajoute(ec.ieme(i));
	}
}

bool Colonie::naissance(){
	return stockSucre > 10;
}

bool Colonie::presenceNid(Coord C){
	return positionNid.contient(C);
}

TEST_CASE("classe colonie"){
	Colonie c {0};
	Colonie c1 {1};
	CHECK(c.id()==0);
	CHECK(c.nbFourmis()==0);
	CHECK_FALSE(c.presenceNid(Coord {1,1}));
	CHECK_FALSE(c.naissance());
	Fourmi f {0, Coord {1,1}, 0};
	Fourmi f2 {1, Coord {1,2},1};
	c.ajoutFourmi(f);
	c.ajoutFourmi(f2);
	f2.deplace(Coord {1,3});
	c.rangeFourmi(f2);
	CHECK(c.ieme(0).colo() == 0);
	CHECK(c.ieme(1).coord() == Coord {1,3});
	CHECK(c.nbFourmis()==2);
	c.supprimeFourmi(f);
	CHECK(c.nbFourmis()==1);
	CHECK(c.ieme(0).colo() == 1);
	c.ajoutNid(EnsCoord {{Coord {5,5}, Coord {5,6}, Coord {6,5}, Coord {6,6}}});
	CHECK(c.presenceNid(Coord {5,5}));
	for (size_t i=0; i<11; i++){
		c.ajoutSucre();
	}
	CHECK(c.naissance());
	for (size_t i=0; i<5; i++){
		c.supprSucre();
	}
	CHECK_FALSE(c.naissance());
}
	
	
	
	