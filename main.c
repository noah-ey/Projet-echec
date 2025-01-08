#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    Case** plateau = creer_echiquier();
    
    afficher_plateau(plateau);
    
    

    return 0;
}
