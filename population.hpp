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