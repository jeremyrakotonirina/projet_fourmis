#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "simulation.hpp"
#include "doctest.h"


void deplacerAleatoirement(Grille &g, vector<Fourmi> tabF, Colonie &c){
	for(size_t i = 0 ; i < tabF.size() ; i++){
		Place p = g.chargePlace(tabF[i].coord());
		deplacerFourmi(g, tabF[i], p, peutSeDeplacer(g, tabF[i]).choixHasard());
		integrite(tabF, g);
		c.rangeFourmi(tabF[i]);
	}
}

/**
TEST_CASE("DeplacerAlatoirement"){
	vector<Fourmi> tabF;
	Colonie c0 {0};
	Colonie c1 {1};
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-5, 5), Coord(TAILLEGRILLE-6, 5), Coord(TAILLEGRILLE-5, 6), Coord(TAILLEGRILLE-6, 6)}), //Nid du bas à gauche
	EnsCoord({Coord(5, TAILLEGRILLE-5), Coord(5, TAILLEGRILLE-6), Coord(6, TAILLEGRILLE-5), Coord(6, TAILLEGRILLE-6)})};
	c0.ajoutNid(ElemNid[0]);
	c1.ajoutNid(ElemNid[1]);
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(TAILLEGRILLE-7, 4+i),0));
		c0.ajoutFourmi(Fourmi(i, Coord(TAILLEGRILLE-7, 4+i),0));
	}
	
	tabF.push_back(Fourmi(4, Coord(TAILLEGRILLE-6, 4),0));
	c0.ajoutFourmi(Fourmi(4, Coord(TAILLEGRILLE-6, 4),0));
	tabF.push_back(Fourmi(5, Coord(TAILLEGRILLE-5, 4),0));
	c0.ajoutFourmi(Fourmi(5, Coord(TAILLEGRILLE-5, 4),0));

	tabF.push_back(Fourmi(6, Coord(TAILLEGRILLE-6, 7),0));
	c0.ajoutFourmi(Fourmi(6, Coord(TAILLEGRILLE-6, 7),0));
	tabF.push_back(Fourmi(7, Coord(TAILLEGRILLE-5,7 ),0));
	c0.ajoutFourmi(Fourmi(7, Coord(TAILLEGRILLE-5,7 ),0));
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(TAILLEGRILLE-4, 4+i),0));
		c0.ajoutFourmi(Fourmi(8+i, Coord(TAILLEGRILLE-4, 4+i),0));
	}
	
	//Fourmis de la deuxième colonnie
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(4, TAILLEGRILLE-7+i),1));
		c1.ajoutFourmi(Fourmi(i, Coord(4, TAILLEGRILLE-7+i),1));
	}
	
	tabF.push_back(Fourmi(4, Coord(5, TAILLEGRILLE-7),1));
	c1.ajoutFourmi(Fourmi(4, Coord(5, TAILLEGRILLE-7),1));

	tabF.push_back(Fourmi(5, Coord(5, TAILLEGRILLE-4),1));
	c1.ajoutFourmi(Fourmi(5, Coord(5, TAILLEGRILLE-4),1));
	tabF.push_back(Fourmi(6, Coord(6, TAILLEGRILLE-7),1));
	c1.ajoutFourmi(Fourmi(6, Coord(6, TAILLEGRILLE-7),1));

	tabF.push_back(Fourmi(7, Coord(6, TAILLEGRILLE-4),1));
	c1.ajoutFourmi(Fourmi(7, Coord(6, TAILLEGRILLE-4),1));

	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(7, TAILLEGRILLE-7+i),1));
		c1.ajoutFourmi(Fourmi(8+i, Coord(7, TAILLEGRILLE-7+i),1));
	}
	
	Grille g = initialiseGrille2();
	
	for(int i = 0 ; i < 30 ; i++){
		deplacerAleatoirement(g, c0.listeF(),c0);
		deplacerAleatoirement(g, c1.listeF(),c1);
		cout << g;
		cout << endl;
		integrite(c0.listeF(), g);
		integrite(c1.listeF(), g);
	}
}
**/



bool contientSucreVoisins(Grille g, Fourmi f){
	for(int j = 0 ; j < voisines(f.coord()).taille() ; j++){
		if(g.chargePlace(voisines(f.coord()).ieme(j)).contientSucre()){
			return true;
		}
	}
	return false;
}

bool contientNidVoisins(Grille g, Fourmi f, Colonie c){
	for(int j = 0 ; j < voisines(f.coord()).taille() ; j++){
		if(c.presenceNid(voisines(f.coord()).ieme(j))){
			return true;
		}
	}
	return false;
}

bool estSurUnePiste(Grille g, Fourmi f, Colonie c){
	for(int j = 0 ; j < peutSeDeplacer(g, f).taille() ; j++){
		Place p = g.chargePlace(peutSeDeplacer(g, f).ieme(j));
		if(p.estSurUnePiste(c)){
			return true;
		}
	}
	return false;
}

bool plusProcheNidVoisins(Grille g, Fourmi f, Colonie c){
	for(int j = 0 ; j < peutSeDeplacer(g, f).taille() ; j++){
		Place p = g.chargePlace(peutSeDeplacer(g, f).ieme(j));
		if(estPlusProcheNid(p, g.chargePlace(f.coord()), c)){
			return true;
		}
	}
	return false;
}

