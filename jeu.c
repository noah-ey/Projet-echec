// programme
// fonction qui ?
// mouvement vert/horiz
// mouvement diag
// verification de la possibilite des demandes
// mouvement des pieces/prend les pieces si besoin
// fonction rock

// timer
// les points des joueur


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
Case** creer_echiquier() {
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

