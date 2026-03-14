/**
 * ============================================================
 * FICHIER : animal.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Animal — entité de base de la simulation.
 *
 * Un animal possède :
 *   - Une espèce : Espece::lapin (proie) ou Espece::renard (prédateur)
 *   - Un sexe aléatoire : Sexe::m ou Sexe::f
 *   - Une satiété : initialisée à FoodInit (5), max MaxFood (10)
 *   - Un âge : incrémenté à chaque tour (viellit), décrémenté en buvant (boit)
 *
 * Paramètres de simulation :
 *   - Lapin  : ageMax=15, ProbBirth=40%, nécessite ≥4 cases vides voisines
 *   - Renard : ageMax=28, ProbBirth=5%, nécessite satiété ≥ FoodReprod (8)
 *
 * Logique de mort (meurt()) :
 *   - Satiété ≤ 0  → mort de faim
 *   - Âge ≥ ageMax → mort de vieillesse (selon l'espèce)
 *
 * Tests intégrés (doctest) : constructeur, getters, setCoord, viellit/boit, meurt.
 *
 * Dépendances :
 *   - animal.hpp, doctest.h
 * ============================================================
 */

#include "animal.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

int Animal::getId(){
    return id;
}

Coord Animal::getCoord(){
    return c;
}

void Animal::setCoord(Coord co){
    c = co;
}

Espece Animal::getEspece(){
    return e;
}

int Animal::getAge(){
    return age;
}

Sexe Animal::getSexe(){
    return s;
}

string Animal::toString(){
    switch(e){
        case Espece::renard:return "Renard";
        case Espece::lapin:return "Lapin" ;
        default :return "???";
    }
}

Animal::Animal() {
    id = -1;
    age = 0;

    int r = rand() % 2;
    if (r == 0) s = Sexe::m;
    else s = Sexe::f;
    

    satiete = FoodInit;
};

Animal::Animal(int id_, Espece e_, Coord c_){
    id = id_;
    e = e_;
    c = c_;
    age = 0;

    int r = rand() % 2;
    if (r == 0) s = Sexe::m;
    else s = Sexe::f;

    satiete = FoodInit;
};

void Animal::mange(){
    satiete += FoodLapin;
    satiete = min(satiete, MaxFood);
};

void Animal::jeune(){
    satiete--;
};

void Animal::viellit(){
    age++;
}

void Animal::boit(){
    age--;
}

bool Animal::meurt(){
    if (satiete <= 0) return true;
    
    if (int(e) == int(Espece::lapin)) {
        if (age >= ageMaxLapin) return true;
    } else {
        if (age >= ageMaxRenard) return true;
    }
    
    return false;
};


bool Animal::seReproduit(int nbVoisinsVides, bool bonusSexe){
    int r = rand() % 100;
    if (bonusSexe) r*=0.75;
    else r*=1.2;

    if (int(e) == int(Espece::lapin)) {
        if (nbVoisinsVides >= MinFreeBirthLapin) {
            if (age > 5 and age <= 10) r /= 2.5;
            if (r <= ProbBirthLapin * 100) return true;
        }

    } else {
        if (satiete >= FoodReprod) {
            if (r <= ProbBirthRenard * 100) return true;
        }
    }

    return false;
};

TEST_CASE("Objet Animal") {
    int id = 42;
    Espece e = Espece::renard;
    Coord c = Coord(10, 10);

    Animal a = Animal(id, e, c);

    //Test constructeur
    CHECK(a.getId() == id);
    CHECK(a.getCoord() == c);
    CHECK(a.getEspece() == e);

    //Test sexe
    CHECK(((int(a.getSexe()) == int(Sexe::m)) or (int(a.getSexe()) == int(Sexe::f))));

    //Test setCoord
    a.setCoord(Coord(14,16));
    CHECK(a.getCoord() == Coord(14,16));

    //Age
    CHECK(a.getAge() == 0);
    a.viellit();
    CHECK(a.getAge() == 1);
    a.boit(); 
    CHECK(a.getAge() == 0);


    //Nourriture
    CHECK(a.meurt() == false);
    a.jeune(); a.jeune(); a.jeune(); a.jeune(); a.jeune(); a.jeune(); 
    CHECK(a.meurt() == true);
  
}