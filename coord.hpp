#include "ensemble.hpp"
#include <vector>
#include <iostream>
#ifndef COORD_HPP
#define COORD_HPP


class Coord {
  private:
    int x, y;
  
  public:

    Coord();
    /**Constructeur par défaut de coord, où x = 0 et y = 0
    **/
    Coord(int);
    /**Contructeur qui se base sur une conversion de coordonnées x y en entier sur le tableau TAILLEGRILLExTAILLEGRILLE
    *@input un entier
    **/
    Coord(int, int);
    /**Constructeur par défaut de coord, où x = 0 et y = 0
    **/
    int getX();
    /**récupère la valeur en x de la coordonnée
    *@return un entier (valeur de x)
    **/
    int getY();
    /**récupère la valeur en y de la coordonnée
    *@return un entier (valeur de y)
    **/
    int toInt();
    /**Convertie une coordonnée en un entier en determinant le numéro de case sur le tableau associé à la coordonnée
    *@return un entier
    **/
    Ensemble voisines();
    /**retourne toutes les cases voisines de la coordonnée en convertissant leurs coordonnées en entier
    *@return un ensemble d'entier (coordonnées converties)
    **/
    
    
};

ostream& operator<<(ostream& out, Coord c);
/**surchage de << pour afficher une coordonnée
*@return l'afficheur ostream&
**/
bool operator==(Coord a, Coord b);
/**surcharge l'opérateur == pour les comparaisons entre coordonnées
*@return un booléen
**/
bool operator!=(Coord a, Coord b);
/**surcharge l'opérateur != pour la comparaison entre coordonnées
*@return un booléen
**/



#endif
