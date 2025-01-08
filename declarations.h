#include <stdlib.h>
#include <stdio.h>
#define NB_LIGNE 8

//Définitons de toutes les fonctions
Case **creer_plateau();
Case *creer_plateau_liste();
void affichage(Partie* partie); 


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
