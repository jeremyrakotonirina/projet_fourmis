#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm> //pour min et max
#include <stdlib.h> //pour rand
#include <random>


using namespace std;

#include "coord.hpp"
#include "doctest.h"



Coord::Coord(int lig, int col){
	if (lig <= TAILLEGRILLE and col <= TAILLEGRILLE and lig >= 0 and col >= 0){
		coordonnees = make_pair(lig, col);
	}
	else{
		throw invalid_argument ("Les coordonnées données ne sont pas valides.");
	}
}


int Coord::get_line() const{
	return coordonnees.first;
}

int Coord::get_col() const{
	return coordonnees.second;
}

TEST_CASE("Classe coord constructeurs et getters"){
	int a=0;
	int b=20;
	Coord C(a,b);
	CHECK(C.get_line()==a);
	CHECK(C.get_line()!=a-1);
	CHECK(C.get_col()==b);
	CHECK(C.get_col()!=b-1);
	CHECK(Coord{a+5,b-6}.get_line()==5);
	CHECK(Coord{a+5,b-6}.get_col()==14);
	CHECK_THROWS_AS(Coord C(-1,15),invalid_argument);
	CHECK_THROWS_AS(Coord C(15,-1),invalid_argument);
	CHECK_THROWS_AS(Coord C(15,TAILLEGRILLE+1),invalid_argument);
}

ostream &operator<<(ostream &out, Coord C){
	out << "(" << C.get_line() << "," << C.get_col() << ")";
	return out;
}

bool operator==(Coord C1, Coord C2){
	return ((C1.get_line() == C2.get_line()) and (C1.get_col() == C2.get_col()));
}

bool operator !=(Coord C1, Coord C2){
	return not(C1 == C2);
}

TEST_CASE("Classe coord opérateurs"){
	ostringstream ch;
	SUBCASE("affiche (0,0)"){
		ch << Coord{0,0};
		CHECK(ch.str()=="(0,0)");
	}
	SUBCASE("affiche (12,3)"){
		ch << Coord{12,3};
		CHECK(ch.str()=="(12,3)");
	}
	Coord a {5,6};
	Coord b {6,5};
	Coord c {6,5};
	CHECK(a!=b);
	CHECK_FALSE(b!=c);
	CHECK(b==c);
	CHECK_FALSE(c==a);
	CHECK_FALSE(a==c);
}
	
		

ostream &operator<<(ostream &out, EnsCoord C){
	for (int i = 0 ; i < C.taille() ; i++){
		out << C.ieme(i) << endl;
	}
	return out;
}

EnsCoord::EnsCoord(vector<Coord> v): EnsembleCord{v}{
}

int EnsCoord::position(Coord C) const{
	int n = -1;
	for(int i = 0 ; i < taille() ; i++){
		if(EnsembleCord[i] == C){
			n = i;
		}
	}
	return n;
}

bool EnsCoord::contient(Coord C) const{
	return position(C) != -1;
}

void EnsCoord::ajoute(Coord C){
	if (contient(C)){
		throw invalid_argument("Déjà présent dans l'ensemble.");
	}
	else{
		EnsembleCord.push_back(C);
	}
}

void EnsCoord::supprime(Coord C){
	if (not(contient(C))){
		throw invalid_argument("Pas présent dans l'ensemble.");
	}
	else{
		EnsembleCord[position(C)] = EnsembleCord[EnsembleCord.size()-1];
	}
	EnsembleCord.pop_back();
}

bool EnsCoord::estVide() const{
	return EnsembleCord.size() == 0;
}

int EnsCoord::taille() const{
	return EnsembleCord.size();
}

Coord EnsCoord::ieme(int n) const{
	return EnsembleCord[n];
}

TEST_CASE("Classe EnsCoord"){
	Coord a {5,6};
	Coord b {3,2};
	Coord c {6,6};
	Coord d {8,7};
	EnsCoord C { {a,b,c,d} };
	
	ostringstream ch;
	ch << C;
	CHECK(ch.str()=="(5,6)\n(3,2)\n(6,6)\n(8,7)\n");
	
	
	CHECK_FALSE(C.estVide());
	CHECK_THROWS_AS(C.ajoute(b),invalid_argument);
	CHECK(C.contient(a));
	C.supprime(a);
	CHECK(C.taille()==3);
	CHECK_THROWS_AS(C.supprime(a),invalid_argument);
	CHECK_FALSE(C.contient(a));
	C.ajoute(a);
	CHECK(C.taille()==4);
	int n = C.taille();
	for(int i = 0; i < n; i++){
		C.supprime(C.ieme(0));
	}

	
	CHECK(C.estVide());
	ch.str(""); //remet ch vide 
	ch << C;
	CHECK(ch.str()=="");
}

