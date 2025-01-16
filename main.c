#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    Partie* partie = creer_partie();
    
    afficher_plateau(partie->echiquier);
    
    Coup coup = proposition_joueur();
    
    int verif = verifier_proposition(coup);

    appliquer_coup(partie->echiquier, coup);

    
    
    
    liberer_plateau(partie->echiquier);
    return 0;
}
