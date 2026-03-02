#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm> //pour min et max


using namespace std;

#include "grille.hpp"
#include "doctest.h"

Grille::Grille() {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            grille[i][j] = Place(Coord(i, j));
        }
    }
}

Place Grille::chargePlace(Coord C) const{
	return grille[C.get_line()][C.get_col()];
}

TEST_CASE("ChargePlace"){
	Grille g = Grille();
	CHECK(g.chargePlace(Coord(0,0)).estVide());
	CHECK_FALSE(g.chargePlace(Coord(0, 0)).contientSucre());
	CHECK_FALSE(g.chargePlace(Coord(10, 15)).contientSucre());
	CHECK((g.chargePlace(Coord(0, 0)).pheroSucre(Colonie {0}) == 0));
}

void Grille::rangePlace(Place p){
	grille[p.coord().get_line()][p.coord().get_col()]=p;
}

TEST_CASE("RangePlace"){
	Grille g = Grille();
	
	Place p = Place(Coord(5, 6));
	CHECK_FALSE(g.chargePlace(Coord(5, 6)).contientSucre());
	p.poseSucre();
	g.rangePlace(p);
	CHECK(g.chargePlace(Coord(5, 6)).contientSucre());
	
	p.enleveSucre();
	g.rangePlace(p);
	CHECK_FALSE(g.chargePlace(Coord(5, 6)).contientSucre());
	
	p.poseFourmi(Fourmi(5, Coord(5, 6),0));
	g.rangePlace(p);
	CHECK(g.chargePlace(Coord(5, 6)).contientFourmi());
}

void Grille::linearisePheroNid(){
	for(float t = 1 ; t <= TAILLEGRILLE ; t++){
		for(int i = 0 ; i<TAILLEGRILLE ; i++){
			for(int j = 0 ; j<TAILLEGRILLE ; j++){
				Coord C = Coord{i, j};
				Place p = chargePlace(C);
				for (int z = 0; z<NBCOLONIE ; z++){
					if(p.pheroNid(Colonie {z}) < 1){
						float m = 0.;
						for(int k = 0 ; k < voisines(C).taille() ; k++){
							Place p1=chargePlace(voisines(C).ieme(k));
							if(p1.pheroNid(Colonie {z}) > m){
								m = p1.pheroNid(Colonie {z});
							}
						}
						p.posePheroNid(max(m - 1.0/t, 0.0),Colonie{z});
						rangePlace(p);
					}
				}
			}
		}
	}
}


TEST_CASE("LinéarisePheroNid"){
	Grille g = Grille();
	for(int i = 0 ; i < TAILLEGRILLE ; i++){
		for(int j = 0 ; j < TAILLEGRILLE ; j++){
			for (int z = 0; z<NBCOLONIE ; z++){
				CHECK_FALSE(g.chargePlace(Coord(i, j)).estSurUnePiste(Colonie(z))) ;
			}
		}
	}
	
	Place p = Place(Coord(5, 6));
	p.poseNid(Colonie {0});
	CHECK_FALSE(g.chargePlace(Coord(5, 6)).contientSucre());
	g.rangePlace(p);
	CHECK(g.chargePlace(Coord(5, 6)).contientNid());
	CHECK(g.chargePlace(Coord(5, 6)).pheroNid(Colonie {0}) > 0);
	
	Place p1 = Place(Coord(10,6));
	p1.poseNid(Colonie {1});
	g.rangePlace(p1);
	
	
	g.linearisePheroNid();
	CHECK(g.chargePlace(Coord(4, 6)).pheroNid(Colonie {0}) > 0);
	CHECK(g.chargePlace(Coord(4, 6)).pheroNid(Colonie {0}) < 1.2);
	CHECK(g.chargePlace(Coord(6, 6)).pheroNid(Colonie {1}) > 0);
	CHECK(g.chargePlace(Coord(6, 6)).pheroNid(Colonie {1}) < 1.2);

	CHECK(g.chargePlace(Coord(5, 7)).pheroNid(Colonie {0}) > 0);
	CHECK(g.chargePlace(Coord(5, 7)).pheroNid(Colonie {0}) < 1.2);
	CHECK(g.chargePlace(Coord(4, 7)).pheroNid(Colonie {1}) > 0);
	
}


