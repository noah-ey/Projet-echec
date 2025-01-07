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

// Structure pour un nœud de liste chaînée
typedef struct noeud {
    Case data;
    struct noeud* suivant;  // Pointeur vers la case suivante
} Noeud;

// Structure pour une rangée
typedef struct rangee {
    Noeud* debut;          // Début de la rangée
    struct rangee* suivante; // Pointeur vers la rangée suivante
} Rangee;

// Structure pour une partie
typedef struct partie {
    Rangee* plateau;       // Pointeur vers la première rangée
    Couleur joueur_actif;
} Partie;

// Fonction pour créer un nœud
Noeud* creer_noeud(Piece p, Couleur c) {
    Noeud* nouveau = malloc(sizeof(Noeud));
    if (!nouveau) {
        perror("Erreur d'allocation mémoire pour un nœud");
        exit(EXIT_FAILURE);
    }
    nouveau->data.p = p;
    nouveau->data.c = c;
    nouveau->suivant = NULL;
    return nouveau;
}

// Fonction pour créer une rangée
Rangee* creer_rangee() {
    Rangee* nouvelle = malloc(sizeof(Rangee));
    if (!nouvelle) {
        perror("Erreur d'allocation mémoire pour une rangée");
        exit(EXIT_FAILURE);
    }
    nouvelle->debut = NULL;
    nouvelle->suivante = NULL;
    return nouvelle;
}

// Fonction pour ajouter une case à une rangée
void ajouter_case(Rangee* rang, Piece p, Couleur c) {
    Noeud* nouveau = creer_noeud(p, c);
    if (!rang->debut) {
        rang->debut = nouveau;
    } else {
        Noeud* temp = rang->debut;
        while (temp->suivant) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
    }
}

// Fonction pour créer un plateau
Rangee* creer_plateau() {
    Rangee* plateau = NULL;
    Rangee* derniere_rang = NULL;

    // Créer les 8 rangées
    for (int i = 0; i < MAX_CASE; i++) {
        Rangee* nouvelle_rang = creer_rangee();
        if (!plateau) {
            plateau = nouvelle_rang;
        } else {
            derniere_rang->suivante = nouvelle_rang;
        }
        derniere_rang = nouvelle_rang;

        // Initialiser chaque rangée avec des cases
        for (int j = 0; j < MAX_CASE; j++) {
            if (i == 1) {
                ajouter_case(nouvelle_rang, PION, NOIR);
            } else if (i == 6) {
                ajouter_case(nouvelle_rang, PION, BLANC);
            } else if (i == 0 || i == 7) {
                Piece ordre_pieces[] = { TOUR, CAVALIER, FOU, REINE, ROI, FOU, CAVALIER, TOUR };
                Couleur couleur = (i == 0) ? NOIR : BLANC;
                ajouter_case(nouvelle_rang, ordre_pieces[j], couleur);
            } else {
                ajouter_case(nouvelle_rang, VIDE, BLANC);
            }
        }
    }
    return plateau;
}

