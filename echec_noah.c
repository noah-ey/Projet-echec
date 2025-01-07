#include "declarations.h"

Case **creer_plateau(){
    // Allocation mémoire d'un plateau d'échec
    Case** plateau = (Case**)malloc(sizeof(Case*) * NB_LIGNE);
    for(int i = 0; i < NB_LIGNE; i++){
        *plateau = (Case*)malloc(sizeof(Case) * NB_LIGNE);
    }

    // Initialisation de l'échiquier
    // Les cases vides
    for(int i = 2; i <= 5; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            plateau[i][j].piece = VIDE;
        }
    }

    // Les pions
    for(int j = 0; j < NB_LIGNE; j++){
        plateau[1][j].piece = PION;
        plateau[6][j].piece = PION;
    }

    // Les autres pièces
    Piece ordre[] = {TOUR, CAVALIER, FOU, ROI, REINE, FOU, CAVALIER, TOUR};
    for(int j = 0; j < NB_LIGNE; j++){
        plateau[0][j].piece = ordre[j];
        plateau[0][j].couleur = BLANC;
        plateau[6][j].piece = ordre[j];
        plateau[6][j].couleur = NOIR;
    }

    return plateau;
}



void affiche_plateau(Case** plateau){
    for(int i = 0; i < NB_LIGNE; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            // Affichage si la case est vide
            if(plateau[i][j].piece == VIDE){
                printf("\t ");
            }

            // Affichage si la case est blanche
            else if(plateau[i][j].couleur == BLANCHE){
                Piece type_piece = PION;
                if(plateau[i][j].piece == type_piece) printf("\tp"); // Test s'il s'agit d'un pion
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tr"); // Une tour
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tn"); // Un cavalier
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tb"); // Un fou
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tq"); // Une reine
                type_piece++;
                else printf("\tk"); // Un roi
            }

            // Affichage si la case est noire
            else{
                Piece type_piece = PION;
                if(plateau[i][j].piece == type_piece) printf("\tP"); // Test s'il s'agit d'un pion
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tR"); // Une tour
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tN"); // Un cavalier
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tB"); // Un fou
                type_piece++;
                else if(plateau[i][j].piece == type_piece) printf("\tQ"); // Une reine
                type_piece++;
                else printf("\tK"); // Un roi
            }
        }
    }
}