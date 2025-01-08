#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    Case** plateau = creer_plateau();
    
    afficher_plateau(plateau);
    
    Coup coup = proposition_joueur();
    
    int verif = verifier_proposition(coup);
    
    
    liberer_plateau(plateau);
    return 0;
}