EnsCoord voisines(Coord c){
	EnsCoord d {vector <Coord> {} };
	for (int i = max(c.get_line()-1, 0); i <= min(c.get_line()+1, TAILLEGRILLE-1); i++) {
		for (int j = max(c.get_col()-1, 0); j <= min(c.get_col()+1, TAILLEGRILLE-1); j++) {
			if (i != c.get_line() or j != c.get_col()){
				d.ajoute(Coord{i,j});
				}
		}
	}
	return d;
}

TEST_CASE("Voisines"){
	Coord a {1,0};
	Coord b {1,1};
	Coord c {1,2};
	Coord d {2,2};
	Coord e {3, 2};
	Coord f {3, 1};
	Coord g {3, 0};
	Coord h {2, 0};
	EnsCoord C { {a,b,c,d, e, f, g, h} };
	
	CHECK(voisines(Coord{2, 1}).contient(a));
	CHECK(voisines(Coord{2, 1}).contient(b));
	CHECK(voisines(Coord{2, 1}).contient(c));
	CHECK(voisines(Coord{2, 1}).contient(d));
	CHECK(voisines(Coord{2, 1}).contient(e));
	CHECK(voisines(Coord{2, 1}).contient(f));
	CHECK(voisines(Coord{2, 1}).contient(g));
	CHECK(voisines(Coord{2, 1}).contient(h));
	CHECK(voisines(Coord{2, 1}).contient(a));

	CHECK(voisines(Coord{TAILLEGRILLE-1, TAILLEGRILLE-1}).contient(Coord{TAILLEGRILLE-2, TAILLEGRILLE-2}));
	CHECK(voisines(Coord{TAILLEGRILLE-1, TAILLEGRILLE-1}).contient(Coord{TAILLEGRILLE-2, TAILLEGRILLE-1}));
	CHECK(voisines(Coord{TAILLEGRILLE-1, TAILLEGRILLE-1}).contient(Coord{TAILLEGRILLE-1, TAILLEGRILLE-2}));
	
	
	for (int i=0; i<TAILLEGRILLE; i++){
		for (int j=0; j<TAILLEGRILLE; j++){
			if (i==0 or i==TAILLEGRILLE-1){
				if (j==0 or j==TAILLEGRILLE-1) CHECK(voisines(Coord{i,j}).taille()==3);
				else CHECK(voisines(Coord{i,j}).taille()==5);
			}
			else if (j==0 or j==TAILLEGRILLE-1){
				CHECK(voisines(Coord{i,j}).taille()==5);
			}
			else {
				CHECK(voisines(Coord{i,j}).taille()==8);
			}
		}
	}
				
}

Coord EnsCoord::choixHasard() const {
    // Utiliser un moteur de génération de nombres aléatoires
    random_device rd;
    mt19937 gen(rd()); // Utiliser un générateur Mersenne Twister pour la génération de nombres aléatoires

    // Définir la distribution pour générer des indices dans la plage [0, taille())
    uniform_int_distribution<int> distribution(0, taille() - 1);

    // Générer un indice aléatoire
    int indiceAleatoire = distribution(gen);

    // Retourner la coordonnée correspondant à l'indice aléatoire
    return ieme(indiceAleatoire);
}


TEST_CASE("choix hasard"){
	Coord a {2,2};
	Coord b {1,1};
	Coord c {1,2};
	Coord d {2,2};
	Coord e {3, 2};
	Coord f {3, 1};
	Coord g {3, 3};
	Coord h {2, 1};
	EnsCoord C { {a,b,c,d, e, f, g, h} };
	CHECK(voisines(C.choixHasard()).taille() == 8);
	//CHECK(choixHasard(C).get_line() <= 3 and choixHasard(C).get_line() >= 0 and choixHasard(C).get_col() <= 3 and choixHasard(C).get_col() >= 0);
}