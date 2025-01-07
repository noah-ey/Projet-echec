// Afficher l’échiquier : 9x9 car 8x8 cases + lettres et n° pour les coordonnées
// Création en début de partie     → Affichage pendant la partie
// Interaction avec le(s) joueur(s) : Demander la case puis l’action


#include "fonctions.h"

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
