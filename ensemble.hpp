#include <vector> 
#include <iostream>

#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

using namespace std;

class Ensemble{
    private:
        vector<int> t;
        int MAXCARD;
        int card;
    public:
        /**
         * Constructeur créant un emsemble de taille 0.

         * 
         * @return Ensemble
         */
        Ensemble();

        /**
         * Constructeur créant un emsemble de taille donnée.
         *
         * @param int taille maximum de l'ensemble
         * 
         * @return Ensemble
         */
        Ensemble(int);

        /**
         * Informe si un ensemble est vide.
         * 
         * @return bool true => l'ensemble est vide
         */
        bool estVide();

        /**
         * Informe de la cardinalité d'un ensemble
         * 
         * @return int le cardinal d'un ensemble
         */
        int cardinal();

        /**
         * Ajoute un élement à l'ensemble
         * 
         * @param int l'élement à ajouter
         */
        void ajoute(int n);

        /**
         * Permet d'obtenir un élément d'un index donnée dans l'ensemble.
         *
         * @param int index de l'élément à retourner
         * 
         * @return int l'élément
         */
        int obtenir(int);

        /**
         * Permet de retourner et retirer un élement au hasard d'un ensemble.
         * 
         * @return int l'élément tiré au hasard
         */
        int tire();
};

/**
 * Permet d'afficher un ensemble dans un flux.
 *
 * @param ostream& le flux
 * @param Ensemble l'ensemble à afficher
 * 
 * @return ostream& le flux garni
 */
ostream& operator<<(ostream& out, Ensemble e);
#endif