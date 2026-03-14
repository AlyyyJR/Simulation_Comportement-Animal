/**
 * ============================================================
 * FICHIER : jeu.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Jeu — orchestrateur principal de
 * la simulation prédateur-proie (modèle type Lotka-Volterra).
 *
 * Jeu agrège une Grille (carte 20×20) et une Population (registre
 * des animaux vivants) et coordonne toutes les interactions.
 *
 * Constructeurs :
 *   - Jeu()     : génération aléatoire — 7% renards, 20% lapins,
 *                 3% arbres, 3% rochers, 1% eau sur la grille 20×20
 *   - Jeu(s)    : mode debug — un seul animal au centre (10,10) ;
 *                 "R"=renard, autre=lapin
 *
 * Méthodes clés :
 *   - mouvements()            : tour de simulation complet
 *   - deplaceAnimal(a, c)     : supprime + replace à la nouvelle coord
 *   - supprimeAnimal(a)       : vide la case grille + supprime de Population
 *   - reproduit(parent, c)    : crée un nouvel animal à la coord c
 *   - voisinsVide(c)          : Ensemble des cases voisines libres ("O")
 *   - voisinsLapin(c)         : Ensemble des cases voisines occupées par un lapin
 *   - aVoisinsSexeOppose(c,s) : true si un voisin de même espèce a le sexe opposé à s
 *   - aVoisinsEau(c)          : true si au moins un voisin est une case eau
 *   - getTypeCase(c)          : "O"=vide, "A"=arbre, "C"=rocher, "E"=eau,
 *                               "R"=renard, "Lj"=lapin jeune(<5), "La"=adulte, "Lv"=vieux
 *   - compterEspece(s)        : compte les cases dont le type commence par s[0]
 *   - verifieGrille()         : vérifie la cohérence bidirectionnelle grille↔population
 *
 * Logique de mouvements() par animal :
 *   1. Viellit l'animal (age++)
 *   2. Meurt si age ≥ ageMax ou satiété ≤ 0 → supprimeAnimal
 *   3. Boit si voisin eau → age-- (rajeunit)
 *   4. Lapin : se déplace vers case vide → seReproduit éventuel
 *   5. Renard : perd 1 satiété → mange lapin voisin OU se déplace → seReproduit
 *
 * Tests intégrés (doctest) : constructeur, verifieGrille, mouvements
 *   (mode interactif console — demande saisie utilisateur).
 *
 * Dépendances :
 *   - jeu.hpp, doctest.h
 * ============================================================
 */

#include "jeu.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

void Jeu::ajouteAnimal(Animal a) {
    grille.setCase(a.getCoord(), a.getId());
    population.set(a);
}

Jeu::Jeu() {
    grille = Grille();
    population = Population();

    Coord c;
    Espece e;
    Animal a;
    int id;

    for(int y = 0; y < 20; y++) {
        for(int x = 0; x < 20; x++) {
            c = Coord(x, y);
            int r = rand() % 100;
            
            if (r < 7) {
                e = Espece::renard;
                id = population.reserve();

                a = Animal(id, e, c);
                ajouteAnimal(a);

            } else if (r < 20+7) {
                e = Espece::lapin;
                id = population.reserve();

                a = Animal(id, e, c);
                ajouteAnimal(a);
            } else if (r < 20+7+3) {
                grille.setCase(c, -2);
            } else if (r < 20+7+3+3) {
                grille.setCase(c, -3);
            } else if (r < 20+7+3+3+1) {
                grille.setCase(c, -4);
            }
        }
    }
}

Jeu::Jeu(string s){
    grille = Grille();
    population = Population();
    Coord c = Coord(10,10);
    Espece e;
    int id;
    Animal a;
    if(s == "R"){
        e = Espece::renard;
        id = population.reserve();
        a = Animal(id, e, c);
        ajouteAnimal(a);
        return;
    }
    else{
        e = Espece::lapin;
        id = population.reserve();
        a = Animal(id, e, c);
        ajouteAnimal(a);
        return;
    }

}

