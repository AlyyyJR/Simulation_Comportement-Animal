/**
 * @file grille.hpp
 * @brief Déclaration de la classe Grille — terrain 20×20 de la simulation.
 *
 * @details
 * La Grille est un tableau 2D d'entiers (`vector<vector<int>>`) de taille TAILLEGRILLE×TAILLEGRILLE.
 * Chaque case est encodée comme suit :
 *
 *  | Valeur | Signification                |
 *  |--------|------------------------------|
 *  | -1     | Case vide (aucun élément)    |
 *  | -2     | Arbre (obstacle)             |
 *  | -3     | Rocher (obstacle)            |
 *  | -4     | Eau (source de nourriture)   |
 *  | ≥ 0    | ID de l'animal présent       |
 *
 * Les méthodes `caseVide`, `caseArbre`, `caseRocher`, `caseEau` permettent
 * d'interroger rapidement le type d'une case à partir d'une coordonnée Coord.
 *
 * @author Équipe projet Simulation Comportement Animal
 * @date 2024
 */

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