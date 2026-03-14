/**
 * ============================================================
 * FICHIER : grille.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Grille — carte 20×20 de la simulation.
 *
 * La grille est un tableau 2D vector<vector<int>> de dimension
 * TAILLEGRILLE × TAILLEGRILLE (20×20 = 400 cases).
 *
 * Convention d'encodage des cases :
 *   - -1  : case vide  (terrain libre, traversable)
 *   - -2  : arbre      (obstacle, infranchissable)
 *   - -3  : rocher     (obstacle, infranchissable)
 *   - -4  : eau        (buvable — rajeunit le renard/lapin adjacent)
 *   - ≥ 0 : id d'un Animal vivant présent sur la case
 *
 * Méthodes principales :
 *   - caseVide(c)   : true si case == -1
 *   - caseArbre(c)  : true si case == -2
 *   - caseRocher(c) : true si case == -3
 *   - caseEau(c)    : true si case == -4
 *   - getCase(c)    : retourne l'id de l'animal (lève si vide)
 *   - setCase(c,id) : affecte une valeur à la case
 *   - videCase(c)   : remet la case à -1 (vide)
 *
 * Tests intégrés (doctest) : constructeur, setCase, videCase,
 *   caseArbre, caseRocher, getCase.
 *
 * Dépendances :
 *   - grille.hpp, doctest.h
 * ============================================================
 */

#include "grille.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Grille::Grille(){
  vector<int> l;

  for(int x = 0; x < 20; x++) {
    l = {};
    for(int y = 0; y < 20; y++) {
      l.push_back(-1);
    }
    tab.push_back(l);
  }
};

bool Grille::caseVide(Coord c){
  return (tab[c.getX()][c.getY()] == -1);
};

bool Grille::caseArbre(Coord c){
  return (tab[c.getX()][c.getY()] == -2);
};

bool Grille::caseRocher(Coord c){
  return (tab[c.getX()][c.getY()] == -3);
};

bool Grille::caseEau(Coord c){
  return (tab[c.getX()][c.getY()] == -4);
};

int Grille::getCase(Coord c){
  if (tab[c.getX()][c.getY()] == -1) throw invalid_argument("Case vide !");
  return tab[c.getX()][c.getY()];
};
    
void Grille::videCase(Coord c){
  tab[c.getX()][c.getY()] = -1;
};

void Grille::setCase(Coord c, int id){
  tab[c.getX()][c.getY()] = id;
};

TEST_CASE("Objet Grille") {
    Grille test = Grille();

  CHECK(test.caseVide(Coord{rand() % 20, rand() % 20 }));

  test.setCase(Coord{10,10}, -2);

  CHECK(test.caseArbre(Coord{10,10}));
  CHECK_FALSE(test.caseRocher(Coord{10,10}));

  test.videCase(Coord{10,10});

  CHECK_FALSE(test.caseArbre(Coord{10,10}));
  CHECK(test.caseVide(Coord{10,10}));

  test.setCase(Coord{10,10},-3);
  
  CHECK(test.caseRocher(Coord{10,10}));
  CHECK(test.getCase(Coord{10,10})== -3);
}