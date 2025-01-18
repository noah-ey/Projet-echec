#include "declarations.h"

/* ***********************************************
Fichier qui gère les interactions avec les joueurs
************************************************* */

/* Fonction qui permet de savoir le coup du joueur */
Coup proposition_joueur(Coup coup){
	printf("Quel coup allez vous jouer ?\n");

	int xFrom, xTo;
	char posI, posF;
	Coup res;
	
	printf("Case de départ : "); 
	scanf("%c%d", &posI, &xFrom);
	while (getchar() != '\n'); // Pour clear le buffer
	
	printf("Case d'arrivée : "); 
	scanf("%c%d", &posF, &xTo); 
	while (getchar() != '\n'); // Pour clear le buffer

	// Conversion des coordonnées
    res.xFrom = xFrom - 1;
    res.yFrom = posI - 'A';
    res.xTo = xTo - 1;
    res.yTo = posF - 'A';
	
	return (res);
}


/* Fonction qui vérifie si 'prop' est un coup correspondant à l'échiquier */
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
		if(abs(coup.xTo - coup.xFrom) == 1){ // Cas le plus courant, le pion avance d'une case horizontale
			return 1;
		}
		if(abs(coup.xTo - coup.xFrom) == 2){ // Cas plus rare : premier déplacement du pion possible d'avancer de 2 cases horizontales
			if((coup.xFrom == 1 && joueur == noir) || (coup.xFrom == 6 && joueur == blanc)){
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
    printf("Veuillez choisir une pièce");
    return 0;
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

/* Fonction compte les points des joueurs 
Le coup donné en arguement aura été préalablement vérifié */
void points(Partie* partie, Couleur joueur, Coup coup){
    int x = coup.xTo; // On s'intéresse uniquement aux coordonnées d'arrivée
    int y = coup.yTo;
    Piece piece = partie->echiquier[x][y].p;
    if(joueur == blanc){
        if(piece == pion){
            partie->Blanc.score += 1;
        }
        else if(piece == tour){
            partie->Blanc.score += 5;
        }
        else if(piece == cavalier){
            partie->Blanc.score += 3;
        }
        else if(piece == fou){
            partie->Blanc.score += 3;
        }
        else if(piece == reine){
            partie->Blanc.score += 9;
        }
        else if(piece == roi){
            partie->Blanc.score += 1000; // Permettra de détecter qu'on a mangé le roi et donc de finir la partie
        }
    }
    else{
        if(piece == pion){
            partie->Noir.score += 1;
        
        }
        else if(piece == tour){
            partie->Noir.score += 5;
        
        }
        else if(piece == cavalier){
            partie->Noir.score += 3;
        
        }
        else if(piece == fou){
            partie->Noir.score += 3;
        
        }
        else if(piece == reine){
            partie->Noir.score += 9;
        
        }
        else if(piece == roi){
            partie->Noir.score += 1000; // Permettra de détecter qu'on a mangé le roi et donc de finir la partie
        
        }
    }
}

/* Fonction qui gère le déroulement de la partie d'échec */
void deroulement(Partie* partie){
	Couleur joueur_actif = partie->joueur_actif;
	int win = 0;
	int est_echec = 0;

	while(!win && partie->Blanc.time > 0 && partie->Noir.time > 0){
        if(joueur_actif == blanc){ // Cas joueur Blanc / On sépare les deux cas pour accéder à partie->Blanc.time
            printf("\nScore Blanc : %d / Noir : %d\n", partie->Blanc.score, partie->Noir.score);
			afficher_plateau(partie);
			printf("Tour du joueur blanc\n");
            printf("Joueur blanc il vous reste %f secondes\n", partie->Blanc.time);
            clock_t start = clock();

            Coup coup = proposition_joueur(coup); // On demande au joueur actif quel coup il veut jouer
            if(verifier_proposition(coup)){ // Verification si la proposition est traitable 
                if(verifier_coup(partie, coup)){ 
					                 
					points(partie, blanc, coup);
					est_echec = RoiEnEchec(partie, coup);
					
                    appliquer_coup(partie, coup); // Réalise la promotion du pion s'il peut en faire une
                    clock_t end = clock();
                    timer(start, end, partie); // On met à jour le temps restant du joueur actif
                    printf("Joueur blanc il vous reste %f secondes\n",partie->Blanc.time);

					if(est_echec){
						printf("Le roi Noir est en echec !\n");
						est_echec = 0;
					}

                    joueur_actif = (joueur_actif == blanc) ? noir : blanc;  // Changement du joueur actif une fois le coup appliqué
					partie->joueur_actif = joueur_actif;
					printf("Changement de joueur : joueur_actif = %d\n", joueur_actif);
                }
            }
        }
        else{ // Cas joueur Noir
			printf("\nScore Blanc : %d / Noir : %d\n", partie->Blanc.score, partie->Noir.score);
            afficher_plateau(partie);
			printf("Tour du joueur noir\n");
            printf("Joueur noir il vous reste %f secondes\n", partie->Noir.time);
            clock_t start = clock();
            Coup coup = proposition_joueur(coup); // On demande au joueur actif quel coup il veut jouer
            if(verifier_proposition(coup)){ // Verification si la proposition est traitable 
				printf("Proposition invalide, veuillez réessayer.\n");
                if(verifier_coup(partie, coup)){ // Verification si le coup est jouable
					printf("Coup non valide, veuillez réessayer.\n");
                    points(partie, noir, coup);
					est_echec = RoiEnEchec(partie, coup);
                    appliquer_coup(partie, coup);
					promotion(partie,coup); // Réalise la promotion du pion s'il peut en faire une
                    clock_t end = clock();
                    timer(start, end, partie); // On met à jour le temps restant du joueur actif
                    printf("Joueur noir il vous reste %f secondes\n", partie->Noir.time);

					if(est_echec){
						printf("Le roi Blanc est en echec !\n");
						est_echec = 0;
					}

                    joueur_actif = (joueur_actif == noir) ? blanc : noir;  // Changement du joueur actif une fois le coup appliqué
					partie->joueur_actif = joueur_actif;
					printf("Changement de joueur : joueur_actif = %d\n", joueur_actif);
                }
            }
        }
        if(partie->Blanc.score > 1000 || partie->Noir.score > 1000) // Condition qui permet de remarquer que le roi a été mangé
		    win = 1;
	}

	// Fin de partie, annonce du gagnant :
	if(win){
		if(partie->Blanc.score > 1000){
			printf("Les blancs ont gagné par echec et mat !\n");
		}
		else{
			printf("Les noirs ont gagné par echec et mat !\n");
		}
	}
	else{
		if(partie->Blanc.time <= 0){
			printf("Le joueur Blanc a perdu par manque de temps !\n");
		}
		else{
			printf("Le joueur noir a perdu par manque de temps !\n");
		}
	}
}

