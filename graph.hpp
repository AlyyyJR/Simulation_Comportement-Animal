#define SDL_MAIN_HANDLED 
#include <string>
#include <cstdlib>
#include <stdio.h>  
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "jeu.hpp"
#include "doctest.h"
#include <ctime>
#include <SDL2/SDL.h>
#ifndef GRAPH_HPP
#define GRAPH_HPP



int toucheMouvement_SDL();
/**Permet de determiner les entrées utilisateurs
*@return un entier en fonction de l'entrée utilisateur
**/
void initialisation(SDL_Renderer* renderer, SDL_Window* window, int taille);
/**affiche une grille vide
*@input le renderer et la window SDL, la taille de la grille
**/
void afficheTexte(const char* texte, int x, int y, SDL_Renderer* renderer, SDL_Window* window, int r, int g, int b);
/**Affiche un texte de taille fixe sur l'écran
*@input une chaine de caractère, les coordonnées x,y, le renderer et la window SDL, la couleur en RGB)
**/
void afficheImage(const char* fichier, SDL_Rect destination, SDL_Renderer* renderer);
/**Affiche une image
*@input le fichier, le rectangle SDL de destination de l'image, le renderer SDL
**/
vector<vector<SDL_Rect>> coordTab(SDL_Window* window,int taille);
/** Permet d'obtenir l'ensemble des carrés de la grille 
*@input la window SDL, la taille de la grille
*@return un tableau de rectangle SDL
**/
int ecouteAcceuil();
/**detecte les entrées utilisateurs adapté à l'écran d'acceuil
*@return l'entier en fonction de l'entrée utlisateur
**/
void afficherRecensement(SDL_Window* window, SDL_Renderer* renderer,Jeu j);
/**Affiche à l'écran le nombre de lapin et du renard dans le jeu
*@input la window et le renderer SDL, une structure de Jeu
**/
void testCoordTab(SDL_Window* window, SDL_Renderer* renderer,int taille);
/**Test de maanière graphique la focntion coordTab
*@input la window et le renderer SDL, une taile de grille
**/
int ecranDacceuil(SDL_Renderer* renderer, SDL_Window* window);
/**affiche l'écran d'acceuil et s'occupe des redirections vers les autres éléments
*@input le renderer et la fenetre SDL
**/
void AffichePlateau(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, Jeu j,int taille);
/**affiche la grille avec ses elements
*@input la window, le renderer, la texture SDL, une structure de jeu, la taille de la grille
**/
int FoxWar(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture,int delay);
/** Lance FoxWar
*@input la window, le renderer et la texture SDL
**/
int debugMode(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);
/**Lance le mode de test graphique et de debug
*@input la window, le renderer et la texture SDL
**/
int ecranDacceuilDebug(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) ;
/**affiche l'écran de debug
*@input la window, le renderer et la texture SDL
**/
int modeOption(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int delay);

#endif