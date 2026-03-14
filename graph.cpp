/**
 * ============================================================
 * FICHIER : graph.cpp
 * Projet  : Simulation Comportement Animal (FoxWar)
 * Auteur  : Aly KONATE
 * ============================================================
 * Point d'entrée et couche graphique SDL2 de la simulation.
 *
 * Ce fichier contient :
 *   - main()              : init SDL2/TTF, boucle de menu principal
 *   - ecranDacceuil()     : affiche le menu d'accueil animé (foret.bmp,
 *                           titre3X.bmp), capture touche [1-4/ESC]
 *   - FoxWar()            : boucle de jeu principale — à chaque frame :
 *                           initialisation grille, AffichePlateau,
 *                           afficherRecensement, j.mouvements(), SDL_Delay
 *   - AffichePlateau()    : affiche la grille via images BMP par type de case :
 *                           R=renard, Lj/La/Lv=lapin (jeune/adulte/vieux),
 *                           C=caillou, A=arbre, E=eau, O=vide
 *   - afficherRecensement(): affiche en haut à gauche le compteur de lapins,
 *                           renards et le numéro de tour courant
 *   - initialisation()    : dessine la grille de lignes SDL (fond visuel)
 *   - coordTab()          : calcule la correspondance (i,j) → SDL_Rect écran
 *                           centrée dans la fenêtre redimensionnable
 *   - afficheTexte()      : rendu de texte via TTF_RenderText_Blended + COMIC.TTF
 *   - afficheImage()      : charge un .bmp, crée texture, copie, libère tout
 *   - debugMode()         : mode test — permet de visualiser coord, mouvement
 *                           renard seul ou lapin seul pas à pas
 *   - modeOption()        : réglage du délai par frame (flèche haut/bas,
 *                           quitter avec flèche gauche)
 *   - toucheMouvement_SDL() : polling du clavier SDL (flèches), bloquant
 *                           jusqu'au relâchement de la touche
 *   - ecouteAcceuil()     : polling touches [1-4/ESC] sans blocage
 *
 * Menu principal :
 *   1 → FoxWar (simulation complète)
 *   2 → Options (réglage delay)
 *   4 → Debug/Test
 *   ESC → Quitter
 *
 * Prérequis :
 *   Windows/MinGW + SDL2 + SDL2_ttf
 *   Police COMIC.TTF + images BMP dans le même répertoire
 *
 * Dépendances :
 *   - graph.hpp (jeu.hpp, population.hpp, grille.hpp, animal.hpp,
 *     ensemble.hpp, coord.hpp), doctest.h, SDL2, SDL2_ttf
 * ============================================================
 */

#include <stdlib.h>
#include "graph.hpp"
#define SDL_MAIN_HANDLED
#include <ctime> 

using namespace std;

int main(int argc, char* argv[]){
	doctest::Context context(argc, argv);
  	int test_result = context.run();
  	if (context.shouldExit()) return test_result;
	int delay = 200;
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("FoxWar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
	TTF_Init();
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    while (true) {
		int ecoute = ecranDacceuil(renderer, window);
		switch (ecoute) {
		case(1):
            FoxWar(window,renderer,texture,delay);
			break;
		case(2):
			delay = modeOption(window,renderer,texture, delay);
			break;
		case(3):
			//d'autres options ?
			break;
		case(4):
			debugMode(window,renderer,texture);
			break;
		case(5):
            //quitter
			return 0;
		}
	}
}


int toucheMouvement_SDL() {
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT]) {
		while (state[SDL_SCANCODE_LEFT]) {
			SDL_PumpEvents();
		}
		return 37;
	}
	else if (state[SDL_SCANCODE_UP]) {
		while (state[SDL_SCANCODE_UP]) {
			SDL_PumpEvents();
		}
		return 40;
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		while (state[SDL_SCANCODE_RIGHT]) {
			SDL_PumpEvents();
		}
		return 39;
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		while (state[SDL_SCANCODE_DOWN]) {
			SDL_PumpEvents();
		}
		return 38;
	}
	else {
		return 0;
	}

}

