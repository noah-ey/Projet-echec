#include "declarations.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires à la création et à l'affichage de l'échiquier

*************************************************** */


/* Fonction pour obtenir le caractère de la pièce */
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

/* Fonction pour obtenir la couleur d'affichage d'une pièce */
char* couleur_piece(Couleur c) {
    return (c == blanc) ? "\033[32m" : "\033[31m";  // Vert pour blanc, Rouge pour noir
}

/* Fonction pour allouer et initialiser l'échiquier */
Case** creer_plateau(){
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

    // On initialise l'échiquier avec des cases vides
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

/* Fonction pour initialiser la partie et ses variables */
Partie creer_partie() {
    Partie partie;

    partie.echiquier = creer_plateau();

    partie.joueur_actif = blanc; // Le blanc commencera
    partie.Blanc.time = GAME_TIME;
    partie.Blanc.score = 0;

    partie.Noir.time = GAME_TIME;
    partie.Noir.score = 0;

    return partie;
}



/* Fonction pour libérer l'échiquier */
void liberer_plateau(Partie partie){
    Case **plateau = partie.echiquier;
    for (int i = 0; i < NB_LIGNE; i++) {
            free(plateau[i]);
        }
        free(plateau);
}

/* Fonction pour afficher l'échiquier avec des couleurs de fond */
void afficher_plateau(Partie* partie){
    Case** plateau = partie->echiquier;

    for (int i = 0; i < NB_LIGNE; i++) {
	    printf("   ");
        for (int j = 0; j < NB_LIGNE; j++){

            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m     \033[0m");
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m     \033[0m");
            }
        }
        printf("\n");
        // affiche les chiffres sur chaque ligne
        printf(" %d ", 1 + i);
	
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
        printf("   ");
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
     // Affiche les lettres sous les cases
    printf("     A    B    C    D    E    F    G    H");
    
    printf("\n");
}
