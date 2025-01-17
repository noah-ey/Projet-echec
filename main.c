#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

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