void initialisation(SDL_Renderer* renderer, SDL_Window* window, int taille) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
	SDL_Rect grille {(w-h)/2,0,h,h};
	SDL_RenderDrawRect(renderer, &grille);
	for (int x = 0; x < taille; x++) {
		SDL_Rect ligne{ grille.x,grille.y + x*int(grille.h / taille),grille.w,int(grille.h / taille)};
		SDL_RenderDrawRect(renderer, &ligne);
	}
	for (int y = 0; y < taille; y++) {
		SDL_Rect colonne{ grille.x + y*int(grille.w / taille),grille.y,int(grille.w / taille),grille.h };
		SDL_RenderDrawRect(renderer, &colonne);
	}
}

void afficheTexte(const char* texte, int x, int y, SDL_Renderer* renderer, SDL_Window* window, int r, int g, int b) {
	TTF_Font* font = TTF_OpenFont("COMIC.TTF", 28);
	int w, h;
	SDL_Rect position;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Color couleur = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(255) };
	SDL_Surface* text = TTF_RenderText_Blended(font, texte, couleur);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
	position.x = x;
	position.y = y;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderCopy(renderer, texture, nullptr, &position);
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture); //important
}

void afficheImage(const char* fichier, SDL_Rect destination, SDL_Renderer* renderer) {
	SDL_Surface* image = SDL_LoadBMP(fichier);
	SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	SDL_RenderCopy(renderer, pTextureImage, nullptr, &destination);
	SDL_DestroyTexture(pTextureImage);
}

int ecouteAcceuil() {
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_1]) {
		while (state[SDL_SCANCODE_1]) {
			SDL_PumpEvents();
		}
		return 1;
	}
	else if (state[SDL_SCANCODE_2]) {
		while (state[SDL_SCANCODE_2]) {
			SDL_PumpEvents();
		}
		return 2;
	}
	else if (state[SDL_SCANCODE_3]) {
		while (state[SDL_SCANCODE_3]) {
			SDL_PumpEvents();
		}
		return 3;
	}
	else if (state[SDL_SCANCODE_4]) {
		while (state[SDL_SCANCODE_4]) {
			SDL_PumpEvents();
		}
		return 4;
	}
	else if (state[SDL_SCANCODE_ESCAPE]) {
		while (state[SDL_SCANCODE_ESCAPE]) {
			SDL_PumpEvents();
		}
		return 5;
	}return -1;
}


int ecranDacceuil(SDL_Renderer* renderer, SDL_Window* window) {
	TTF_Init();
	SDL_Event events;
	bool isOpen = true;
	int w, h;
	int res = 0;
	int ecoute = -1;
	while (isOpen) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				return 5;
			}
		}
		SDL_GetWindowSize(window, &w, &h);
		SDL_SetRenderDrawColor(renderer, 90, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_Rect bg {0,0,w,h};
		SDL_Rect titre{(w)/4,0,w/2,h / 7};
		
		afficheImage("foret.bmp",bg,renderer);
		switch(res){
			case(0):afficheImage("titre30.bmp",titre,renderer);break;
			case(1):afficheImage("titre31.bmp",titre,renderer);break;
			case(2):afficheImage("titre32.bmp",titre,renderer);break;
			case(3):afficheImage("titre33.bmp",titre,renderer);break;
			case(4):afficheImage("titre33.bmp",titre,renderer);break;
		}
		res = (res+1)%4;

		afficheImage("titre3.bmp",titre,renderer);
		//afficheTexte("FowWar | Jessy & Gregoire", w / 2 - h / 6, h / 6, renderer, window, 255, 100, 0);
		afficheTexte("1. Lancer", 2 * h / 6, 2 * h / 6, renderer, window,0, 93, 255);
		afficheTexte("2. Options", 2 * h / 6, 3 * h / 6, renderer, window, 0, 93, 255);
		//afficheTexte("3. option 2", 2 * h / 6, 4 * h / 6, renderer, window, 0, 93, 255);
		afficheTexte("4. Debug-Test", 2 * h / 6, 5 * h / 6, renderer, window,0, 93, 255);

		afficheTexte("Press esc to quit", 0, 0, renderer, window, 0, 0, 255);
		ecoute = ecouteAcceuil();
		SDL_RenderPresent(renderer);
		if (ecoute != -1) {
			return ecoute;
		}
		SDL_Delay(100);
	}
    return 0;
}

