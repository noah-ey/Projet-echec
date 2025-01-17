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
Case** creer_plateau();
Partie creer_partie();
void liberer_plateau(Partie partie);
char aff_char(Case case_jeu);
char* couleur_piece(Couleur c);
void afficher_plateau(Partie* partie);

Coup proposition_joueur();
int verifier_proposition(Coup prop);
int verifier_coup(Partie* partie, Coup coup);
void timer(clock_t start, clock_t end, Partie* partie);
void points(Partie* partie, Couleur joueur, Coup coup);
void deroulement(Partie* partie);

void appliquer_coup(Partie* partie, Coup coup);
int verti(Coup coup);
int horiz(Coup coup);
int diagonal(Coup coup);
int verifCavalier(Coup coup);

int RoiEnEchec(Partie* partie, Coup coup);
int risquePourRoi(Partie* partie, int roiX, int roiY);
