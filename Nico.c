#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_LIGNE 8


// Définition des structures
typedef enum piece { 
    vide, pion, tour, cavalier, fou, reine, roi 
} Piece;
typedef enum couleur {
blanc, noir 
} Couleur;

typedef struct Case {
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



//Définitons de toutes les fonctions
Case **creer_plateau();
void liberer_plateau(Case **plateau);
char aff_char(Case case_jeu);
char* couleur_piece(Couleur c);
void afficher_plateau(Case** plateau);

Coup proposition_joueur();
int verifier_proposition(Coup prop);
int verifier_coup(Partie* partie, Coup coup);
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Fonction pour obtenir le caractère de la pièce
char aff_char(Case case_jeu) {
    switch (case_jeu.p) {
        case pion: return (case_jeu.c == blanc) ? 'P' : 'p';
        case tour: return (case_jeu.c == blanc) ? 'T' : 't';
        case cavalier: return (case_jeu.c == blanc) ? 'C' : 'c';
        case fou: return (case_jeu.c == blanc) ? 'F' : 'f';
        case reine: return (case_jeu.c == blanc) ? 'D' : 'd';
        case roi: return (case_jeu.c == blanc) ? 'R' : 'r';
        default: return ' ';
    }
}

// Fonction pour obtenir la couleur d'affichage d'une pièce
char* couleur_piece(Couleur c) {
    return (c == blanc) ? "\033[32m" : "\033[31m";  // Vert pour blanc, Rouge pour noir
}

// Fonction pour allouer et initialiser l'échiquier
Case** creer_plateau() {
    // On alloue l'échiquier 8x8
    Case** echiquier = (Case**)malloc(NB_LIGNE * sizeof(Case*));
    if (echiquier == NULL) {
        printf("Erreur dans l'allocation mémoire pour l'échiquier\n");
        exit(1);
    }

    // On alloue chaque ligne de l'échiquier
    for (int i = 0; i < NB_LIGNE; i++) {
        echiquier[i] = (Case*)malloc(NB_LIGNE * sizeof(Case));
        if (echiquier[i] == NULL) {
            printf("Erreur dans l'allocation mémoire pour une ligne de l'échiquier\n");
            exit(1);
        }
    }

    // On initialise l'échiquier avec les cases vides
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
            echiquier[i][j].p = vide;
            echiquier[i][j].c = blanc; // Par défaut, toutes les cases sont blanches
        }
    }

    // On place les pions
    for (int j = 0; j < NB_LIGNE; j++) {
        echiquier[1][j].p = pion;
        echiquier[1][j].c = noir;
        echiquier[6][j].p = pion;
        echiquier[6][j].c = blanc;
    }

    // On place les pièces
    Piece ordre_pieces[] = { tour, cavalier, fou, reine, roi, fou, cavalier, tour };
    for (int j = 0; j < NB_LIGNE; j++) {
        echiquier[0][j].p = ordre_pieces[j];
        echiquier[0][j].c = noir;
        echiquier[7][j].p = ordre_pieces[j];
        echiquier[7][j].c = blanc;
    }

    return echiquier;
}



// Fonction pour libérer l'échiquier
void liberer_plateau(Case **plateau){
    for (int i = 0; i < NB_LIGNE; i++) {
            free(plateau[i]);
        }
        free(plateau);
}

// Fonction pour afficher l'échiquier avec des couleurs de fond
void afficher_plateau(Case** plateau) {
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m     \033[0m");
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m     \033[0m");
            }
        }
        printf("\n");

        // Afficher les pièces sur chaque case
        for (int j = 0; j < NB_LIGNE; j++) {
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m  %s%c  \033[0m", couleur_piece(plateau[i][j].c), aff_char(plateau[i][j]));
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m  %s%c  \033[0m", couleur_piece(plateau[i][j].c), aff_char(plateau[i][j]));
            }
        }
        printf("\n");

    // Redondance/ Supprimer ?? Nico explique moi mdr
        for (int j = 0; j < NB_LIGNE; j++) {
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m     \033[0m");
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m     \033[0m");
            }
        }
        printf("\n");
    }
}
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// fonction qui deplace la piece sans condition
void appliquer_coup(Case** echiquier,Coup coup){
	echiquier[coup.xTo][coup.yTo] = echiquier[coup.xFrom][coup.yFrom];
    	echiquier[coup.xFrom][coup.yFrom].p = vide;
    	return;
}

// fonction qui verifie que le mouvement soit vertical
int verti(Coup coup){
	if (coup.yFrom == coup.yTo){
		return 1;
	}
	printf("mouvement impossible car il n'est pas verti\n");
	return 0;
}
// fonction qui verifie que le mouvement soit horizontal
int horiz(Coup coup){
	if (coup.xFrom == coup.xTo) {
		return 1;
	}
	printf("mouvement impossible car il n'est pas horiz\n");
    	return 0;
}
// fonction qui verifie que le mouvement soit diagonal
int diagonal(Coup coup){
	if (abs(coup.xTo - coup.xFrom) == abs(coup.yTo - coup.yFrom)){ //HAHA la valeur absolue suffisait bien mdrr
		return 1;
	}
	printf("mouvement impossible car il n'est pas verti\n");
	return 0;
}
// fonction qui verifie que le mouvement soit bon pour le cavalier
int verifCavalier(Coup coup){
	if (((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1) || (abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1))){ // 2 fois la même condition, je pense qu'il faut changer quelque chose
		return 1;
	} 
	printf("Mouvement impossible car cela ne correspond pas au cavalier\n");
	return 0;
}

OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
#include "declarations.h"


// Demande au joueur son coup dans le code généré
Coup proposition_joueur(){
	int xFrom, yFrom, xTo, yTo;
		
	printf("Quel coup allez vous jouer ?\n");
	printf("xFrom : "); scanf("%d", &xFrom);
	printf("yFrom : "); scanf("%d", &yFrom);
	printf("xTo : "); scanf("%d", &xTo);
	printf("yTo : "); scanf("%d", &yTo);
	
	Coup res = {xFrom, yFrom, xTo, yTo};
	return (res);
}

// Fonction qui vérifie si 'prop' est un coup correspondant à l'échiquier
int verifier_proposition(Case** echiquier,Coup prop){
	
	if(prop.xFrom >= NB_LIGNE || prop.xFrom < 0){
		printf("Attention il ne s'agit pas d'un coup\n");
		return 0;
		}
	if(prop.yFrom >= NB_LIGNE || prop.yFrom < 0){
		printf("Attention il ne s'agit pas d'un coup\n");
		return 0;
	}
	if(prop.xTo >= NB_LIGNE || prop.xTo < 0){
		printf("Attention il ne s'agit pas d'un coup\n");
		return 0;
	}
	if(prop.yTo >= NB_LIGNE || prop.yTo < 0){
		printf("Attention il ne s'agit pas d'un coup\n");
		return 0;
	}
	if (echiquier[prop.xFrom][prop.yFrom].p == vide) {
   		printf("La case initiale est vide\n");
    		return 0;
	}
	printf("Il s'agit d'un coup\n");	
	return 1; // Si on atteind cette ligne alors la proposition est un coup
}