void Grille::diminuePheroSucre(){
	for(int i = 0 ; i<TAILLEGRILLE ; i++){
		for(int j = 0 ; j<TAILLEGRILLE ; j++){
			Coord C = Coord(i, j);
			Place p = chargePlace(C);
			p.diminuePheroSucre();
			rangePlace(p);
			}
		}
}

TEST_CASE("DiminuePheroSucre"){
	Grille g = Grille();
	
	g.diminuePheroSucre();
	Place p = Place(Coord(5, 6));
	CHECK_FALSE(g.chargePlace(Coord(5, 6)).contientSucre());
	
	p.poseSucre();
	p.poseSucre();
	g.rangePlace(p);
	CHECK(g.chargePlace(Coord(6, 6)).pheroSucre( Colonie {0}) == 0);
	g.diminuePheroSucre();
	CHECK_FALSE(g.chargePlace(Coord(5, 6)).pheroSucre( Colonie {1}) == 1);
}

void placeNid(Grille &g, EnsCoord ec, Colonie c){
	for (int i=0; i<ec.taille(); i++){
		Place p = g.chargePlace(ec.ieme(i));
		p.poseNid(c);
		g.rangePlace(p);
	}
}

TEST_CASE("fonction PlaceNid"){
	Grille g;
	Colonie c1{1};
	EnsCoord E={{Coord{1,1},Coord{1,2},Coord{1,3}}};
	placeNid(g,E, c1);
	CHECK_FALSE(g.chargePlace(Coord(1, 4)).contientNid());
	for (int i=1; i<=3; i++){
		Place p1=g.chargePlace(Coord {1,i});
		CHECK(p1.contientNid());
	}
}

void placeSucre(Grille &g, EnsCoord ec){
	for (int i=0; i<ec.taille(); i++){
		Place p = g.chargePlace(ec.ieme(i));
		p.poseSucre();
		g.rangePlace(p);
	}
}

TEST_CASE("Fonction placeSucre"){
	Grille g;
	EnsCoord E{{Coord{1,1},Coord{1,2},Coord{1,3}}};
	placeSucre(g,E);
	CHECK_FALSE(g.chargePlace(Coord(1, 4)).contientSucre());
	for (int i=1; i<=3; i++){
		Place p1=g.chargePlace(Coord {1,i});
		CHECK(p1.contientSucre());
	}
}	

void placeFourmis(Grille& g, vector<Fourmi> tabF){
	for(size_t i = 0 ; i < tabF.size() ; i++){
		Place p = g.chargePlace(tabF[i].coord());
		p.poseFourmi(tabF[i]);
		g.rangePlace(p);
	}
}

TEST_CASE("Fonction placeFourmis"){
	Grille g ;
	
	Coord a = Coord(5, 5);
	Coord b = Coord(6, 7);
	Coord c = Coord(8, 9);
	
	vector<Fourmi> tabF = creeTabFourmis(EnsCoord({a, b, c}),0);
	
	placeFourmis(g, tabF);

	CHECK_FALSE(g.chargePlace(Coord(5, 4)).contientFourmi());

	CHECK(g.chargePlace(Coord(5, 5)).contientFourmi());
	CHECK(g.chargePlace(Coord(5, 5)).numeroFourmi() == 0);

	CHECK(g.chargePlace(Coord(6, 7)).contientFourmi());
	CHECK(g.chargePlace(Coord(6, 7)).numeroFourmi() == 1);

	CHECK(g.chargePlace(Coord(8, 9)).contientFourmi());
	CHECK(g.chargePlace(Coord(8, 9)).numeroFourmi() == 2);

}

