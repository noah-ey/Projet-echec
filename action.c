#include "declarations.h"

/* ***********************************
Fichier qui gère les mouvements des pièces
******************************************** */



/* *************************************************************************
fonction qui applique le coup demandé, il faut préalablement tester si le coup est légal et jouable
************************************************************************** */
void appliquer_coup(Partie* partie,Coup coup){
	Case** echiquier = partie->echiquier;
	
	echiquier[coup.xTo][coup.yTo] = echiquier[coup.xFrom][coup.yFrom];
    	echiquier[coup.xFrom][coup.yFrom].p = vide;
}

/* fonction qui verifie que le mouvement soit vertical */
int verti(Coup coup){
	if (coup.yFrom == coup.yTo){
		return 1;
	}
	printf("mouvement impossible car il n'est pas verti\n");
	return 0;
}

/* fonction qui verifie que le mouvement soit horizontal */
int horiz(Coup coup){
	if (coup.xFrom == coup.xTo) {
		return 1;
	}
	printf("mouvement impossible car il n'est pas horiz\n");
    	return 0;
}

/* fonction qui verifie que le mouvement soit diagonal */
int diagonal(Coup coup){
	if (abs(coup.xTo - coup.xFrom) == abs(coup.yTo - coup.yFrom)){
		return 1;
	}
	printf("mouvement impossible car il n'est pas diagonal\n");
	return 0;
}

/* fonction qui verifie que le mouvement soit bon pour le cavalier */
int verifCavalier(Coup coup){
	if ((((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1)) || ((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1)))){ // 2 fois la même condition, je pense qu'il faut changer quelque chose
		return 1;
	} 
	printf("Mouvement impossible car cela ne correspond pas au cavalier\n");
	return 0;
}


/* Fonction qui s'occupe de la promotion d'un pion*/
void promotion(Partie* partie, Coup coup){
	if((coup.xTo == 0 && partie->joueur_actif == blanc) || (coup.xTo == 1 && partie->joueur_actif == noir)){
		char new;
		printf("Promotion du pion ! Veuillez choisi une pièce parmis [p, t, c, f, d] : ");
		scanf("%c", &new);

		if(new == 'd'){
			partie->echiquier[coup.xTo][coup.yTo].p = reine;
		}
		else if(new == 't'){
			partie->echiquier[coup.xTo][coup.yTo].p = tour;
		}
		else if(new == 'f'){
			partie->echiquier[coup.xTo][coup.yTo].p = fou;
		}
		else if(new == 'c'){
			partie->echiquier[coup.xTo][coup.yTo].p = cavalier;
		}
		else if(new == 'p'){
			partie->echiquier[coup.xTo][coup.yTo].p = pion;
		}
		else{
			partie->echiquier[coup.xTo][coup.yTo].p = reine;
			printf("Entrée non correcte mais pas grave ce sera une reine !\n");
		}
	}
}