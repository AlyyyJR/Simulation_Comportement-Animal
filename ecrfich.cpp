/**
 * ============================================================
 * FICHIER : ecrfich.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Utilitaire d'écriture de fichiers image au format PPM (P3).
 *
 * Ce fichier est issu des travaux pratiques d'initiation à la
 * manipulation de fichiers en C++. Il fournit une fonction
 * autonome illustrant la génération d'images bitmap via flux
 * de fichiers standard (ofstream).
 *
 * Variables globales :
 *   - compteurFichier (int) : compteur auto-incrémenté pour nommer
 *     les fichiers img000.ppm, img001.ppm, img002.ppm, ...
 *
 * Fonctions :
 *   - dessinerDamier() : génère une image PPM P3 de 4×4 pixels
 *     représentant un damier diagonale-rouge / fond-vert.
 *     Le fichier est nommé selon compteurFichier (setfill+setw).
 *     Format PPM P3 : header "P3 W H MaxVal" + triplets RGB ASCII.
 *
 * Usage type (indépendant de la simulation principale) :
 *   dessinerDamier(); // crée img000.ppm
 *   dessinerDamier(); // crée img001.ppm
 *
 * Dépendances :
 *   - <iostream>, <iomanip>, <sstream>, <fstream>, <string>
 * ============================================================
 */

#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>

using namespace std;
// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;
// action dessinant un damier
void dessinerDamier(){
  int i,j;
  int r,g,b;
  ostringstream filename;
  // creation d'un nouveau nom de fichier de la forme img347.ppm
  filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
  compteurFichier++;
  cout << "Ecriture dans le fichier : " << filename.str() << endl;
  // ouverture du fichier
  ofstream fic(filename.str(), ios::out | ios::trunc);
  // ecriture de l'entete
  fic << "P3" << endl
      << 4 << " " << 4 << " " << endl
      << 255 << " " << endl;
  // ecriture des pixels
  for (i = 0; i < 4; i++){
      for (j = 0; j < 4; j++){
        // calcul de la couleur
        if (i == j) { r = 255; g = 0; b = 0; }
        else { r = 0; g = 255; b = 0; }
        // ecriture de la couleur dans le fichier
        fic << r << " " << g << " " << b << "    ";
      }
    // fin de ligne dans l'image
    fic << endl;
  }
  // fermeture du fichier
  fic.close();
}

