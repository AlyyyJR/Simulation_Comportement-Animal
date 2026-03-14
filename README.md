# Simulation Comportement Animal — FoxWar

> Simulation d'écosystème prédateur-proie sur une grille 20×20, implémentée en C++ avec rendu graphique SDL2. Les renards (prédateurs) et les lapins (proies) évoluent chaque tour selon des règles de déplacement, reproduction et mortalité inspirées du modèle de Lotka-Volterra.

---

## Objectifs pédagogiques

- Modélisation orientée objet (héritage, encapsulation, composition)
- Structures de données personnalisées (`Ensemble`, `Grille`, `Population`)
- Simulation par automate cellulaire stochastique
- Rendu graphique 2D avec SDL2 et SDL2_ttf
- Tests unitaires intégrés avec doctest

---

## Stack technique

| Composant        | Technologie                         |
|-----------------|-------------------------------------|
| Langage          | C++17                               |
| Rendu graphique  | SDL2 + SDL2_ttf                     |
| Tests unitaires  | doctest (embarqué)                  |
| Build            | Makefile (détection auto plateforme)|
| Assets           | Images BMP + COMIC.TTF              |
| Plateformes      | Windows (MinGW/MSYS2), macOS (Homebrew, Apple Silicon) |

---

## Structure du projet

```
Simulation-Comportement-Animal/
│
├── coord.hpp / coord.cpp         ← Coordonnée (x,y) sur grille + linéarisation
├── ensemble.hpp / ensemble.cpp   ← Ensemble d'entiers à capacité fixe
├── animal.hpp / animal.cpp       ← Entité Animal (espèce, sexe, satiété, âge)
├── grille.hpp / grille.cpp       ← Carte 20×20 (encodage terrain + animaux)
├── population.hpp / population.cpp ← Registre des animaux vivants
├── jeu.hpp / jeu.cpp             ← Orchestrateur (déplacements, mort, reprod.)
├── graph.hpp / graph.cpp         ← Point d'entrée SDL2 + couche graphique
├── ecrfich.cpp                   ← Utilitaire écriture PPM (TP indépendant)
├── test.cpp                      ← Configuration doctest (DOCTEST_CONFIG_IMPLEMENT)
├── doctest.h                     ← Framework de tests unitaires
│
├── *.bmp                         ← Assets visuels (R, Lj, La, Lv, A, C, E, O, foret…)
├── COMIC.TTF                     ← Police SDL pour l'affichage texte
└── Makefile                      ← Compilation multi-plateforme (auto-détection)
```

---

## Architecture

```
main() [graph.cpp]
│
├── SDL_Init / TTF_Init
│
└── Boucle menu ──→ ecranDacceuil()
        │
        ├─ [1] FoxWar()          ←── Boucle de simulation principale
        │         │
        │         ├── Jeu::mouvements()   ← 1 tour complet
        │         ├── AffichePlateau()    ← Rendu grille via BMP
        │         └── afficherRecensement() ← HUD (lapins/renards/tour)
        │
        ├─ [2] modeOption()      ← Réglage delay par frame (flèches)
        └─ [4] debugMode()       ← Visualisation test (coord, 1 renard, 1 lapin)
```

### Hiérarchie des classes

```
Coord          ← case (x,y), toInt(), voisines()
Ensemble       ← set d'entiers, tire() aléatoire
Animal         ← espèce + sexe + satiété + âge
Grille         ← vector<vector<int>> 20×20
Population     ← array<Animal,400> + casesLibre
Jeu            ← Grille + Population + logique simulation
graph.cpp      ← main() + SDL2 rendering
```

---

## Règles de simulation

### Encodage de la grille