vector<vector<SDL_Rect>> coordTab(SDL_Window* window,int taille) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
    SDL_Rect grille {(w-h)/2,0,h,h};
	vector<vector<SDL_Rect>> coord;
    int carre = grille.h /taille;
	coord = vector<vector<SDL_Rect>>(taille);
	for (int i = 0; i < taille; i++) {
		coord[i] = vector<SDL_Rect>(taille);
	}
	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < taille; j++) {
            
			coord[i][j].x = grille.x + j*int(grille.w / taille);
			coord[i][j].y = grille.y + i*int(grille.h / taille);
            coord[i][j].w = carre;
            coord[i][j].h = carre;
		}
	}return coord;
}

void testCoordTab(SDL_Window* window, SDL_Renderer* renderer,int taille) {
	vector<vector<SDL_Rect>> coord = coordTab(window,taille);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int x = 0; x < taille; x++) {
		for (int y = 0; y < taille; y++) {
			coord[x][y].w = 30;
			coord[x][y].h = 30;
			SDL_RenderDrawRect(renderer, &coord[x][y]);
		}
	}
}

void AffichePlateau(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, Jeu j,int taille){
    string s;
    int w, h;
	SDL_GetWindowSize(window, &w, &h);
    SDL_Rect grille {(w-h)/2,0,h,h};
    vector<vector<SDL_Rect>> coord = coordTab(window,taille);
    for(int y = 0; y < 20; y++) {
        s = "";
        for(int x = 0; x < 20; x++) {
            s = j.getTypeCase(Coord(x, y));
        
        if(s == "R"){
                afficheImage("R.bmp",coord[y][x],renderer);
            }
        else if(s == "Lj"){
                afficheImage("Lj.bmp",coord[y][x],renderer);
        }
        else if(s == "La"){
                afficheImage("La.bmp",coord[y][x],renderer);
        }
        else if(s == "Lv"){
                afficheImage("Lv.bmp",coord[y][x],renderer);
        }
        else if(s == "C"){
                afficheImage("C.bmp",coord[y][x],renderer);
        }
        else if(s == "A"){
                afficheImage("A.bmp",coord[y][x],renderer);
        }
		else if(s == "E"){
                afficheImage("E.bmp",coord[y][x],renderer);
        }
        else{
                afficheImage("O.bmp",coord[y][x],renderer);
        }
        }
    
    }
}
void afficherRecensement(SDL_Window* window, SDL_Renderer* renderer,Jeu j,int tour){
    int NbRenards, nbLapins = 0;
    nbLapins = j.compterEspece("L");
    NbRenards = j.compterEspece("R");
    string La = "lapin : "+ to_string(nbLapins);
    char const* texte = La.c_str();
    afficheTexte(texte,0,0,renderer,window,150,0,0);
    string Re = "renard : "+ to_string(NbRenards);
    texte = Re.c_str();
    afficheTexte(texte,0,100,renderer,window,150,0,0);
	string To = "tour : "+ to_string(tour);
    texte = To.c_str();
	afficheTexte(texte,0,200,renderer,window,150,0,0);
}