Grille initialiseGrille(vector<Fourmi> tabF, EnsCoord ElemSucre, vector<EnsCoord> ElemNid){
	Grille g;
	for (int i=0; i< NBCOLONIE; i++){
		placeNid(g, ElemNid[i], Colonie(i));
	}
	placeSucre(g, ElemSucre);
	placeFourmis(g, tabF);
	g.linearisePheroNid();
	return g;
}

ostringstream afficherGrille(Grille g, vector<Fourmi> tabF){
	ostringstream out;
	for(int i = 0 ; i < TAILLEGRILLE ; i++){
		for(int j = 0 ; j < TAILLEGRILLE ; j++){
			if(g.chargePlace(Coord(i, j)).contientNid()){
				out << "|N";
			}
			else if(g.chargePlace(Coord(i, j)).contientFourmi()){
				for(size_t k = 0 ; k < tabF.size() ; k++){
					if(tabF[k].coord() == Coord(i, j)){
						if(tabF[k].porteSucre()){
							out << "|F";
						}
						else{
							out << "|f";
						}
					}
				}
			}
			else if(g.chargePlace(Coord(i, j)).contientSucre()){
				out << "|S"; 
			}
			else{
				out << "| ";
			}
		}
		out << "|" << endl;
	}
	return out;
}

EnsCoord peutSeDeplacer(Grille g, Fourmi f){
	EnsCoord VoisinesF = voisines(f.coord());
	vector<Coord> VoisinesCompatibles;
	
	for(int i = 0 ; i < VoisinesF.taille() ; i++){
		if(g.chargePlace(VoisinesF.ieme(i)).estVide()){
			VoisinesCompatibles.push_back(VoisinesF.ieme(i));
		}
	}
	if (VoisinesCompatibles.size() == 0){
		return EnsCoord({f.coord()});
	}
	else{
		return EnsCoord(VoisinesCompatibles);
	}
}

void deplacerFourmi(Grille &g, Fourmi &f, Place p1, Place p2){
	if(not(p2.estVide())){
		throw invalid_argument("La place p2 contient déjà une fourmie");
	}
	
	if(not(p1.contientFourmi())){
		throw invalid_argument("La place p1 ne contient pas de fourmi");
	}
	
	f.deplace(p2.coord());
	Place P1 = g.chargePlace(p1.coord());
	P1.enleveFourmi(f);
	g.rangePlace(P1);
	
	Place P2 = g.chargePlace(p2.coord());
	P2.poseFourmi(f);
	g.rangePlace(P2);
}

void deplacerAleatoirement(Grille &g, vector<Fourmi> &tabF){
	for(size_t i = 0 ; i < tabF.size() ; i++){
		Place p = g.chargePlace(tabF[i].coord());
		deplacerFourmi(g, tabF[i], p, peutSeDeplacer(g, tabF[i]).choixHasard());
		integrite(tabF, g);
	}
}




void integrite(vector <Fourmi> tabF, Grille g){
	for (int i=0; i<int(tabF.size()); i++){
		if (tabF[i].num() != i) throw runtime_error ("le numéro d'une des fourmis n'est pas en adéquation avec son indice dans le vector");
		Place p= g.chargePlace(tabF[i].coord());
		if (p.estVide()) throw runtime_error ("une des fourmis pense être dans une place vide");
	}
	for (int i=0; i<TAILLEGRILLE; i++){
		for (int j=0; j<TAILLEGRILLE; j++){
			Place p=g.chargePlace(Coord {i,j});
			if (p.coord().get_line() != i or p.coord().get_col() != j){
				cout << i << endl <<j << endl <<p.coord().get_line() <<endl <<p.coord().get_col() << endl;
				throw runtime_error ("erreur coordonnées des places dans la grille");
			}
		}
	}
}


