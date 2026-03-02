#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm>

using namespace std;

#include "simulation2.hpp"
#include "doctest.h"


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


/**
void Ennemis(Grille &g, vector<Fourmi> &tabF){
	for(size_t j = 0 ; j < tabF.size() ; j++){
		for(int i = 0 ; i < voisines(tabF[j].coord()).taille() ; i++){
			if(g.chargePlace(voisines(tabF[j].coord()).ieme(i)).contientFourmi()){
				if(tabF[g.chargePlace(voisines(tabF[j].coord()).ieme(i)).numeroFourmi()].colo() != tabF[i].colo()){
					int n = g.chargePlace(voisines(tabF[j].coord()).ieme(i)).numeroFourmi();
					Place p = g.chargePlace(tabF[g.chargePlace(voisines(tabF[j].coord()).ieme(i)).numeroFourmi()].coord());
					p.enleveFourmi(tabF[n]);
					tabF.erase(tabF.begin() + n);
					g.rangePlace(p);
					integrite(tabF, g);
					break;
				}
			}
		}
	}
}
**/


void ajoutSucre(Grille &g){
	vector<Coord> Sucre;
	for(int i = 0 ; i < TAILLEGRILLE ; i++){
		for(int j = 0 ; j < TAILLEGRILLE ; j++){
			Place p = g.chargePlace(Coord(i, j));
			if(p.estVide()){
				Sucre.push_back(Coord(i, j));
			}
		}
	}
	Place p2 = EnsCoord(Sucre).choixHasard();
	p2.poseSucre();
	g.rangePlace(p2);
}


void comportementFourmis(Grille &g, vector<Fourmi> &tabF){
	//Ennemis(g, tabF);
	for(size_t i = 0 ; i < tabF.size() ; i++){
		if(not(tabF[i].porteSucre()) and contientSucreVoisins(g, tabF[i])){
			tabF[i].prendSucre();
			Place p = g.chargePlace(tabF[i].coord());
			p.posePheroSucre(tabF[i].colo());
			g.rangePlace(p);
			integrite(tabF, g);
		}
		else if(tabF[i].porteSucre() and contientNidVoisins(g, tabF[i], tabF[i].colo())){
			tabF[i].poseSucre();
			integrite(tabF, g);
		}
		else if(tabF[i].porteSucre() and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and plusProcheNidVoisins(g, tabF[i], tabF[i].colo())){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(estPlusProcheNid(p, g.chargePlace(tabF[i].coord()), tabF[i].colo())){
					deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), p);
					Place p2 = g.chargePlace(tabF[i].coord());
					p2.posePheroSucre(tabF[i].colo());
					g.rangePlace(p2);
					integrite(tabF, g);
					ok = false;
				}
				j++;
			}
		}
		else if(not(tabF[i].porteSucre()) and g.chargePlace(tabF[i].coord()).estSurUnePiste(tabF[i].colo()) and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and not(plusProcheNidVoisins(g, tabF[i], tabF[i].colo())) and estSurUnePiste(g, tabF[i], tabF[i].colo())){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(not(estPlusProcheNid(p, g.chargePlace(tabF[i].coord()), tabF[i].colo())) and p.estSurUnePiste(tabF[i].colo())){
					deplacerFourmi(g, tabF[i], g.chargePlace(tabF[i].coord()), p);
					integrite(tabF, g);
					ok = false;
				}
				j++;
			}
		}
		
		else if(not(tabF[i].porteSucre()) and peutSeDeplacer(g, tabF[i]).ieme(0) != tabF[i].coord() and estSurUnePiste(g, tabF[i], tabF[i].colo())){
			int j = 0;
			bool ok = true;
			while(ok and j<peutSeDeplacer(g, tabF[i]).taille()){
				Place p = g.chargePlace(peutSeDeplacer(g, tabF[i]).ieme(j));
				if(p.estSurUnePiste(tabF[i].colo())){
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
		tabF.push_back(Fourmi(n, Coord(14, TAILLEGRILLE-17+i), 0));
		n++;
	}
	
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-17), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(15, TAILLEGRILLE-14), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-17), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(16, TAILLEGRILLE-14), 0));
	n++;
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(17, TAILLEGRILLE-17+i), 0));
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
	
	
	int m = 0;
	for(int i = 0 ; i < 500; i++){
		if(m==20){
			ajoutSucre(g);
			m=0;
		}
		comportementFourmis(g, tabF);
		cout << afficherGrille(g, tabF).str();
		cout << endl;
	}
	
	
	
}**/