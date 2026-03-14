#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "coord.hpp"
#include <string>
using namespace std;

enum class Espece {lapin, renard};
enum class Sexe {m, f};


class Animal{
    private:
        int id;
        Coord c;
        Espece e;
        Sexe s;
        int satiete;
        int age;

        int FoodInit = 5;
        int FoodLapin = 5;
        int MaxFood = 10;

        int FoodReprod = 8;
        float ProbBirthRenard = 0.05;
        int ageMaxRenard = 28;
    
        int MinFreeBirthLapin = 4;
        float ProbBirthLapin = 0.4;
        int ageMaxLapin = 15;
        

    public:
        /**
         * Constructeur créant un animal vierge aux attributs incertains.
         *
         * @return Animal
         */
        Animal();

        /**
         * Constructeur créant un animal selon l'id, l'espece et les coordonnées. Le sexe, l'age et la satiete sont initialisés.
         *
         * @param int l'identifiant,
         * @param Espece l'espece, 
         * @param Coord les coordonées
         * 
         * @return Animal
         */
        Animal(int id_, Espece e_, Coord c_);
        
        /**
         * Retourne l'identifiant d'un animal
         *
         * @return int l'id de l'animal
         */
        int getId();

        /**
         * Retourne les coordonnées d'un animal
         *
         * @return Coord les coordonnées de l'animal
         */
        Coord getCoord();

        /**
         * Définit les coordonées d'un animal
         *
         * @param Coord les coordonnées à définir à l'animal
         */
        void setCoord(Coord);

        /**
         * Retourne l'espèce d'un animal
         *
         * @return Espece l'espèce de l'animal
         */
        Espece getEspece();

        /**
         * Retourne le sexe d'un animal
         *
         * @return Sexe le sexe de l'animal
         */
        Sexe getSexe();

        /**
         * Convertit un animal en affichage textuel
         *
         * @return string une phrase décrivant l'animal
         */
        string toString();

        /**
         * Retourne l'age d'un animal
         *
         * @return int l'age de l'animal
         */
        int getAge();
        
        /**
         * Vérifie si l'animal doit mourrir (age et satiete)
         *
         * @return bool true => l'animal doit mourrir
         */
        bool meurt();

        /**
         * Vérifie si l'animal doit se reproduire
         *
         * @param int le nombre de cases libres à côté
         * @param bool si un congénère de sexe opposé est à côté
         * @return bool true => l'animal doit se reproduire
         */
        bool seReproduit(int, bool);

        /**
         * Fait manger l'animal (+FoodInit à la satiete)
         *
         */
        void mange();

        /**
         * Fait jeuner l'animal (-1 à la satiete)
         *
         */
        void jeune();

        /**
         * Fait viellir l'animal (-1 à l'age)
         *
         */
        void viellit();

        /**
         * Fait boire l'animal (+1 à l'age)
         *
         */
        void boit();
};

#endif