TEST_CASE("fonction initialiseGrille et integrite"){
	EnsCoord sucre{{Coord{1,1},Coord{1,2},Coord{1,3}}};
	vector<EnsCoord> nid = {EnsCoord {{Coord{5,1},Coord{5,2},Coord{5,3}}},EnsCoord {{Coord{6,1},Coord{6,2},Coord{7,1}}}};
	vector <Fourmi> F = creeTabFourmis(EnsCoord {{Coord{6,1},Coord{6,2},Coord{6,3}}},0);
	Grille g = initialiseGrille(F,sucre,nid);
	integrite(F,g);
	for (int i=1; i<=3; i++){
		Place p=g.chargePlace(Coord {6,i});
		CHECK(p.contientFourmi());
		Place p1=g.chargePlace(Coord {5,i});
		CHECK(p1.contientNid());
		Place p2=g.chargePlace(Coord {1,i});
		CHECK(p2.contientSucre());
	}
}

/**
TEST_CASE("Initialise Grille"){
	Grille g = Grille();
	vector<Fourmi> tabF;
	vector<Coord> ElemSucre;
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-15, 15), Coord(TAILLEGRILLE-16, 15), Coord(TAILLEGRILLE-15, 16), Coord(TAILLEGRILLE-16, 16)}), //Nid du bas à gauche
	EnsCoord({Coord(15, TAILLEGRILLE-15), Coord(15, TAILLEGRILLE-16), Coord(16, TAILLEGRILLE-15), Coord(16, TAILLEGRILLE-16)})}; //Nid du haut à droite
	
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	int n = 0;
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-17, 14+i), 1));
		n++;
	}
	
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-16, 14), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-15, 14), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-16, 17), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-15, 17), 1));
	n++;
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-14, 14+i), 1));
		n++;
	}
	
	//Fourmis de la deuxième colonnie
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(14, TAILLEGRILLE-17+i), 2));
		n++;
	}
	
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-17), 2));
	n++;
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-14), 2));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-17), 2));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-14), 2));
	n++;
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(17, TAILLEGRILLE-17+i), 2));
		n++;
	}
	
	vector<Coord> CarreHautGauche;
	vector<Coord> CarreBasDroite;
	for(int i = 0 ; i < TAILLEGRILLE/2 ; i++){
		for(int j = 0 ; j < TAILLEGRILLE/2 ; j++){
			CarreHautGauche.push_back(Coord(i, j));
		}
	}
	
	for(int i = 2*TAILLEGRILLE/4 ; i < TAILLEGRILLE ; i++){
		for(int j = 2*TAILLEGRILLE/4 ; j < TAILLEGRILLE ; j++){
			CarreBasDroite.push_back(Coord(i, j));
		}
	}
	
	EnsCoord CHG = EnsCoord(CarreHautGauche);
	EnsCoord CBD = EnsCoord(CarreBasDroite);
	
	for (int i=0; i<15; i++){
		ElemSucre.push_back(voisines(CHG.choixHasard()).choixHasard());
		ElemSucre.push_back(voisines(CBD.choixHasard()).choixHasard());
	}
	
	g = initialiseGrille(tabF, EnsCoord(ElemSucre), ElemNid);
	
	for(int i = 0 ; i < 30; i++){
		deplacerAleatoirement(g, tabF);
		cout << afficherGrille(g, tabF).str();
	}
}
**/


