
#include <stdio.h>
#include <stdlib.h>

int main() {
    Case** plateau = creer_echiquier();
    
    afficher_plateau(plateau);
    
    for (int i = 0; i < NB_LIGNE; i++) {
        free(plateau[i]);
    }
    free(plateau);

    return 0;
}