| Valeur | Signification |
|--------|--------------|
| -1     | Case vide (libre) |
| -2     | Arbre (obstacle) |
| -3     | Rocher (obstacle) |
| -4     | Eau (rajeunit l'animal adjacent) |
| ≥ 0    | ID de l'animal présent |

### Type de case (getTypeCase)

| Code | Signification |
|------|--------------|
| `O`  | Vide |
| `A`  | Arbre |
| `C`  | Caillou / Rocher |
| `E`  | Eau |
| `R`  | Renard |
| `Lj` | Lapin jeune (âge < 5) |
| `La` | Lapin adulte (5 ≤ âge < 10) |
| `Lv` | Lapin vieux (âge ≥ 10) |

### Paramètres des animaux

| Paramètre        | Lapin | Renard |
|-----------------|-------|--------|
| `ageMax`         | 15    | 28     |
| `ProbBirth`      | 40 %  | 5 %    |
| `FoodInit`       | 5     | 5      |
| `MaxFood`        | 10    | 10     |
| `FoodReprod`     | —     | 8 (satiété min) |
| `MinFreeBirth`   | 4 cases vides | — |

### Déroulement d'un tour (mouvements)

Pour chaque animal, dans un ordre aléatoire :

1. **Vieillit** (`age++`)
2. **Mort** si `satiete ≤ 0` ou `age ≥ ageMax` → supprimé
3. **Boit** si voisin eau → `age--` (rajeunit)
4. **Lapin** : se déplace vers case vide → `seReproduit()` éventuel
5. **Renard** : `satiete--` → si faim → mort ; sinon :
   - Mange lapin voisin → `satiete += FoodLapin` → se déplace
   - OU se déplace vers case vide
   - → `seReproduit()` éventuel

### Logique de reproduction (seReproduit)

```
r = rand() % 100
si bonusSexe (voisin de sexe opposé): r *= 0.75   (bonus 25%)
sinon:                                 r *= 1.2    (malus 20%)

Lapin : si nbVoisinsVides ≥ 4 ET (r ≤ ProbBirthLapin*100)
  si 5 < âge ≤ 10 : r /= 2.5   (bonus d'âge)
  → seReproduit = true

Renard : si satiete ≥ 8 ET (r ≤ ProbBirthRenard*100)
  → seReproduit = true
```

---

## Contrôles

| Touche       | Action |
|-------------|--------|
| `1`          | Lancer la simulation |
| `2`          | Options (réglage vitesse) |
| `4`          | Mode Debug/Test |
| `ESC`        | Quitter |
| `↑ / ↓`     | (Options) Augmenter / Diminuer le délai |
| `←`          | (Options) Retour au menu |

---

## Assets graphiques

| Fichier       | Usage |
|--------------|-------|
| `R.bmp`      | Renard |
| `Lj.bmp`     | Lapin jeune |
| `La.bmp`     | Lapin adulte |
| `Lv.bmp`     | Lapin vieux |
| `A.bmp`      | Arbre |
| `C.bmp`      | Caillou |
| `E.bmp`      | Eau |
| `O.bmp`      | Case vide |
| `foret.bmp`  | Fond menu d'accueil |
| `titre3*.bmp`| Animation titre |
| `COMIC.TTF`  | Police HUD |

---

## Installation & Lancement

Le Makefile détecte automatiquement la plateforme (macOS/Linux/Windows) et adapte les chemins SDL2.

---

### macOS (Apple Silicon — M1 / M2 / M3 / M4 Pro)

#### 1. Installer les dépendances via Homebrew

Si Homebrew n'est pas encore installé :

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Installer SDL2 et SDL2_ttf :

```bash
brew install sdl2 sdl2_ttf
```

> Sur Apple Silicon, Homebrew s'installe dans `/opt/homebrew` (détecté automatiquement par le Makefile).

#### 2. Installer les outils de compilation

```bash
xcode-select --install
```

Cela installe `g++` (Clang/LLVM) et `make`.

#### 3. Compiler

```bash
make
```

#### 4. Lancer

```bash
./Main
```

> Assurez-vous que tous les assets (`*.bmp`, `COMIC.TTF`) sont dans le même répertoire que l'exécutable.

#### Diagnostic macOS

```bash
# Vérifier que SDL2 est bien trouvé
sdl2-config --version
sdl2-config --cflags --libs

# Vérifier l'architecture du binaire compilé (doit afficher arm64)
file Main
```

---

### Windows (MinGW / MSYS2)

#### 1. Installer MSYS2

Télécharger depuis [msys2.org](https://www.msys2.org/) et installer les paquets :

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf make
```

#### 2. Compiler et lancer

```bash
make
./Main.exe
```

---

### 🐧 Linux (Debian/Ubuntu)

```bash
sudo apt update && sudo apt install g++ make libsdl2-dev libsdl2-ttf-dev
make
./Main
```

---

## Tests unitaires

Les tests [doctest](https://github.com/doctest/doctest) sont exécutés automatiquement au démarrage, avant la boucle SDL. Chaque classe dispose de ses propres cas de tests dans son fichier `.cpp` :

| Fichier           | TEST_CASE |
|------------------|-----------|
| `coord.cpp`       | "Objet Coord" |
| `ensemble.cpp`    | "Objet Ensemble" |
| `animal.cpp`      | "Objet Animal" |
| `grille.cpp`      | "Objet Grille" |
| `population.cpp`  | "Objet Population" |
| `jeu.cpp`         | "Objet Jeu" (interactif console) |

---

## Auteur

**Aly KONATE** — Projet universitaire C++ / SDL2
