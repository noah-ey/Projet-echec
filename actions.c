

// programme
// fonction qui ?
// verification de la possibilite des demandes (fichier c)
// mouvement vert/horiz
// mouvement diag
// mouvement des pieces/prend les pieces si besoin
// fonction rock
// situation d'echec

// timer
// les points des joueur
// les fonction save (qui permet de revenir en arriere une fois)

// realiser 1000 test pour par exemple si il mets é au lieu de 2 que cela ne fasse pas de la dé

// fonction qui deplace la piece sans condition
void deplacement(Coup){
    echiquier[xTo][yTo] = echiquier[xFrom][yFrom];
    echiquier[xFrom][yFrom].p = vide;
    return;
}
// fonctin qui verifie que le mouvement soit vertical et qui deplace le pion si c'est bon
int verti (Coup){
    if (yFrom != yTo)){
        printf("mouvement impossible car il n'est pas verti");
        return 0;
    }
    return 1;
}
// fonctin qui verifie que le mouvement soit horizontal et qui deplace le pion si c'est bon
int horiz (Coup){
    if ((yFrom != xTo) {
        printf("mouvement impossible car il n'est pas horiz");
        return 0;
    }
    return 1;
}
// fonctin qui verifie que le mouvement soit diagonal et qui deplace le pion si c'est bon
void diagonal (Coup){
    if ((xTo - xFrom != yTo - yFrom) || (-yTo + xFrom != xTo - yFrom) || (yTo + xFrom != xTo + yFrom)){ // dans la premiere diagonal puis dans la deuxieme diagonal en haut puis dans la deuxieme diagonal en bas
        return 0;
    }
    return 1;
}
