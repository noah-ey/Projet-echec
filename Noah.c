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



/* ***************************************************

Programme qui contient les fonctions nécessaires à la création et à l'affichage de l'échiquier

*************************************************** */

// Fonction pour obtenir le caractère de la pièce
char aff_char(Case case_jeu) {
    switch (case_jeu.p) {
        case pion: return (case_jeu.c == blanc) ? 'P' : 'p';
        case tour: return (case_jeu.c == blanc) ? 'T' : 't';
        case cavalier: return (case_jeu.c == blanc) ? 'C' : 'c';
        case fou: return (case_jeu.c == blanc) ? 'F' : 'f';
        case reine: return (case_jeu.c == blanc) ? 'D' : 'd';
        case roi: return (case_jeu.c == blanc) ? 'R' : 'r';
        default: return ' ';
    }
}

// Fonction pour obtenir la couleur d'affichage d'une pièce
char* couleur_piece(Couleur c) {
    return (c == blanc) ? "\033[32m" : "\033[31m";  // Vert pour blanc, Rouge pour noir
}

/* Fonction pour allouer et initialiser l'échiquier */
Case** creer_plateau(){
    // On alloue l'échiquier 8x8
    Case** echiquier = (Case**)malloc(NB_LIGNE * sizeof(Case*));
    if (echiquier == NULL) {
        printf("Erreur dans l'allocation mémoire pour l'échiquier\n");
        exit(1);
    }

    // On alloue chaque ligne de l'échiquier
    for (int i = 0; i < NB_LIGNE; i++) {
        echiquier[i] = (Case*)malloc(NB_LIGNE * sizeof(Case));
        if (echiquier[i] == NULL) {
            printf("Erreur dans l'allocation mémoire pour une ligne de l'échiquier\n");
            exit(1);
        }
    }

    // On initialise l'échiquier avec des cases vides
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
            echiquier[i][j].p = vide;
            echiquier[i][j].c = blanc; // Par défaut, toutes les cases sont blanches
        }
    }

    // On place les pions
    for (int j = 0; j < NB_LIGNE; j++) {
        echiquier[1][j].p = pion;
        echiquier[1][j].c = noir;
        echiquier[6][j].p = pion;
        echiquier[6][j].c = blanc;
    }

    // On place les pièces
    Piece ordre_pieces[] = { tour, cavalier, fou, reine, roi, fou, cavalier, tour };
    for (int j = 0; j < NB_LIGNE; j++) {
        echiquier[0][j].p = ordre_pieces[j];
        echiquier[0][j].c = noir;
        echiquier[7][j].p = ordre_pieces[j];
        echiquier[7][j].c = blanc;
    }
    return echiquier;
}

/* Fonction pour initialiser la partie et ses variables */
Partie creer_partie() {
    Partie partie;

    partie.echiquier = creer_plateau();

    partie.joueur_actif = blanc; // Le blanc commencera
    partie.Blanc.time = GAME_TIME;
    partie.Blanc.score = 0;

    partie.Noir.time = GAME_TIME;
    partie.Noir.score = 0;

    return partie;
}



// Fonction pour libérer l'échiquier
void liberer_plateau(Partie partie){
    Case **plateau = partie.echiquier;
    for (int i = 0; i < NB_LIGNE; i++) {
            free(plateau[i]);
        }
        free(plateau);
}

// Fonction pour afficher l'échiquier avec des couleurs de fond
void afficher_plateau(Partie* partie){
    Case** plateau = partie->echiquier;

    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
		printf("   ");
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m     \033[0m");
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m     \033[0m");
            }
        }
        printf("\n");
        // affiche les chiffres sur chaque ligne
        printf(" %d ", 1 + i);

        // Afficher les pièces sur chaque case
        for (int j = 0; j < NB_LIGNE; j++) {
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m  %s%c  \033[0m", couleur_piece(plateau[i][j].c), aff_char(plateau[i][j]));
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m  %s%c  \033[0m", couleur_piece(plateau[i][j].c), aff_char(plateau[i][j]));
            }
        }
        printf("\n");

        for (int j = 0; j < NB_LIGNE; j++) {
            if ((i + j) % 2 == 0) {
                // Case sombre : bleu foncé
                printf("\033[48;5;17m     \033[0m");
            } else {
                // Case claire : gris clair
                printf("\033[48;5;250m     \033[0m");
            }
        }
        printf("\n");
    }
     // Affiche les lettres sous les cases
    printf("   A     B     C     D     E     F    G");
    
    printf("\n");
}


