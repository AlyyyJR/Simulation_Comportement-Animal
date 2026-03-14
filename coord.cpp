/**
 * ============================================================
 * FICHIER : coord.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Coord — coordonnée sur la grille 20×20.
 *
 * La grille est un tableau de TAILLEGRILLE×TAILLEGRILLE (20×20 = 400 cases).
 * Une Coord peut être représentée soit en (x, y), soit en entier unique
 * via la formule : n = y * TAILLEGRILLE + x (linéarisation row-major).
 *
 * Constructeurs :
 *   - Coord()     : (0, 0) par défaut
 *   - Coord(n)    : conversion entier → (x, y)
 *   - Coord(x, y) : coordonnées directes (lève invalid_argument si hors grille)
 *
 * Méthodes principales :
 *   - toInt()    : (x, y) → entier (index dans le tableau linéaire)
 *   - voisines() : retourne un Ensemble des indices des cases adjacentes (4 ou 8 voisins)
 *
 * Tests intégrés (doctest) : vérification des constructeurs, getters, toInt.
 *
 * Dépendances :
 *   - ensemble.hpp (Ensemble), doctest.h
 * ============================================================
 */

#include "coord.hpp"
#include "doctest.h"
#include "ensemble.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

int TAILLEGRILLE = 20;

Coord::Coord() {
  x = 0;
  y = 0;
}

Coord::Coord(int n) {
  if (n < 0 or n >= TAILLEGRILLE * TAILLEGRILLE) throw invalid_argument("Les numéros doivent être positifs");
  
  x = n % TAILLEGRILLE;
  y = n / TAILLEGRILLE;
}

Coord::Coord(int col, int lig) {
  if (lig < 0 or col < 0 or lig >= TAILLEGRILLE or col >= TAILLEGRILLE) throw invalid_argument("Les numéros doivent être positifs");
  x = col;
  y = lig;
}

int Coord::getX() {
   return x;
}

int Coord::getY() {
  return y;
}

int Coord::toInt() {
  return y * TAILLEGRILLE + x;
} 

ostream& operator<<(ostream& out, Coord c) {
  out << "(" << c.getX() << " , " << c.getY() << ")";
  return out;
}

bool operator==(Coord a, Coord b) {
  return a.getX() == b.getX() and a.getY() == b.getY();
}

bool operator!=(Coord a, Coord b) {
  return not(a == b);
}



Ensemble Coord::voisines(){
    Ensemble e = Ensemble(8);

    int xmin = max(x - 1, 0);
    int xmax = min(x + 1, TAILLEGRILLE -1);
    int ymin = max(y - 1, 0);
    int ymax = min(y + 1, TAILLEGRILLE -1);

    for(int ix = xmin; ix <= xmax; ix++){
        for(int iy = ymin; iy <= ymax; iy++){
            if (not(ix == x and iy == y)){
                e.ajoute(Coord{ix,iy}.toInt());
            }
        }
    }

    return e;
}

        
TEST_CASE("Objet Coord") {
  Coord c = Coord{10,5};
  CHECK(c.getX() == 10);
  CHECK(c.getY() == 5);
  cout << c << endl;
  
  Coord cBis = Coord{5,10};
  CHECK_FALSE(cBis == c);
  
  Coord c2 = Coord{20};
  CHECK(c2.getX() == 0);
  CHECK(c2.getY() == 1);
  cout << c2 << endl;
  
  CHECK(Coord{55}.toInt()== 55);
}