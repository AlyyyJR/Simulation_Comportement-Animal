/**
 * ============================================================
 * FICHIER : ensemble.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Ensemble — structure de données
 * représentant un ensemble d'entiers de taille bornée.
 *
 * Un Ensemble est un tableau de capacité fixe (MAXCARD) qui
 * stocke des entiers sans doublons. Il est utilisé partout dans
 * la simulation pour représenter des sous-ensembles de cases :
 *   - voisines d'une Coord (jusqu'à 8 éléments)
 *   - IDs d'animaux présents dans la Population
 *
 * Constructeurs :
 *   - Ensemble()     : ensemble vide de capacité 0
 *   - Ensemble(int n): ensemble vide de capacité n
 *
 * Méthodes principales :
 *   - ajoute(n)  : ajoute n à la fin (lève runtime_error si plein)
 *   - tire()     : retire et retourne un élément aléatoire (destructif)
 *   - obtenir(i) : accès non-destructif à l'élément en position i
 *   - cardinal() : nombre d'éléments courant
 *   - estVide()  : true si cardinal == 0
 *
 * Note sur tire() :
 *   Tire un indice aléatoire dans [0, card[, retourne l'élément,
 *   puis décale les éléments suivants pour combler le vide.
 *   Complexité O(n). Utilisé pour parcourir des ensembles dans
 *   un ordre aléatoire (Monte-Carlo).
 *
 * Tests intégrés (doctest) : estVide, cardinal, ajoute, tire.
 *
 * Dépendances :
 *   - ensemble.hpp, doctest.h
 * ============================================================
 */

#include "ensemble.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <stdlib.h>


using namespace std;

ostream& operator<<(ostream& out, Ensemble e){
    out <<"[";
    for(int x = 0; x < e.cardinal(); x++){
        out << e.obtenir(x)<<";";
    }
    out<<"]";
    return out;
}
Ensemble::Ensemble(){
    card = 0;
    MAXCARD = 0;
    t = vector<int>(0);
}

Ensemble::Ensemble(int cm){
    card = 0;
    MAXCARD = cm;
    t = vector<int>(cm);
}
        

bool Ensemble::estVide(){
    if (card == 0) return true;
    return false;
}

int Ensemble::cardinal(){
    return card;
}

int Ensemble::obtenir(int pos){
    if (pos < 0 or pos >= card) throw invalid_argument("Position incorecte");
    return t[pos]; 
}

void Ensemble::ajoute(int n){
    if(card >= MAXCARD){
        throw runtime_error("plus de place dans l'ensemble :,(");
        return;
    }
    t[card] = n;
    card++;
}

int Ensemble::tire(){
    if(card == 0){
        throw runtime_error("pas d'éléments à tirer dans l'ensemble");
        return -1;
    }
    
    int tir = rand() % card;
    int n = t[tir];
    for(int x = tir+1; x < card; x++){
        t[x - 1] = t[x];
    }
    card--;
    return n;
}

TEST_CASE("Objet Ensemble") {
    Ensemble e = Ensemble(10);

    CHECK(e.estVide());
    CHECK(e.cardinal() == 0);

    e.ajoute(4);
    CHECK(e.cardinal() == 1);

    CHECK(e.obtenir(0) == 4);
    CHECK(e.tire() == 4);
    CHECK(e.estVide());
}