Grille initialiseGrille2(){
	vector<Fourmi> tabF;
	vector<Coord> ElemSucre;
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-15, 15), Coord(TAILLEGRILLE-16, 15), Coord(TAILLEGRILLE-15, 16), Coord(TAILLEGRILLE-16, 16)}), //Nid du bas à gauche
	EnsCoord({Coord(15, TAILLEGRILLE-15), Coord(15, TAILLEGRILLE-16), Coord(16, TAILLEGRILLE-15), Coord(16, TAILLEGRILLE-16)})}; //Nid du haut à droite
	
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(TAILLEGRILLE-17, 14+i), 0));
	}
	

	tabF.push_back(Fourmi(4, Coord(TAILLEGRILLE-16, 14), 0));
	tabF.push_back(Fourmi(5, Coord(TAILLEGRILLE-15, 14), 0));
	tabF.push_back(Fourmi(6, Coord(TAILLEGRILLE-16, 17), 0));
	tabF.push_back(Fourmi(7, Coord(TAILLEGRILLE-15, 17), 0));
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(TAILLEGRILLE-14, 14+i), 0));
	}
	
	//Fourmis de la deuxième colonnie
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(14, TAILLEGRILLE-17+i), 1));
	}
	
	tabF.push_back(Fourmi(4, Coord(115, TAILLEGRILLE-17),1));
	tabF.push_back(Fourmi(5, Coord(15, TAILLEGRILLE-14),1));
	tabF.push_back(Fourmi(6, Coord(16, TAILLEGRILLE-17),1));
	tabF.push_back(Fourmi(7, Coord(16, TAILLEGRILLE-14),1));
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(14, TAILLEGRILLE-17+i), 1));
	}
	
	vector<Coord> CarreHautGauche;
	vector<Coord> CarreBasDroite;
	for(int i = 0 ; i < TAILLEGRILLE/2 ; i++){
		for(int j = 0 ; j < TAILLEGRILLE/2 ; j++){
			CarreHautGauche.push_back(Coord(i, j));
		}
	}
	
	for(int i = 2*TAILLEGRILLE/4 ; i < TAILLEGRILLE ; i++){
		for(int j = 2*TAILLEGRILLE/4 ; j < TAILLEGRILLE ; j++){
			CarreBasDroite.push_back(Coord(i, j));
		}
	}
	
	EnsCoord CHG = EnsCoord(CarreHautGauche);
	EnsCoord CBD = EnsCoord(CarreBasDroite);
	
	for (int i=0; i<15; i++){
		ElemSucre.push_back(voisines(CHG.choixHasard()).choixHasard());
		ElemSucre.push_back(voisines(CBD.choixHasard()).choixHasard());
	}
	
	return initialiseGrille(tabF, EnsCoord(ElemSucre), ElemNid);
}

/**
ostream &operator<<(ostream &out, Grille g){
	for(int i = 0 ; i < TAILLEGRILLE ; i++){
		for(int j = 0 ; j < TAILLEGRILLE ; j++){
			if(g.chargePlace(Coord(i, j)).contientNid()){
				out << "|N";
			}
			else if(g.chargePlace(Coord(i, j)).contientFourmi()){
				out << "|f";
			}
			else if(g.chargePlace(Coord(i, j)).contientSucre()){
				out << "|S"; 
			}
			else{
				out << "| ";
			}
		}
		out << "|" << endl;
	}
	return out;
}

TEST_CASE("surcharge grille et initialisegrille2"){
	Grille g= initialiseGrille2();
	cout << g;
}

void deplacerFourmi(Grille &g, Fourmi &f, Place p1, Place p2){
	if(not(p2.estVide())){
		throw invalid_argument("La place p2 contient déjà une fourmie");
	}
	
	if(not(p1.contientFourmi())){
		throw invalid_argument("La place p1 ne contient pas de fourmi");
	}
	
	f.deplace(p2.coord());
	Place P1 = g.chargePlace(p1.coord());
	P1.enleveFourmi(f);
	g.rangePlace(P1);
	
	Place P2 = g.chargePlace(p2.coord());
	P2.poseFourmi(f);
	g.rangePlace(P1);
	g.rangePlace(P2);
}


EnsCoord peutSeDeplacer(Grille g, Fourmi f){
	EnsCoord VoisinesF = voisines(f.coord());
	vector<Coord> VoisinesCompatibles;
	
	for(int i = 0 ; i < VoisinesF.taille() ; i++){
		if(g.chargePlace(VoisinesF.ieme(i)).estVide()){
			VoisinesCompatibles.push_back(VoisinesF.ieme(i));
		}
	}
	if (VoisinesCompatibles.size() == 0){
		return EnsCoord({f.coord()});
	}
	else{
		return EnsCoord(VoisinesCompatibles);
	}
}

**/