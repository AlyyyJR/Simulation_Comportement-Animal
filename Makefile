CXX = g++
CXXFLAGS = -w -std=c++17
EXEC_FILES = Main

# ─── Détection automatique de la plateforme ────────────────────────────────────
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S), Darwin)
    # macOS (Intel ou Apple Silicon M1/M2/M3/M4)
    # Homebrew installe dans /opt/homebrew sur Apple Silicon (arm64)
    # et dans /usr/local sur Intel (x86_64)
    ifeq ($(UNAME_M), arm64)
        HOMEBREW_PREFIX = /opt/homebrew
    else
        HOMEBREW_PREFIX = /usr/local
    endif
    INCLFLAGS = -I$(HOMEBREW_PREFIX)/include -I$(HOMEBREW_PREFIX)/include/SDL2
    LDFLAGS   = -L$(HOMEBREW_PREFIX)/lib -lSDL2 -lSDL2_ttf
else
    # Linux / Windows (MSYS2/MinGW)
    INCLFLAGS = -I/usr/include/SDL2
    LDFLAGS   = -lSDL2 -lSDL2_ttf
endif

# ─── Cibles ────────────────────────────────────────────────────────────────────
all: Main

Main:
	$(CXX) $(INCLFLAGS) -o Main *.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC_FILES)

# ─── Aide ──────────────────────────────────────────────────────────────────────
.PHONY: all clean help

help:
	@echo "Utilisation :"
	@echo "  make          — compile FoxWar (détection auto macOS/Linux)"
	@echo "  make clean    — supprime le binaire et les fichiers objets"
	@echo ""
	@echo "Plateforme detectee : $(UNAME_S) / $(UNAME_M)"