void comportementFourmis(Grille &g, vector<Fourmi> tabF, Colonie &c){
	for(size_t i = 0 ; i < tabF.size() ; i++){
		if(not(tabF[i].porteSucre()) and contientSucreVoisins(g, tabF[i])){
			tabF[i].prendSucre();
			Place p = g.chargePlace(tabF[i].coord());
			p.posePheroSucre(c);
			g.rangePlace(p);
			integrite(tabF, g);
		}
		else if(tabF[i].porteSucre() and contientNidVoisins(g, tabF[i],c)){
			tabF[i].poseSucre();
			c.ajoutSucre();
			integrite(tabF, g);
		}
		else if(tabF[i].porteSucre() and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and plusProcheNidVoisins(g, tabF[i],c)){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(estPlusProcheNid(p, g.chargePlace(tabF[i].coord()),c)){
					deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), p);
					Place p2 = g.chargePlace(tabF[i].coord());
					p2.posePheroSucre(c);
					g.rangePlace(p2);
					integrite(tabF, g);
					ok = false;
				}
				j++;
			}
		}
		else if(not(tabF[i].porteSucre()) and g.chargePlace(tabF[i].coord()).estSurUnePiste(c) and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and not(plusProcheNidVoisins(g, tabF[i],c)) and estSurUnePiste(g, tabF[i],c)){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(not(estPlusProcheNid(p, g.chargePlace(tabF[i].coord()),c)) and p.estSurUnePiste(c)){
					deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), p);
					integrite(tabF, g);
					ok = false;
				}
				j++;
			}
		}
		
		else if(not(tabF[i].porteSucre()) and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and estSurUnePiste(g, tabF[i],c)){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(p.estSurUnePiste(c)){
					deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), p);
					integrite(tabF, g);
					ok = false;
				}
				j++;
			}
		}
		
		else if(not(tabF[i].porteSucre()) and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord()){
			deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), g.chargePlace(peutSeDeplacer(g, tabF[i]).choixHasard()));
			integrite(tabF, g);
		}
		c.rangeFourmi(tabF[i]);
	}
}


TEST_CASE("ComportementFourmi"){
	vector<Fourmi> tabF;
	Colonie c0 {0};
	Colonie c1 {1};
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-15, 15), Coord(TAILLEGRILLE-16, 15), Coord(TAILLEGRILLE-15, 16), Coord(TAILLEGRILLE-16, 16)}), //Nid du bas à gauche
	EnsCoord({Coord(15, TAILLEGRILLE-15), Coord(15, TAILLEGRILLE-16), Coord(16, TAILLEGRILLE-15), Coord(16, TAILLEGRILLE-16)})}; //Nid du haut à droite
	
	c0.ajoutNid(ElemNid[0]);
	c1.ajoutNid(ElemNid[1]);
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(TAILLEGRILLE-17, 14+i), 0));
		c0.ajoutFourmi(Fourmi(i, Coord(TAILLEGRILLE-17, 14+i),0));
	}
	
	tabF.push_back(Fourmi(4, Coord(TAILLEGRILLE-16, 14), 0));
	c0.ajoutFourmi(Fourmi(4, Coord(TAILLEGRILLE-16, 14),0));
	
	tabF.push_back(Fourmi(5, Coord(TAILLEGRILLE-15, 14), 0));
	c0.ajoutFourmi(Fourmi(5, Coord(TAILLEGRILLE-15, 14),0));
	
	tabF.push_back(Fourmi(6, Coord(TAILLEGRILLE-16, 17), 0));
	c0.ajoutFourmi(Fourmi(6, Coord(TAILLEGRILLE-16, 17), 0));
	tabF.push_back(Fourmi(7, Coord(TAILLEGRILLE-15, 17), 0));
	c0.ajoutFourmi(Fourmi(7, Coord(TAILLEGRILLE-15, 17),0));
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(TAILLEGRILLE-14, 14+i), 0));
		c0.ajoutFourmi(Fourmi(8+i, Coord(TAILLEGRILLE-14, 14+i),0));
	}
	
	//Fourmis de la deuxième colonnie
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(i, Coord(14, TAILLEGRILLE-17+i), 1));
		c1.ajoutFourmi(Fourmi(i, Coord(14, TAILLEGRILLE-17+i),1));
	}
	
	
	
	tabF.push_back(Fourmi(4, Coord(115, TAILLEGRILLE-17),1));
	c1.ajoutFourmi(Fourmi(4, Coord(15, TAILLEGRILLE-17),1));

	tabF.push_back(Fourmi(5, Coord(15, TAILLEGRILLE-14),1));
	c1.ajoutFourmi(Fourmi(5, Coord(15, TAILLEGRILLE-14),1));
	tabF.push_back(Fourmi(6, Coord(16, TAILLEGRILLE-17),1));
	c1.ajoutFourmi(Fourmi(6, Coord(16, TAILLEGRILLE-17),1));

	tabF.push_back(Fourmi(7, Coord(16, TAILLEGRILLE-14),1));
	c1.ajoutFourmi(Fourmi(7, Coord(16, TAILLEGRILLE-14),1));

	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(8+i, Coord(14, TAILLEGRILLE-17+i), 1));
		c1.ajoutFourmi(Fourmi(8+i, Coord(14, TAILLEGRILLE-17+i),1));
	}
	
	Grille g = initialiseGrille2();
	for(int i = 0 ; i < 30 ; i++){
		comportementFourmis(g, c0.listeF(),c0);
		comportementFourmis(g, c1.listeF(),c1);
		cout << endl;
		g.diminuePheroSucre();
		cout << afficherGrille(g, tabF).str();
		cout <<endl;
	}
	
}

/**TEST_CASE("Initialise Grille"){
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
		tabF.push_back(Fourmi(n, Coord(14, TAILLEGRILLE-17+i), 1));
		n++;
	}
	
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-17), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-14), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-17), 1));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-14), 1));
	n++;
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(17, TAILLEGRILLE-17+i), 1));
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
		comportementFourmis(g, tabF, Colonie(1));
		cout << afficherGrille(g, tabF).str();
	}
}
**/