/* ***********************************
Fichier qui gère les mouvements des pièces
******************************************** */



// fonction qui applique le coup demandé, il faut préalablement tester si le coup est légal et jouable
void appliquer_coup(Partie* partie,Coup coup){
	Case** echiquier = partie->echiquier;
	
	echiquier[coup.xTo][coup.yTo] = echiquier[coup.xFrom][coup.yFrom];
    	echiquier[coup.xFrom][coup.yFrom].p = vide;
}

// fonction qui verifie que le mouvement soit vertical
int verti(Coup coup){
	if (coup.yFrom == coup.yTo){
		return 1;
	}
	printf("mouvement impossible car il n'est pas verti\n");
	return 0;
}
// fonction qui verifie que le mouvement soit horizontal
int horiz(Coup coup){
	if (coup.xFrom == coup.xTo) {
		return 1;
	}
	printf("mouvement impossible car il n'est pas horiz\n");
    	return 0;
}
// fonction qui verifie que le mouvement soit diagonal
int diagonal(Coup coup){
	if (abs(coup.xTo - coup.xFrom) == abs(coup.yTo - coup.yFrom)){
		return 1;
	}
	printf("mouvement impossible car il n'est pas verti\n");
	return 0;
}
// fonction qui verifie que le mouvement soit bon pour le cavalier
int verifCavalier(Coup coup){
	if ((((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1)) || ((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1)))){ // 2 fois la même condition, je pense qu'il faut changer quelque chose
		return 1;
	} 
	printf("Mouvement impossible car cela ne correspond pas au cavalier\n");
	return 0;
}



/* *******************************************
Fichier qui gère les interactions avec les joueurs
********************************************** */

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
        if(piece == vide){
            break;
        }
        if(piece == pion){
            partie->Blanc.score += 1;
            break;
        }
        if(piece == tour){
            partie->Blanc.score += 5;
            break;
        }
        if(piece == cavalier){
            partie->Blanc.score += 3;
            break;
        }
        if(piece == fou){
            partie->Blanc.score += 3;
            break;
        }
        if(piece == reine){
            partie->Blanc.score += 9;
            break;
        }
        if(piece == roi){
            partie->Blanc.score += 1000; // Permettra de détecter qu'on a mangé le roi et donc de finir la partie
            break;
        }
    }
    else{
        if(piece == vide){
            break;
        }
        if(piece == pion){
            partie->Noir.score += 1;
            break;
        }
        if(piece == tour){
            partie->Noir.score += 5;
            break;
        }
        if(piece == cavalier){
            partie->Noir.score += 3;
            break;
        }
        if(piece == fou){
            partie->Noir.score += 3;
            break;
        }
        if(piece == reine){
            partie->Noir.score += 9;
            break;
        }
        if(piece == roi){
            partie->Noir.score += 1000; // Permettra de détecter qu'on a mangé le roi et donc de finir la partie
            break;
        }
    }
}

