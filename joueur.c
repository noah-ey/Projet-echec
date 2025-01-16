#include "declarations.h"

/*
Fichier qui gère les interactions avec les joueurs
*/

// Fonction demandant au joueur son coup dans le code généré
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



/* Fonction vérifiant si le coup est légal 
Renvoie 1 si le coup est legal, 0 sinon */
int verifier_coup(Partie* partie, Coup coup){
	Case** plateau = partie->echiquier;
	Couleur joueur = partie->joueur_actif;

	// Analysons quel type de pièce l'utilisateur veut déplacer, afin de vérifier si le coup demandé correspond
	// Cas d'une case vide
	if(plateau[coup.xFrom][coup.yFrom].p == vide){ 
		printf("Veuillez choisir une case contenant une pièce !\n");
		return 0;
	}
	// Cas d'une pièce adverse
	if(plateau[coup.xFrom][coup.yFrom].c != joueur){ 
		printf("Veuillez choisir une pièce de votre couleur !\n");
		return 0;
	}
	// Cas d'un pion 
	if(plateau[coup.xFrom][coup.yFrom].p == pion){ 
		if(abs(coup.yTo - coup.yFrom) == 1){ // Cas le plus courant, le pion avance d'une case horizontale
			return 1;
		}
		if(abs(coup.yTo - coup.yFrom) == 2){ // Cas plus rare : premier déplacement du pion possible d'avancer de 2 cases horizontales
			if(coup.xFrom == 1 || coup.xFrom == 6){
				return 1;
			}
		}
		if(diagonal(coup) && (abs(coup.yTo - coup.yFrom) == 1)){ // Cas où le pion mange une pièce : déplacement diagonale de 1 case
			if((plateau[coup.xFrom][coup.yFrom].p != vide) && (plateau[coup.xTo][coup.yTo].c != joueur)){ // Le pion mange s'il y a une pièce adverse
				return 1;
			}
		}
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
	if(plateau[coup.xFrom][coup.yFrom].p == fou){ 
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
		if(diagonal(coup) || verti(coup) || horiz(coup)){ // Le roi se déplace comme une reine 
			if((abs(coup.xTo - coup.xFrom) == 1) && (abs(coup.yTo - coup.yFrom) == 1)){ // Mais la distance est limitée à 1
				return 1;
			}
		}
		return 0;
	}
}


/* Fonction qui gère le temps disponible à chaque joueur */
void timer(clock_t start, clock_t end, Partie* partie){
	if(partie->joueur_actif == blanc){
		partie->Blanc.time -= ((double) end - start) / CLOCKS_PER_SEC;
	}
	else{
		partie->Noir.time -= ((double) end - start) / CLOCKS_PER_SEC;
	}
}

/* Fonction qui gère le déroulement de la partie d'échec */
void deroulement(Partie* partie){
	Case** plateau = partie->echiquier;
	Couleur joueur_actif = partie->joueur_actif;
	int win = 0;

	while(!win || joueur_actif.time <= 0){
		printf("Tour du joueur %s", joueur_actif);
		afficher_plateau(plateau);
		printf("Joueur : %s il vous reste %f secondes", joueur_actif, joueur_actif.time);
		clock_t start = clock();
		Coup coup = proposition_joueur(); // On demande au joueur actif quel coup il veut jouer
		if(verifier_proposition(coup)){ // Verification si la proposition est traitable 
			if(verifier_coup(coup)){ // Verification si le coup est jouable
				appliquer_coup(partie, coup);
				clock_t end = clock();
				timer(start, end, partie); // On met à jour le temps restant du joueur actif
				printf("Joueur : %s il vous reste %f secondes", joueur_actif, joueur_actif.time);
				if(joueur_actif == blanc) // Changement du joueur actif une fois le coup appliqué
					joueur_actif++;
				else
					joueur_actif--;
			}
		}
		win = 1;
	}
}
