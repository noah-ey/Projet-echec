#include <stdlib.h>
#include <stdio.h>


//Définitons de toutes les fonctions
Case **creer_plateau();
Case *creer_plateau_liste();
void affichage(Partie* partie); 




// Déclaration des structures
enum piece{
	VIDE, PION, TOUR, CAVALIER, FOU, REINE, ROI
	};
typedef enum piece Piece;

enum couleur{
	BLANC, NOIR
	};
typedef enum couleur Couleur;

struct case{
	Piece piece;
	Couleur couleur;
	};
Typedef struct case Case

struct coup{
	int xFrom;
	int yFrom;
	int xTo;
	int yTo;
	};
Typedef struct coup Coup

struct partie{
	Case** plateau;
	Couleur joueur_actif;
	};
Typedef struct partie Partie
