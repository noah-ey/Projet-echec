// Afficher l’échiquier : 9x9 car 8x8 cases + lettres et n° pour les coordonnées
// Création en début de partie     → Affichage pendant la partie
// Interaction avec le(s) joueur(s) : Demander la case puis l’action


#include "declarations.h"

// Renvoie un pointeur vers un plateau initialisé en début de partie
Case **creer_plateau(){
	Case** plateau = malloc(sizeof((Case*));
	for(int i = 0; i < 8; i++){
		plateau[i] = malloc(8*sizeof(Case));
		for(int j = 0; j < 8; j++){
			plateau[i][j].piece = VIDE;
		}
	}	
	

	return plateau;
 }

// Plateau avec une liste par ligne
Case *creer_plateau_liste(){

}


// Affiche l’état du jeu (plateau, joueur actif)
void affichage(Partie* partie){
	printf("Le joueur actuel est : "); //compléter
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(plateau[i][j].piece == VIDE){
				printf("| ");
			}
			if(plateau[i][j].piece == PION){
				printf("|p");
			}//continuer
		}
	}
}

nicooooooooooooooooooooooooooooooooooooooooo
#include <stdio.h>
#include <stdlib.h>

#define MAX_CASE 8

// Définition des types
typedef enum piece { VIDE, PION, TOUR, CAVALIER, FOU, REINE, ROI } Piece;
typedef enum couleur { BLANC, NOIR } Couleur;

typedef struct case {
    Piece p;
    Couleur c;
} Case;

typedef struct coup {
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
} Coup;

typedef struct partie {
    Case** plateau;
    Couleur joueur_actif;
} Partie;

// Fonction pour allouer et initialiser le plateau
Case** creer_plateau() {
    // Allocation du plateau 8x8
    Case** plateau = malloc(MAX_CASE * sizeof(Case*));
    if (!plateau) {
        perror("Erreur d'allocation mémoire pour le plateau");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CASE; i++) {
        plateau[i] = malloc(MAX_CASE * sizeof(Case));
        if (!plateau[i]) {
            perror("Erreur d'allocation mémoire pour une ligne du plateau");
            exit(EXIT_FAILURE);
        }
    }

    // Initialisation du plateau avec des cases vides
    for (int i = 0; i < MAX_CASE; i++) {
        for (int j = 0; j < MAX_CASE; j++) {
            plateau[i][j].p = VIDE;
            plateau[i][j].c = BLANC;  // Par défaut, on peut initialiser toutes les cases à BLANC
        }
    }

    // Placement des pions
    for (int j = 0; j < MAX_CASE; j++) {
        plateau[1][j].p = PION;
        plateau[1][j].c = NOIR;
        plateau[6][j].p = PION;
        plateau[6][j].c = BLANC;
    }

    // Placement des pièces majeures
    Piece ordre_pieces[] = { TOUR, CAVALIER, FOU, REINE, ROI, FOU, CAVALIER, TOUR };
    for (int j = 0; j < MAX_CASE; j++) {
        plateau[0][j].p = ordre_pieces[j];
        plateau[0][j].c = NOIR;
        plateau[7][j].p = ordre_pieces[j];
        plateau[7][j].c = BLANC;
    }

    return plateau;
}

// Fonction pour initialiser une partie
Partie initialiser_partie() {
    Partie partie;
    partie.plateau = creer_plateau();
    partie.joueur_actif = BLANC;  // Le joueur BLANC commence
    return partie;
}

// Fonction pour afficher le plateau
void afficher_plateau(Case** plateau) {
    for (int i = 0; i < MAX_CASE; i++) {
        for (int j = 0; j < MAX_CASE; j++) {
            char piece_char = '.';
            switch (plateau[i][j].p) {
                case PION: piece_char = 'P'; break;
                case TOUR: piece_char = 'T'; break;
                case CAVALIER: piece_char = 'C'; break;
                case FOU: piece_char = 'F'; break;
                case REINE: piece_char = 'D'; break;
                case ROI: piece_char = 'R'; break;
                default: break;
            }
            printf("%c ", piece_char);
        }
        printf("\n");
    }
}
