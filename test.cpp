/**
 * ============================================================
 * FICHIER : test.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Point de configuration du framework de tests unitaires doctest.
 *
 * Ce fichier active l'implémentation de doctest en définissant
 * DOCTEST_CONFIG_IMPLEMENT avant l'inclusion du header.
 * Sans cette définition dans exactement un .cpp, les fonctions
 * main() et le runner de doctest ne seraient pas générés.
 *
 * Les cas de tests eux-mêmes (TEST_CASE) sont définis dans
 * chaque fichier source concerné :
 *   - coord.cpp     : "Objet Coord"
 *   - ensemble.cpp  : "Objet Ensemble"
 *   - animal.cpp    : "Objet Animal"
 *   - grille.cpp    : "Objet Grille"
 *   - population.cpp: "Objet Population"
 *   - jeu.cpp       : "Objet Jeu"
 *   - graph.cpp     : point d'entrée + runner doctest (Context)
 *
 * Utilisation :
 *   Les tests sont lancés automatiquement au démarrage via
 *   doctest::Context dans graph.cpp (main), avant la boucle SDL.
 *   Passer --no-run ou filtrer avec --test-case="..." pour contrôle.
 *
 * Dépendances :
 *   - doctest.h
 * ============================================================
 */

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
