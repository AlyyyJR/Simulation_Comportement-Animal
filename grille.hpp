#ifndef GRILLE_HPP
#define GRILLE_HPP
#include "coord.hpp"
#include <array>
#include <vector>
using namespace std;

class Grille {
  private:
    vector<vector<int>> tab;
  
  public:
    Grille();
    /**Constucteur de Grille par défaut
    **/

    bool caseVide(Coord);
    /** permet de savoir si une certaine case de la grille est vide
    *@input une coordonnée
    *@return un booléen
    **/
    bool caseArbre(Coord);
    /**Permet de savoir si une case du tableau est un arbre
    *@input une coordonnée
    *@return un booléen
    **/
    bool caseRocher(Coord);
    /**Permet de savoir si une case du tableau est un caillou
    *@input une coordonnée
    *@return un booléen
    **/
    bool caseEau(Coord c);
    /**Permet de savoir si une case du tableau est de l'eau
    *@input une coordonnée
    *@return un booléen
    **/
    int getCase(Coord);
    /**Retourne l'élément sur la case
    *@input une coordonnée
    *@return un entier qui représente l'élément sur la case
    **/
    void videCase(Coord);
    /**Vide une case de la grille => remplace l'int de la case par -1
    *@input une coordonnée
    **/
    void setCase(Coord, int);
    /**Met un certain entier sur une case de la grille
    *@input une coordonnée, un entier
    **/
};

#endif