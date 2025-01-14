#include "declarations.h"


// Demande au joueur son coup dans le code généré
Coup proposition_joueur(){
	int xFrom, yFrom, xTo, yTo;
		
	printf("Quel coup allez vous jouer ?\n");
	printf("xFrom : "); scanf("%d", &xFrom);
	printf("yFrom : "); scanf("%d", &yFrom);
	printf("xTo : "); scanf("%d", &xTo);
	printf("yTo : "); scanf("%d", &yTo);
	
	Coup res = {xFrom-1, yFrom-1, xTo-1, yTo-1};
	return (res);
}

// Fonction qui vérifie si 'prop' est un coup correspondant à l'échiquier
int verifier_proposition(Coup prop){
	
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
	
	printf("Il s'agit d'un coup\n");	
	return 1; // Si on atteind cette ligne alors la proposition est un coup
}



// Vérifie que le coup est jouable / légal ?
int verifier_coup(Partie* partie, Coup coup){
	Case** plateau = partie.echiquier;

	// Analysons quel type de pièce l'utilisateur veut déplacer, afin de vérifier si le coup demandé correspond
	// Cas d'une case vide
	if(plateau[coup.xFrom][coup.yFrom].p == vide){ 
		printf("Veuillez choisir une case contenant une pièce !\n");
		return 0;
	}
	// Cas d'une tour
	if(plateau[coup.xFrom][coup.yFrom].p == tour){ 
		if(verti(coup) || horiz(coup)){ // La tour se déplace en vertical ou en horizontal
			return 1;
		}
		return 0;
	}
	// Cas d'un cavalier
	if(plateau[coup.xFrom][coup.yFrom].p == cavalier){ 
		if(verifCavalier(coup)){
			return 1;
		}
		return 0;
	}
	// Cas d'un fou
	if(plateau[coup.xFrom][coup.yFrom].p == four){ 
		if(diagonal(coup)){ // Le fou se déplace en diagonal uniquement
			return 1;
		}
		return 0;
	}
	// Cas d'une reine
	if(plateau[coup.xFrom][coup.yFrom].p == reine){ 
		if(diagonal(coup) || verti(coup) || horiz(coup)){ // Les déplacements de la reine combine ceux d'un fou et d'une tour
			return 1;
		}
		return 0;
	}
	// Cas d'un roi
	if(plateau[coup.xFrom][coup.yFrom].p == roi){ 
		if(diagonal(coup) || verti(coup) || horiz(coup)){ // Le roi se déplace comme une reine mais dont la distance est limitée à 1
			return 1;
		}
		return 0;
	}
}
