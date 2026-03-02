#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <array>

using namespace std;

#include "places.hpp"
#include "doctest.h"

//Constructeur

Place::Place(Coord C):
	coords{C},
	sucre{0},
	caseNid{false},
	numFourmi{-1}{
		for (int i=0; i< NBCOLONIE; i++){
			phSucre[i]=0;
			phNid[i]=0.;
		}
}

Place::Place(): Place{Coord {0,0}} {
}

//Getters
Coord Place::coord() const{
	return coords;
}

int Place::pheroSucre(Colonie c) const{
	return phSucre[c.id()];
}

float Place::pheroNid(Colonie c) const{
	return phNid[c.id()];
}

int Place::numeroFourmi() const{
	return numFourmi;
}

//Méthodes

bool Place::contientSucre() const{
	return sucre != 0;
}

bool Place::contientNid() const{
	return caseNid;
}

bool Place::estSurUnePiste(Colonie c) const{
	return phSucre[c.id()] != 0;
}

bool Place::contientFourmi() const{
	return numFourmi != -1;
}

bool Place::estVide() const{
	return (not contientFourmi() and not contientNid() and not contientSucre());
}

void Place::poseSucre(){
	sucre++;
}

void Place::enleveSucre(){
	sucre--;
}

void Place::poseNid(Colonie c){
	caseNid=true;
	phNid[c.id()]=1.0;
}

void Place::poseFourmi(Fourmi f){
	numFourmi=f.num();
}

void Place::enleveFourmi(Fourmi f){
	numFourmi=-1;
}

void Place::posePheroNid(float intensite, Colonie c){
	phNid[c.id()]=intensite;
}

void Place::posePheroSucre(Colonie c){
	phSucre[c.id()]=255;
}

void Place::diminuePheroSucre(){
	for (size_t i=0; i<NBCOLONIE; i++){
		
		if (phSucre[i]-5 >=0) phSucre[i] -= 5;
		else phSucre[i]=0;
	}
}



//Procédures

void deplaceFourmi(Fourmi f, Place &p1, Place &p2){
	p1.enleveFourmi(f);
	p2.poseFourmi(f);
}

bool estPlusProcheNid(Place p1, Place p2, Colonie c){
	return p1.pheroNid(c) > p2.pheroNid(c);
}

//Tests

TEST_CASE("classe places"){
	Place p1{Coord {5,6}};
	Colonie c0 {0};
	Colonie c1 {1};
	CHECK(p1.pheroSucre(c0) == 0);
	CHECK(p1.pheroNid(c0) == 0);
	CHECK(p1.numeroFourmi() == -1);
	CHECK_FALSE(p1.contientSucre());
	CHECK_FALSE(p1.contientNid());
	CHECK_FALSE(p1.estSurUnePiste(c0));
	CHECK_FALSE(p1.contientFourmi());
	CHECK(p1.estVide());
	
	p1.poseSucre();
	CHECK_FALSE(p1.estVide());
	p1.enleveSucre();
	CHECK_FALSE(p1.contientSucre());
	p1.poseNid(c0);
	CHECK(p1.contientNid());
	CHECK(p1.pheroNid(c0) == 1.);
	
	Fourmi f1{1, Coord {5,6},0};
	p1.poseFourmi(f1);
	CHECK(p1.contientFourmi());
	p1.enleveFourmi(f1);
	CHECK_FALSE(p1.contientFourmi());
	
	p1.posePheroSucre(c1);
	CHECK(p1.estSurUnePiste(c1));
	CHECK_FALSE(p1.estSurUnePiste(c0));
	CHECK(p1.pheroSucre(c1) == 255);
	p1.diminuePheroSucre();
	CHECK(p1.pheroSucre(c1) == 250);
	CHECK(p1.pheroSucre(c0) == 0);
	
	Place p2{ Coord{5,7}};
	p1.poseFourmi(f1);
	deplaceFourmi(f1, p1, p2);
	CHECK_FALSE(p1.contientFourmi());
	CHECK(p2.contientFourmi());
	CHECK(estPlusProcheNid(p1,p2,c0));
	CHECK_FALSE(estPlusProcheNid(p2,p1,c0));
	
	Place p3{};
	CHECK(p3.coord()==Coord{0,0});
	CHECK(p3.pheroSucre(c1) == 0);
	CHECK(p3.pheroNid(c1) == 0);
	CHECK(p3.numeroFourmi() == -1);
	CHECK_FALSE(p3.contientSucre());
	CHECK_FALSE(p3.contientNid());
	CHECK_FALSE(p3.estSurUnePiste(c1));
	CHECK_FALSE(p3.contientFourmi());
	CHECK(p3.estVide());
	
}

	
	
	
	
	
	
	
	
	
	
	