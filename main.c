#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    Case** plateau = creer_plateau();
    
    afficher_plateau(plateau);
    
    liberer_plateau(plateau);

    return 0;
}
