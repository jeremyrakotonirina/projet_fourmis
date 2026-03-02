#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm> //pour min et max
#include <stdlib.h> //pour rand

using namespace std;
#include "fourmis.hpp"
#include "doctest.h"

Fourmi::Fourmi(int indice, Coord C, int clan) : numero{indice}, 
	coordonnees{C}, 
	sucre{false},
	colonie{clan}{
	}

int Fourmi::colo() const{
	return colonie;
}

int Fourmi::num() const{
	return numero;
}

Coord Fourmi::coord() const{
	return coordonnees;
}

bool Fourmi::memeColonie(Fourmi f1) const{
	return f1.colo() == colo();
}
	
bool Fourmi::porteSucre() const{
	return sucre;
}

void Fourmi::prendSucre(){
	if (porteSucre()){
		throw runtime_error ("La fourmi porte déjà du sucre");
	}
	else{
		sucre = true;
	}
}

void Fourmi::poseSucre(){
	if (not(porteSucre())){
		throw runtime_error ("La fourmi ne porte pas de sucre");
	}
	else{
		sucre = false;
	}
}

TEST_CASE("Constructeur"){
	CHECK_FALSE(Fourmi(5, Coord(5, 5),0).porteSucre());
	CHECK(Fourmi(5, Coord(5, 5),0).num() == 5);
	CHECK(Fourmi(5, Coord(5, 5),0).colo() == 0);
	CHECK_THROWS_AS(Fourmi(5, Coord(5, 5),0).poseSucre(), runtime_error);
	Fourmi f = Fourmi(5, Coord(5, 5),0);
	Fourmi f1 = Fourmi(6, Coord(6,5),1);
	CHECK_FALSE(f.memeColonie(f1));
	f.prendSucre();
	CHECK(f.porteSucre());
	CHECK_THROWS_AS(f.prendSucre(), runtime_error);
	CHECK(f.coord().get_line() == 5);
	CHECK(f.coord().get_col() == 5);
}

void Fourmi::deplace(Coord C){
	if (not(voisines(C).contient(coord()))){
		throw runtime_error ("Ce n'est pas une case voisine");
	}else{
		coordonnees = C;
	}
}

TEST_CASE("Déplace"){
	Fourmi f = Fourmi(5, Coord(5, 5),0);
	f.prendSucre();
	CHECK_THROWS_AS(f.deplace(Coord(8,8)), runtime_error);
	CHECK_THROWS_AS(f.deplace(Coord(5,8)), runtime_error);
	CHECK_THROWS_AS(f.deplace(Coord(8,5)), runtime_error);
	f.deplace(Coord(6, 6));
	CHECK(f.coord().get_line() == 6);
	CHECK(f.coord().get_col() == 6);
	
	Fourmi f2 = Fourmi(5, Coord(TAILLEGRILLE, TAILLEGRILLE),0);
	CHECK_THROWS_AS(f2.deplace(Coord(TAILLEGRILLE+1,TAILLEGRILLE+1)), invalid_argument);
}

vector<Fourmi> creeTabFourmis(EnsCoord ec,int clan){
	vector<Fourmi> tabFourmis;
	for(int i = 0 ; i < ec.taille() ; i++){
		tabFourmis.push_back(Fourmi(i, ec.ieme(i),clan));
	}
	return tabFourmis;
}

TEST_CASE("Crée tab Fourmis"){
	Coord a = Coord(5, 5);
	Coord b = Coord(6, 7);
	Coord c = Coord(8, 9);
	EnsCoord ec = EnsCoord({a, b, c});
	vector<Fourmi> tabF = creeTabFourmis(ec,0);
	CHECK(tabF[0].memeColonie(tabF[1]));
	for(size_t i = 0 ; i < tabF.size() ; i++){
		CHECK_FALSE(tabF[i].porteSucre());
		tabF[i].prendSucre();
	}
	for(size_t i = 0 ; i < tabF.size() ; i++){
		CHECK(tabF[i].porteSucre());
	}
}