

// programme
// fonction qui ?
// verification de la possibilite des demandes (fichier c)
// mouvement des pieces/prend les pieces si besoin
// fonction rock
// situation d'echec

// timer
// les points des joueur
// les fonction save (qui permet de revenir en arriere une fois)

// realiser 1000 test pour par exemple si il mets é au lieu de 2 que cela ne fasse pas de la dé

// fonction qui deplace la piece sans condition
void deplacement(Coup coup){
    echiquier[xTo][yTo] = echiquier[xFrom][yFrom];
    echiquier[xFrom][yFrom].p = vide;
    return;
}
// fonctin qui verifie que le mouvement soit vertical
int verti (Coup coup){
    if (yFrom == yTo)){
        printf("mouvement impossible car il n'est pas verti\n");
        return 1;
    }
    return 0;
}
// fonctin qui verifie que le mouvement soit horizontal
int horiz (Coup coup){
    if ((yFrom == xTo) {
        printf("mouvement impossible car il n'est pas horiz\n");
        return 1;
    }
    return 0;
}
// fonctin qui verifie que le mouvement soit diagonal
int diagonal (Coup coup){
    if (xTo - xFrom == yTo - yFrom){  // dans la premiere diagonal
        return 1;
    } if (-yTo + xFrom == xTo - yFrom){  // dans la deuxieme diagonal 
        return 1;
    } if (yTo + xFrom == xTo + yFrom){  // dans la deuxieme diagonal en bas
        return 1;
    }
    return 0;
}
// fonctin qui verifie que le mouvement soit bon pour le cavalier
int mouvcavalier (Coup coup){
    if ((abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1) || (abs (coup.xTo - coup.xFrom) == 2) && (abs (coup.yTo - coup.yFrom) == 1)){
        return 1;
    } 
    printf("Mouvement impossible car cela ne correspond pas au cavalier\n");
    return 0;
}