int FoxWar(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture,int delay) {
	SDL_Event events;
	int tour = 0;
    Jeu j = Jeu();
    int TAILLEGRILLE = 20;
	while (true) {
		bool isOpen = true;
		int fin = -1;
		while (isOpen && fin == -1) {
			while (SDL_PollEvent(&events)) {
				if (events.type == SDL_QUIT) {

					isOpen = false;
					return 0;
					break;
				}
			}
			SDL_SetRenderDrawColor(renderer, 184, 233, 148, 100);
			SDL_RenderClear(renderer);
			initialisation(renderer, window,TAILLEGRILLE);
            AffichePlateau(window, renderer,texture, j,TAILLEGRILLE);
            afficherRecensement(window,renderer,j,tour);
			tour ++;
			SDL_RenderPresent(renderer);
            j.mouvements();
            SDL_Delay(delay);

		}
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}




int ecranDacceuilDebug(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
	TTF_Init();
	SDL_Event events;
	bool isOpen = true;
	int w, h;
	int ecoute = -1;
	while (isOpen) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				isOpen = false;
				break;
			}
		}
		SDL_GetWindowSize(window, &w, &h);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		afficheTexte("FOXWAR DEBUG/TEST", w / 2 - h / 6, h / 6, renderer, window, 255, 255, 0);
		afficheTexte("1. test coord", h / 6, 2 * h / 6, renderer, window, 255, 0, 255);
		afficheTexte("2. test mouvement renard ", h / 6, 3 * h / 6, renderer, window, 255, 0, 255);
		afficheTexte("3. test mouvement lapin", h / 6, 4 * h / 6, renderer, window, 255, 0, 255);
		afficheTexte("Press esc to quit", 0, 0, renderer, window, 0, 0, 255);

		ecoute = ecouteAcceuil();
		SDL_RenderPresent(renderer);
		if (ecoute != -1) {
			return ecoute;
		}
	}
}


int debugMode(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
	int TAILLEGRILLE = 20;
	Jeu j;
	while (true) {
		SDL_Event events;
		int w, h;
		int ecoute = ecranDacceuilDebug(window, renderer, texture);
		bool isOpen = true;
		while (isOpen) {
			while (SDL_PollEvent(&events)) {
				if (events.type == SDL_QUIT) {
					isOpen = false;
					break;
				}
			}
			SDL_GetWindowSize(window, &w, &h);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			switch (ecoute) {
			case(1):
				TAILLEGRILLE = (TAILLEGRILLE % 20) +1;
				initialisation(renderer, window,TAILLEGRILLE);
				testCoordTab(window, renderer,TAILLEGRILLE);
				SDL_Delay(400);
				break;
			case(2):
				j = Jeu("R");
				ecoute = 6;
				break;
			case(3):
				j =  Jeu("L");
				ecoute = 6;
				break;
			case(5):
				return 0;
			case(6):
				TAILLEGRILLE = 20;
				initialisation(renderer, window,TAILLEGRILLE);
				AffichePlateau(window, renderer,texture, j,TAILLEGRILLE);
				j.mouvements();

            	SDL_Delay(100);
			}
			SDL_RenderPresent(renderer);
		}
	}
}


int modeOption(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int delay) {
	int TAILLEGRILLE = 20;
	int aug = 0;
	while (true) {
		SDL_Event events;
		int w, h;
		bool isOpen = true;
		while (isOpen) {
			while (SDL_PollEvent(&events)) {
				if (events.type == SDL_QUIT) {
					isOpen = false;
					return delay;
					break;
				}
			}
			SDL_GetWindowSize(window, &w, &h);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			aug = toucheMouvement_SDL();
			afficheTexte("FOXWAR OPTIONS", w / 2 - h / 6, h / 6, renderer, window, 255, 0, 0);
			string s = "Delay par image: " + to_string(delay)  + " ms";
			char const* texte = s.c_str();
			afficheTexte(texte, h / 6, 2 * h / 6, renderer, window, 255, 0, 255);
			afficheTexte("Press <- to quit", 0, 0, renderer, window, 0, 0, 255);

			switch(aug){
				case(40): delay = (delay+50)*(delay <500)+(500)*(delay >= 500);break;
				case(38): delay = (delay-50)*(delay > 0)+(0)*(delay <= 0);break;
				case(37): return delay;
			}
        	
			
			SDL_RenderPresent(renderer);
		}
	}
}



