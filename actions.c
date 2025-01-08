

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



// fonctin qui verifie que le mouvement soit horizontal ou vertical et qui deplace le pion si c'est bon
void verti_Horiz (Coup){
    if ((xFrom == xTo) || (yFrom == yTo)){
        echiquier[xTo][yTo] = echiquier[xFrom][yFrom];
    }
    
}

// fonctin qui verifie que le mouvement soit diagonal et qui deplace le pion si c'est bon
void diagonal (Coup){
    if ((xFrom == xTo) || (yFrom == yTo)){
        echiquier[xTo][yTo] = echiquier[xFrom][yFrom];
    }
}