void Jeu::verifieGrille() {
    Animal a;
    Coord c;
    int id;

    //Cohérence animal-grille
    Ensemble animaux = population.getIds();
    while (not animaux.estVide()) {
        a = population.get(animaux.tire());

        if (grille.caseVide(a.getCoord()) or grille.caseArbre(a.getCoord()) or grille.caseRocher(a.getCoord()) or grille.caseEau(a.getCoord())) throw runtime_error("Incohérence animal-grille (case vide)"); 
        if (grille.getCase(a.getCoord()) !=  a.getId()) throw runtime_error("Incohérence animal-grille (mauvais id)"); 
    }

    //Cohérence grille-animal
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 20; y++) {
            c = Coord(x, y);

            if ((not grille.caseVide(c)) and (not grille.caseArbre(c)) and (not grille.caseRocher(c)) and (not grille.caseEau(c))) {
                id = grille.getCase(c);
                a = population.get(id);

                if (a.getCoord() != c or a.getId() != id) throw runtime_error("Incohérence grille-animal"); 
            }
        }
    }
}

Ensemble Jeu::voisinsVide(Coord c) {
    Ensemble EnsoisinsCase = c.voisines();
    Ensemble EnsVoisinsVide = Ensemble(8);

    int pos;
    while (not EnsoisinsCase.estVide()) {
        pos = EnsoisinsCase.tire();
        if (getTypeCase(Coord(pos)) == "O") EnsVoisinsVide.ajoute(pos);
    }

    return EnsVoisinsVide;
}

Ensemble Jeu::voisinsLapin(Coord c) {
    Ensemble EnsoisinsCase = c.voisines();
    Ensemble EnsVoisinsVide = Ensemble(8);

    int pos;
    while (not EnsoisinsCase.estVide()) {
        pos = EnsoisinsCase.tire();
        if ((getTypeCase(Coord(pos)) == "Lj") or (getTypeCase(Coord(pos)) == "Lv") or (getTypeCase(Coord(pos)) == "La")) EnsVoisinsVide.ajoute(pos);
    }

    return EnsVoisinsVide;
}

bool Jeu::aVoisinsSexeOppose(Coord c, Sexe s) {
    Ensemble EnsoisinsCase = c.voisines();

    int pos;
    while (not EnsoisinsCase.estVide()) {
        pos = EnsoisinsCase.tire();
        
        //Pas case obstacle ou vide
        if (not(grille.caseVide(Coord(pos)) or grille.caseArbre(Coord(pos)) or grille.caseRocher(Coord(pos)) or grille.caseEau(Coord(pos)))) {
            //Meme espèce
            if (int(population.get(grille.getCase(Coord(pos))).getEspece()) == int(population.get(grille.getCase(c)).getEspece())) {
                //Sexe différent
                if (int(population.get(grille.getCase(pos)).getSexe()) != int(s)) return true;
            }
        }
        
    }

    return false;
}

bool Jeu::aVoisinsEau(Coord c) {
    Ensemble EnsoisinsCase = c.voisines();

    int pos;
    while (not EnsoisinsCase.estVide()) {
        pos = EnsoisinsCase.tire();
        if (getTypeCase(pos) == "E") return true;
    }

    return false;
}

string Jeu::getTypeCase(Coord c) {
    if (grille.caseVide(c)) return "O";
    if (grille.caseArbre(c)) return "A";
    if (grille.caseRocher(c)) return "C";
    if (grille.caseEau(c)) return "E";
    
    int id = grille.getCase(c);
    Animal a = population.get(id);

    if (a.getEspece() == Espece::lapin) {
        if(a.getAge() < 5) return "Lj";
        else if (a.getAge() < 10) return "La";
        return "Lv";
    }
    return "R";
}

int Jeu::compterEspece(string s) {
    int nb = 0;

    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 20; y++) {
            char sp = getTypeCase(Coord(x, y)).at(0);
            char sa = s.at(0);
            if (sp == sa) nb++;
        }
    }

    return nb;
}

