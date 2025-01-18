#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
	Partie partie = creer_partie();
	
	deroulement(&partie);
    
	liberer_plateau(partie);
	return 0;
}
