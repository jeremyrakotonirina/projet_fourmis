#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>

using namespace std;

#include "graphique.hpp"
#include "doctest.h"


// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;


void dessinerGrille(Grille g, vector<Fourmi> tabF){
	int i, j;
	int r, G, b;
	ostringstream filename;
	filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
	compteurFichier++;
	ofstream fic(filename.str(), ios::out | ios::trunc);
	// ecriture de l'entete
	fic << "P3" << endl
      << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
      << 255 << " " << endl;
	for(i = 0 ; i < TAILLEGRILLE ; i++){
		for(j = 0 ; j < TAILLEGRILLE ; j++){
			if(g.chargePlace(Coord(i, j)).contientNid()){
				r = 170 ; G = 85 ; b = 0; 
			}
			else if(g.chargePlace(Coord(i, j)).contientFourmi()){
				for(size_t k = 0 ; k < tabF.size() ; k++){
					if(tabF[k].coord() == Coord(i, j)){
						if(tabF[k].porteSucre()){
							if(tabF[k].colo() == 0){
								r = 255 ; G = 0 ; b = 0;
							}
							else{
								r = 0 ; G = 0 ; b = 255;
							}
						}
						else{
							if(tabF[k].colo() == 0){
								r = 125 ; G = 0 ; b = 0;
							}
							else{
								r = 0 ; G = 0 ; b = 125;
							}
						}
					}
				}
			}
			else if(g.chargePlace(Coord(i, j)).contientSucre()){
				r = 0; G = 250; b = 0;
			}
			else{
				r = g.chargePlace(Coord(i, j)).pheroSucre(0) ; G = 0 ; b = g.chargePlace(Coord(i, j)).pheroSucre(1);
			}
			fic << r << " " << G << " " << b << "    ";
		}
	}
}

TEST_CASE("Grille"){
	Grille g = Grille();
	vector<Fourmi> tabF;
	vector<Coord> ElemSucre;
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-15, 15), Coord(TAILLEGRILLE-16, 15), Coord(TAILLEGRILLE-15, 16), Coord(TAILLEGRILLE-16, 16)}), //Nid du bas à gauche
	EnsCoord({Coord(15, TAILLEGRILLE-15), Coord(15, TAILLEGRILLE-16), Coord(16, TAILLEGRILLE-15), Coord(16, TAILLEGRILLE-16)})}; //Nid du haut à droite
	
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	int n = 0;
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-17, 14+i), 0));
		n++;
	}
	
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-16, 14), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-15, 14), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-16, 17), 0));
	n++;
	tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-15, 17), 0));
	n++;
	
	for(int i = 0 ; i < 4 ; i++){
		tabF.push_back(Fourmi(n, Coord(TAILLEGRILLE-14, 14+i), 0));
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
	
	
	int m = 0;
	for(int i = 0 ; i < 1000; i++){
		if(m==20){
			ajoutSucre(g);
			m=0;
		}
		comportementFourmis(g, tabF);
		dessinerGrille(g, tabF);
		m++;
	}
	
	
	
}