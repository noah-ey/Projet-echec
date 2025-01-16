#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NB_LIGNE 8
#define GAME_TIME 600


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
typedef struct joueur{
    Couleur c;
    double time;
    int score;
} Joueur;

typedef struct partie {
    Case** echiquier;
    Couleur joueur_actif;
    Joueur Blanc;
    Joueur Noir;
} Partie;



//Définitons de toutes les fonctions
Case **creer_partie();
void liberer_plateau(Case **plateau);
char aff_char(Case case_jeu);
char* couleur_piece(Couleur c);
void afficher_plateau(Case** plateau);

Coup proposition_joueur();
int verifier_proposition(Coup prop);
int verifier_coup(Partie* partie, Coup coup);
void deroulement(Case** echiquier);

void appliquer_coup(Partie* partie, Coup coup);
int verti(Coup coup);
int horiz(Coup coup);
int diagonal(Coup coup);
int verifCavalier(Coup coup);


