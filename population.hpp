/**
 * @file population.hpp
 * @brief Déclaration de la classe Population — gestion du tableau d'animaux (max 400).
 *
 * @details
 * La Population maintient un tableau statique de 400 animaux (`array<Animal, 400>`)
 * et un vecteur de cases libres (`casesLibre`) pour une allocation rapide d'IDs.
 * Le champ `dernierId` permet de suivre le prochain identifiant disponible.
 *
 * Workflow typique :
 *  1. `reserve()` — réserve un slot et retourne son ID
 *  2. `set(animal)` — place l'animal dans le slot réservé
 *  3. `get(id)` — accède à l'animal par son ID
 *  4. `supprime(id)` — libère le slot (remet la case dans `casesLibre`)
 *  5. `getIds()` — retourne l'Ensemble de tous les IDs actuellement occupés
 *
 * @author Équipe projet Simulation Comportement Animal
 * @date 2024
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP
#include "animal.hpp"
#include "coord.hpp"
#include "ensemble.hpp"
#include <array>
#include <vector>
using namespace std;

class Population {
  private:
    int dernierId;
    array<Animal, 400> tabAnimal;
    vector<int> casesLibre{400, 0};
  
  public:
    Population();
    /**Constructeur par défaut de Population
    **/
    Animal get(int);
    /**Permet d'obtenir un animal de la population grace à son ID
    *@input un entier (ID)
    *@return un Animal
    **/
    Ensemble getIds();
    /**Permet d'obtenir tout les ID des éléments dans population
    *@return un ensemble d'id
    **/
    
    int reserve();
    /**reserve un id de la liste des ID
    *@return l'id reservé
    **/
    void set(Animal);
    /**Insere un animal dans la population 
    *@input l'animal à insérer
    **/
    void supprime(int);
    /**Supprime un animal à l'aide de son ID
    *@input l'id de l'animal à supprimer
    **/
};

#endif