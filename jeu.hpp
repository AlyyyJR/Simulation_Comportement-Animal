/**
 * @file jeu.hpp
 * @brief Déclaration de la classe Jeu — moteur principal de la simulation FoxWar.
 *
 * @details
 * La classe Jeu orchestre l'ensemble de la simulation en combinant :
 *  - Une `Grille` (terrain 20×20 avec obstacles et cases eau)
 *  - Une `Population` (ensemble des animaux actifs, lapins et renards)
 *
 * La méthode centrale est `mouvements()`, qui exécute un tour complet :
 *  1. Pour chaque animal (ordre aléatoire via Ensemble) :
 *     - Vieillissement via `viellit()`
 *     - Vérification de mort (`meurt()`) → suppression si nécessaire
 *     - Déplacement vers une case voisine libre (lapin) ou occupée par lapin (renard)
 *     - Alimentation (renard mange lapin voisin, lapin boit eau voisine)
 *     - Reproduction si conditions réunies (satiété ≥ FoodReprod, voisin sexe opposé,
 *       probabilité selon espèce)
 *
 * Deux constructeurs sont disponibles :
 *  - `Jeu()` : initialisation standard (7% renards, 20% lapins aléatoirement)
 *  - `Jeu(string)` : initialise avec un unique animal d'une espèce donnée (tests)
 *
 * @author Équipe projet Simulation Comportement Animal
 * @date 2024
 */

#ifndef JEU_HPP
#define JEU_HPP
#include "ensemble.hpp"
#include "coord.hpp"
#include "animal.hpp"
#include "grille.hpp"
#include "population.hpp"

#include <vector>
#include <iostream>
using namespace std;

class Jeu {
  private:
    Grille grille;
    Population population;

    int FoodReprod;
    int ProbBirthRenard;
    
    int ProbBirthLapin;
    int MinFreeBirthLapin;
  
  public:
    /**
     * Constructeur créant un jeu initialisé normalement.
     * 
     * @return Jeu
     */
    Jeu();

    /**
     * Constructeur créant un jeu avec un animal d'une espece données.
     * 
     * @param string l'identifiant de l'espece de l'animal à ajouter (R Renard; L Lapin)
     * 
     * @return Jeu
     */
    Jeu(string);

    /**
     * Vérifie qu'un jeu est cohérent (grille-animaux et animaux-grille)
     *
     * throw si il y a une incohérence
     */
    void verifieGrille();

    /**
     * Permet d'obtenir les coordonnées des cases vides à 1 cases de celle données
     *
     * @param Coord de la case centrale
     * 
     * @return Ensemble des cases vides à proximité.
     */
    Ensemble voisinsVide(Coord);

    /**
     * Permet d'obtenir les coordonnées des cases lapins à 1 cases de celle données
     *
     * @param Coord de la case centrale
     * 
     * @return Ensemble des cases lapins à proximité.
     */
    Ensemble voisinsLapin(Coord);

    /**
     * Permet de savoir si il a un voisins de sexe opposé et de même espece 
     *
     * @param Coord de la case centrale
     * 
     * @return bool true => a un voisin de sexe opposé et de même espece
     */
    bool aVoisinsSexeOppose(Coord, Sexe);

    /**
     * Permet de savoir si il y a une case eau à proximité.
     *
     * @param Coord de la case centrale
     * 
     * @return bool true => il y a une case eau à proximité.
     */
    bool aVoisinsEau(Coord);

    /**
     * Permet d'obtenir les coordonnées des cases eau à 1 cases de celle données
     *
     * @param Coord de la case centrale
     * 
     * @return Ensemble des cases eau à proximité.
     */
    string getTypeCase(Coord);

    /**
     * Permet de compter le nombre d'animaux d'une espece
     *
     * @param string identifiant de l'espece (L lapin; R Renard)
     * 
     * @return int le nombre d'animaux de cette espece.
     */
    int compterEspece(string);

    /**
     * Permet d'éffectuer tous les mouvements correspondants à un tour
     *
     */
    void mouvements();

    /**
     * Permet déplacer un animal à des coordonnées données
     *
     * @param Animal Animal à déplacer
     * @param Coord nouvelles coordonées de l'animal
     */
    void deplaceAnimal(Animal, Coord);

    /**
     * Permet de faire reproduire un animal à des coordonnées données
     *
     * @param Animal Animal qui va se reproduire
     * @param Coord coordonées du bébé
     */
    void reproduit(Animal, Coord);

    /**
     * Ajoute un animal au jeu
     *
     * @param Animal Animal à ajouter
     */
    void ajouteAnimal(Animal);

    /**
     * Supprime un animal du jeu
     *
     * @param Animal Animal à ajouter
     */
    void supprimeAnimal(Animal);
};

/**
 * Permet d'afficher un jeu dans un flux.
 *
 * @param ostream& le flux
 * @param Jeu le jeu à afficher
 * 
 * @return ostream& le flux garni
 */
ostream& operator<<(ostream& out, Jeu j);

#endif