/* Fonction qui gère le déroulement de la partie d'échec */
void deroulement(Partie* partie){
	//Case** plateau = partie->echiquier;
	Couleur joueur_actif = partie->joueur_actif;
	int win = 0;

	while(!win || partie->Blanc.time <= 0 || partie->Noir.time <= 0){
        if(joueur_actif == blanc){ // Cas joueur Blanc / On sépare les deux cas pour accéder à partie->Blanc.time
            printf("Tour du joueur blanc\n");

            afficher_plateau(partie);
            printf("Joueur blanc il vous reste %f secondes\n", partie->Blanc.time);
            clock_t start = clock();
            Coup coup = proposition_joueur(); // On demande au joueur actif quel coup il veut jouer
            if(verifier_proposition(coup)){ // Verification si la proposition est traitable 
                if(verifier_coup(partie, coup)){ // Verification si le coup est jouable
                    points(partie, blanc, coup);
                    appliquer_coup(partie, coup);
                    clock_t end = clock();
                    timer(start, end, partie); // On met à jour le temps restant du joueur actif
                    printf("Joueur blanc il vous reste %f secondes\n",partie->Blanc.time);
                    joueur_actif = noir;  // Changement du joueur actif une fois le coup appliqué
                }
            }
        }
        else{ // Cas joueur Noir
            printf("Tour du joueur noir\n");

            afficher_plateau(partie);
            printf("Joueur noir il vous reste %f secondes\n", partie->Noir.time);
            clock_t start = clock();
            Coup coup = proposition_joueur(); // On demande au joueur actif quel coup il veut jouer
            if(verifier_proposition(coup)){ // Verification si la proposition est traitable 
                if(verifier_coup(partie, coup)){ // Verification si le coup est jouable
                    points(partie, noir, coup);
                    appliquer_coup(partie, coup);
                    clock_t end = clock();
                    timer(start, end, partie); // On met à jour le temps restant du joueur actif
                    printf("Joueur noir il vous reste %f secondes\n", partie->Noir.time);
                    joueur_actif = blanc;  // Changement du joueur actif une fois le coup appliqué
                }
            }
        }
        if(partie->Blanc.score > 1000 || partie->Noir.score > 1000) // Condition qui permet de remarquer que le roi a été mangé
		    win = 1;
	}
}


/* ********************************************************************
Fichier qui regroupe toutes les fonctions gérant les conditions d'échec
  fonction qui verif si le mouv que je viens de faire amene une condition d'echec avec ma piece déplacé
  fonction qui verif si le mouv que je viens de faire amene une condition d'echec avec une piece qui peut manger le roi maintenant que j'ai bougé la piece
  fonction qui bloque le mouvement d'une de mes pieces si elle amenerais un echec de mon roi
*********************************************************************** */


// on verif si le mouvement met le roi en echec
int RoiEnEchec(Partie* partie, Coup coup){
    int roiX, roiY;
    //on stock les coordonné du tableau avant test
    Case suivant = partie->echiquier[coup.yTo][coup.xTo];

    //on bouge le tableau
    partie->echiquier[coup.yTo][coup.xTo] = partie->echiquier[coup.yFrom][coup.xFrom];
    partie->echiquier[coup.yFrom][coup.xFrom].p = vide;

    //on trouve le roi
    for(int i = 0; i < NB_LIGNE; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            if(partie->echiquier[i][j].p == roi && partie->echiquier[i][j].c == partie->joueur_actif){
            roiX=i;
            roiY=j;
            }
        }
    }

    //on test l'echec pour toute les pieces en utilisant 
    //int echec = //true si le roi est en echec apres le mouvement 
    //car apres on dois remettre le plateau comme avant donc on dois apeller 
    //une fonction maintenant pour pouvoir renvoyer plus tard le bon return
    int echec = risquePourRoi(partie, roiX, roiY);

    //on remet le tableau comme avant (même chose mais dans l'autre sens)
    partie->echiquier[coup.yFrom][coup.xFrom] = partie->echiquier[coup.yTo][coup.xTo];
    partie->echiquier[coup.yTo][coup.xTo].p = suivant.p;

    return echec; //true si le roi est en echec apres le mouvement 
}


int risquePourRoi(Partie* partie, int roiX, int roiY){
    for(int i = 0; i < NB_LIGNE; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            if(partie->echiquier[i][j].c != partie->joueur_actif){ // Il faudra surement faire un test en début de fonction de qui est le joueur actif
                        Coup coup_potentiel = {i, j, roiX, roiY};
                        if(verifier_coup(partie, coup_potentiel)){
                            printf("La case %d, %d met le roi en echec", i, j);
                            return 1; // risque pour le roi
                        }
            }
        }
    }
    return 0; // pas de risque pour le roi
}






int main() {
	Partie partie = creer_partie();
	
	afficher_plateau(&partie);
	/*
	Coup coup = proposition_joueur();
	
	//int verif = verifier_proposition(coup);
	
	appliquer_coup(&partie, coup);
	
	afficher_plateau(&partie);
	*/
	deroulement(&partie);
    
	liberer_plateau(partie);
	return 0;
}
