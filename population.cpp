/**
 * ============================================================
 * FICHIER : population.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Population — registre de tous
 * les animaux vivants dans la simulation.
 *
 * La Population gère :
 *   - tabAnimal : un array<Animal, 400> à taille fixe (une case
 *     par cellule possible de la grille 20×20)
 *   - casesLibre : un vector<int> d'indices libres dans tabAnimal
 *   - dernierId  : compteur incrémental d'IDs uniques
 *
 * Cycle de vie d'un Animal dans la Population :
 *   1. reserve()       → obtient un id unique (incrémental)
 *   2. Animal(id,...)  → construit l'animal avec cet id
 *   3. set(a)          → place l'animal dans tabAnimal à un indice
 *                        libre (pop_back de casesLibre)
 *   4. get(id)         → retrouve l'animal par son id
 *   5. supprime(id)    → libère la case (push_back dans casesLibre)
 *
 * Méthodes :
 *   - reserve()        : retourne un id unique, incrémente dernierId
 *   - set(a)           : insère l'animal dans une case libre
 *   - get(id)          : recherche linéaire par id (O(n))
 *   - getIds()         : retourne un Ensemble de tous les ids actifs
 *   - supprime(id)     : marque la case comme libre
 *
 * Note : getIds() et get() parcourent tout tabAnimal (O(n)),
 * ce qui est acceptable pour une grille de 400 cases max.
 *
 * Tests intégrés (doctest) : reserve, set, getIds, get, supprime.
 *
 * Dépendances :
 *   - population.hpp, doctest.h
 * ============================================================
 */

#include "population.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
using namespace std;


Population::Population() {
  dernierId = 0;
  for (int i = 0; i < tabAnimal.size(); i++) {
    casesLibre.push_back(i);
  }
}

Animal Population::get(int id) {
  if (id < 0) throw invalid_argument("L'identifiant doit être positif");
  //Chercher un animal avec le même id
  for (int pos = 0; pos < tabAnimal.size(); pos++) {
    if (tabAnimal[pos].getId() == id) {
      //Vérifier que la case est utilisée
      bool posUsed = true;
      
      for (int i = 0; i < casesLibre.size(); i++) {
        if (casesLibre[i] == pos) posUsed = false;
      }

      if (posUsed) return tabAnimal[pos];
    }
  }
  throw invalid_argument("L'identifiant est introuvable");
}

Ensemble Population::getIds() {
  Ensemble e = Ensemble(20*20);

  for (int pos = 0; pos < tabAnimal.size(); pos++) {
    //Vérifier que la case est utilisée
    bool posUsed = true;
    
    for (int i = 0; i < casesLibre.size(); i++) {
      if (casesLibre[i] == pos) posUsed = false;
    }

    if (posUsed) e.ajoute(tabAnimal[pos].getId());
    
  }

  return e;
};

int Population::reserve() {
  dernierId++;
  return dernierId - 1;
};

void Population::set(Animal a){
  if (casesLibre.size() < 1) throw runtime_error("Plus de place");

  int pos = casesLibre.back();
  casesLibre.pop_back();

  tabAnimal[pos] = a;
};

void Population::supprime(int id){
  for (int pos = 0; pos < tabAnimal.size(); pos++) {
    if (tabAnimal[pos].getId() == id) {
      casesLibre.push_back(pos);
    }
  }
};

TEST_CASE("Objet Population") {
  Population p = Population();

  //Test de la méthode reserve
  CHECK(p.reserve() == 0);
  CHECK(p.reserve() == 1);

  int id = p.reserve();
  p.reserve();
  int id2 = p.reserve();
  Espece e = Espece::lapin;
  Coord c = Coord(0,0);
  Animal a = Animal(id, e, c);
  Animal a2 = Animal(id2, e, c);

  //Test de set et de gitIds
  p.set(a);
  Ensemble ens = p.getIds();

  CHECK(ens.cardinal() == 1);
  CHECK(ens.obtenir(0) == id);

  p.set(a2);
  ens = p.getIds();
  CHECK(ens.cardinal() == 2);
  CHECK(ens.obtenir(0) != ens.obtenir(1));


  //Test de get
  Animal aBis = p.get(id);

  CHECK(aBis.getCoord() == a.getCoord());
  CHECK(int(aBis.getEspece()) == int(a.getEspece()));
  CHECK(aBis.getId() == a.getId());

  //Test de supprime et de getIds
  p.supprime(id); p.supprime(id2);
  ens = p.getIds();
  CHECK(ens.estVide());
}