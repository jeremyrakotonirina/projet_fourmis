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

#include "coord.hpp"
#include "fourmis.hpp"
#include "places.hpp"
#include "grille.hpp"
#include "simulation.hpp"
#include "doctest.h"

// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;

/**
// action dessinant un damier
void dessinerDamier(){
  int i,j;
  int r,g,b;
  ostringstream filename;
  // creation d'un nouveau nom de fichier de la forme img347.ppm
  filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
  compteurFichier++;
  cout << "Ecriture dans le fichier : " << filename.str() << endl;
  // ouverture du fichier
  ofstream fic(filename.str(), ios::out | ios::trunc);
  // ecriture de l'entete
  fic << "P3" << endl
      << 4 << " " << 4 << " " << endl
      << 255 << " " << endl;
  // ecriture des pixels
  for (i = 0; i < 4; i++){
      for (j = 0; j < 4; j++){
        // calcul de la couleur
        if (i == j) { r = 255; g = 0; b = 0; }
        else { r = 0; g = 255; b = 0; }
        // ecriture de la couleur dans le fichier
        fic << r << " " << g << " " << b << "    ";
      }
    // fin de ligne dans l'image
    fic << endl;
  }
  // fermeture du fichier
  fic.close();
} **/

void dessinerGrille(Grille g, vector<Fourmi> tabF, Colonie c){
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
							if (c.id()==0){
								r = 123 ; 
								G = 227 ; 
								b = 123;
							}
							else {
								r = 237 ; 
								G = 126 ; 
								b = 126;
							}
						}
						else{
							if (c.id()==0){
								r = 0 ; 
								G = 255 ; 
								b = 0;
							}
							else {
								r = 255 ; 
								G = 0 ; 
								b = 0;
							}
						}
					}
				}
			}
			else if(g.chargePlace(Coord(i, j)).contientSucre()){
				r = 0; G = 0; b = 250;
			}
			else{
				r = g.chargePlace(Coord(i, j)).pheroSucre(c) ; G = 0 ; b = 0;
			}
			fic << r << " " << G << " " << b << "    ";
		}
	}
}

/**

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

**/

TEST_CASE("affichage graphique"){
	Colonie c0 {0};
	Colonie c1 {1};
	vector<EnsCoord> ElemNid = {EnsCoord({Coord(TAILLEGRILLE-5, 5), Coord(TAILLEGRILLE-6, 5), Coord(TAILLEGRILLE-5, 6), Coord(TAILLEGRILLE-6, 6)}), //Nid du bas à gauche
	EnsCoord({Coord(5, TAILLEGRILLE-5), Coord(5, TAILLEGRILLE-6), Coord(6, TAILLEGRILLE-5), Coord(6, TAILLEGRILLE-6)})};
	c0.ajoutNid(ElemNid[0]);
	c1.ajoutNid(ElemNid[1]);
	//Fourmis de la première colonie, je ne sais pas si le compteur marche bien dans ce cas ou si il y a deux compteurs ou c comment
	
	for(int i = 0 ; i < 4 ; i++){
		c0.ajoutFourmi(Fourmi(i, Coord(TAILLEGRILLE-7, 4+i),0));
	}
	
	c0.ajoutFourmi(Fourmi(4, Coord(TAILLEGRILLE-6, 4),0));
	c0.ajoutFourmi(Fourmi(5, Coord(TAILLEGRILLE-5, 4),0));

	c0.ajoutFourmi(Fourmi(6, Coord(TAILLEGRILLE-6, 7),0));
	c0.ajoutFourmi(Fourmi(7, Coord(TAILLEGRILLE-5,7 ),0));
	
	for(int i = 0 ; i < 4 ; i++){
		c0.ajoutFourmi(Fourmi(8+i, Coord(TAILLEGRILLE-4, 4+i),0));
	}
	
	//Fourmis de la deuxième colonnie
	for(int i = 0 ; i < 4 ; i++){
		c1.ajoutFourmi(Fourmi(i, Coord(4, TAILLEGRILLE-7+i),1));
	}
	
	c1.ajoutFourmi(Fourmi(4, Coord(5, TAILLEGRILLE-7),1));

	c1.ajoutFourmi(Fourmi(5, Coord(5, TAILLEGRILLE-4),1));
	c1.ajoutFourmi(Fourmi(6, Coord(6, TAILLEGRILLE-7),1));

	c1.ajoutFourmi(Fourmi(7, Coord(6, TAILLEGRILLE-4),1));

	
	for(int i = 0 ; i < 4 ; i++){
		c1.ajoutFourmi(Fourmi(8+i, Coord(7, TAILLEGRILLE-7+i),1));
	}
	
	Grille g = initialiseGrille2();
	
	for(int k = 0 ; k < 30 ; k++){
		deplacerAleatoirement(g, c0.listeF(),c0);
		deplacerAleatoirement(g, c1.listeF(),c1);
		cout << g;
		cout << endl;
		integrite(c0.listeF(), g);
		integrite(c1.listeF(), g);
		dessinerGrille(g, c0.listeF(),c0);
		dessinerGrille(g, c1.listeF(),c1);
	}

}
