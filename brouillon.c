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
typedef enum piece { vide, pion, tour, cavalier, fou, reine, roi } Piece;
typedef enum couleur { blanc, noir } Couleur;

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
    Case** echiquier;
    Couleur joueur_actif;
} Partie;

// Fonction pour allouer et initialiser l'échiquier
Case** creer_echiquier() {
    // On alloue l'échiquier 8x8
    Case** echiquier = (Case**)malloc(MAX_CASE * sizeof(Case*));
    if (echiquier == NULL) {
        printf("Erreur Dans L’Allocation Mémoire Pour L’Échiquier\n");
        exit(1);
    }

    // On alloue chaque ligne de l'échiquier
    for (int i = 0; i < MAX_CASE; i++) {
        echiquier[i] = (Case*)malloc(MAX_CASE * sizeof(Case));
        if (echiquier[i] == NULL) {
            printf("Erreur Dans L’Allocation Mémoire Pour Une Ligne De L’Échiquier\n");
            exit(1);
        }
    }

    // On initialise l'échiquier avec des cases vides
    for (int i = 0; i < MAX_CASE; i++) {
        for (int j = 0; j < MAX_CASE; j++) {
            echiquier[i][j].p = vide;
            echiquier[i][j].c = blanc; // Par Défaut, Toutes Les Cases Sont Blanches
        }
    }

    // On place les pions
    for (int j = 0; j < MAX_CASE; j++) {
        echiquier[1][j].p = pion;
        echiquier[1][j].c = noir;
        echiquier[6][j].p = pion;
        echiquier[6][j].c = blanc;
    }

    // On place les pièces
    Piece ordre_pieces[] = { tour, cavalier, fou, reine, roi, fou, cavalier, tour };
    for (int j = 0; j < MAX_CASE; j++) {
        echiquier[0][j].p = ordre_pieces[j];
        echiquier[0][j].c = noir;
        echiquier[7][j].p = ordre_pieces[j];
        echiquier[7][j].c = blanc;
    }

    return echiquier;
}