void Jeu::mouvements() {
    Ensemble aDeplacer = population.getIds();
    vector<int> lapinsMorts = {};


    while(not aDeplacer.estVide()) {
        //Obtenir un animal
        int id = aDeplacer.tire();

        //Vérifier si ce n'est pas un lapin déja tué
        bool lapinMort = false;
        for (int i = 0; i < int(lapinsMorts.size()); i++) {
            if (lapinsMorts[i] == id) lapinMort = true;
        }
        if (lapinMort) continue;

        //Obtenir des infos
        Animal a = population.get(id);

        //Faire viellir et vérifier
        population.supprime(a.getId());
        a.viellit();
        population.set(a);

        if(a.meurt()) {
            supprimeAnimal(a);
        } else {
            Ensemble ensVoisinsVides = voisinsVide(a.getCoord());
            int nbVoisinsVides = ensVoisinsVides.cardinal();
            Ensemble ensVoisinsLapins = voisinsLapin(a.getCoord());
            
            Coord cAncien = a.getCoord();

            if (aVoisinsEau(cAncien)) {
                population.supprime(a.getId());
                a.boit();
                population.set(a);
            }

            if (int(a.getEspece()) == int(Espece::lapin)) {
                // Si c'est un lapin
                if (not ensVoisinsVides.estVide() and a.getAge() < 15) {
                    Coord cNouveau = Coord(ensVoisinsVides.tire());

                    deplaceAnimal(a, cNouveau); //Déplacer le lapin

                    if (a.seReproduit(nbVoisinsVides, aVoisinsSexeOppose(cNouveau, a.getSexe()))) reproduit(a, cAncien);
                }
            } else {
                // Si c'est un renard
                //Enlever 1 de nourriture
                population.supprime(a.getId());
                a.jeune();
                population.set(a);

                //Vérifier s'il doit mourrir
                if(a.meurt()) {
                    supprimeAnimal(a);
                } else {
                    //S'il peut manger un lapin
                    if (not ensVoisinsLapins.estVide()) {
                        Coord cNouveau = Coord(ensVoisinsLapins.tire());

                        //Faire un tirage car un lapin jeune à 3/4 chance de mourrir suelemtn
                        //Manger
                        population.supprime(a.getId());
                        a.mange();
                        population.set(a);

                        //Tuer le lapin
                        int idLapinMort = grille.getCase(cNouveau);
                        supprimeAnimal(population.get(idLapinMort));
                        lapinsMorts.push_back(idLapinMort);

                        deplaceAnimal(a, cNouveau); //Déplacer le renard

                        if (a.seReproduit(nbVoisinsVides, aVoisinsSexeOppose(cNouveau, a.getSexe()))) reproduit(a, cAncien);
                    }
                    //Sinon s'il peut se déplacer
                    else if (not ensVoisinsVides.estVide()) {
                        Coord cNouveau = Coord(ensVoisinsVides.tire());
                        if (cNouveau == a.getCoord()) cout << "Mème" << endl;
                        
                        deplaceAnimal(a, cNouveau); //Déplacer le lapin
                        if (a.seReproduit(nbVoisinsVides, aVoisinsSexeOppose(cNouveau, a.getSexe())) ) reproduit(a, cAncien);
                        
                    }
                }
            }
        }
    }
}

void Jeu::deplaceAnimal(Animal a, Coord c) {
    supprimeAnimal(a);
    a.setCoord(c);
    ajouteAnimal(a);
}

void Jeu::supprimeAnimal(Animal a) {
    grille.videCase(a.getCoord());
    population.supprime(a.getId());
}

void Jeu::reproduit(Animal parent, Coord c) {
    Espece e = parent.getEspece();
    int id = population.reserve();
    Animal bebe = Animal(id, e, c);

    ajouteAnimal(bebe);
}

ostream& operator<<(ostream& out, Jeu j) {
    string s;

    for(int y = 0; y < 20; y++) {
        s = "";
        for(int x = 0; x < 20; x++) {
            s += j.getTypeCase(Coord(x, y));
            if (j.getTypeCase(Coord(x, y)) != "La" and j.getTypeCase(Coord(x, y)) != "Lj" and j.getTypeCase(Coord(x, y)) != "Lv") {
                s += " ";
            }
        }
        out << s << endl;
    }
    
    return out;
}

TEST_CASE("Objet Jeu") {
    srand(time(NULL));
    Jeu j = Jeu();
    
    int n = -1;
    int NbRenards, nbLapins = 0;
    string rep = "1";
    while(rep == "1" ) {
        n++; //Ajouter une étape
        nbLapins = j.compterEspece("L");
        NbRenards = j.compterEspece("R");

        j.verifieGrille(); //Vérifier cohérence
        cout << j << endl << "Grile OK : n=" << n << " NbLapins=" << nbLapins << " NbRenards=" << NbRenards << endl;
        cout << "Entrez 0 pour terminer ce test et passer à l'affichage graphique (sinon 1)" << endl;
        //Déplacement et tt
        j.mouvements();
        cin >> rep;
    }
}