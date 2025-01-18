#include "declarations.h"

/* ********************************************************************
Fichier qui regroupe toutes les fonctions gérant les conditions d'échec
*********************************************************************** */


/* *************************************************************
Fonction qui vérifie si le mouvement met le roi adverse en echec
Renvoie 1 si le roi adverse est en echec
**************************************************************** */
int RoiEnEchec(Partie* partie, Coup coup){
    int roiX, roiY;
    //on stock les coordonné du tableau avant test
    Case suivant = partie->echiquier[coup.yTo][coup.xTo];

    //on bouge le tableau
    partie->echiquier[coup.yTo][coup.xTo] = partie->echiquier[coup.yFrom][coup.xFrom];
    partie->echiquier[coup.yFrom][coup.xFrom].p = vide;

    //on trouve le roi adverse
    for(int i = 0; i < NB_LIGNE; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            if(partie->echiquier[i][j].p == roi && partie->echiquier[i][j].c != partie->joueur_actif){
            roiX=i;
            roiY=j;
            }
        }
    }

    int echec = risquePourRoi(partie, roiX, roiY);

    //on remet le tableau comme avant (même chose mais dans l'autre sens)
    partie->echiquier[coup.yFrom][coup.xFrom] = partie->echiquier[coup.yTo][coup.xTo];
    partie->echiquier[coup.yTo][coup.xTo].p = suivant.p;

    return echec; //true si le roi est en echec apres le mouvement 
}


/* ************************************************************************
Fonction qui renvoie 1 s'il y a un risque de capturer le roi (de couleur adverse) en roiXn roiY
************************************************************************ */
int risquePourRoi(Partie* partie, int roiX, int roiY){
    for(int i = 0; i < NB_LIGNE; i++){
        for(int j = 0; j < NB_LIGNE; j++){
            if(partie->echiquier[i][j].c == partie->joueur_actif){ // On vérifie uniquement les coups pour la couleur du joueur actif
                        Coup coup_potentiel = {i, j, roiX, roiY};
                        if(verifier_coup(partie, coup_potentiel)){
                            printf("La case %d, %d met le roi en echec", i, j);
                            return 1; // risque pour le roi
                        }
            }
        }
    }
    return 0; // pas de risque pour le roi
}
