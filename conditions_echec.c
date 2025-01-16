/*
Fichier qui regroupe toutes les fonctions gérant les conditions d'échec
  fonction qui verif si le mouv que je viens de faire amene une condition d'echec avec ma piece déplacé
  fonction qui verif si le mouv que je viens de faire amene une condition d'echec avec une piece qui peut manger le roi maintenant que j'ai bougé la piece
  fonction qui bloque le mouvement d'une de mes pieces si elle amenerais un echec de mon roi
*/


// on verif si le mouvement met le roi en echec
int RoiEnEchec(Partie* partie, Coup coup){

  //on stock les coordonné du tableau avant test
  Case suivant = partie->echiquier[coup.yTo][coup.xTo];
  
  //on bouge le tableau
  partie->echiquier[coup.yTo][coup.xTo] = partie->echiquier[coup.yFrom][coup.xFrom];
  partie->echiquier[coup.yFrom][coup.xFrom].p = vide;

  //on trouve le roi
  for(int i = 0; i < NB_LIGNE; i++){
    for(int j = 0; j < NB_LIGNE; j++){
      if(partie->echiquier[i][j].p == roi && partie->echiquier[i][j].c == partie->joueur_actif){
        roiX=i;
        roiY=j;
      }
    }
  }

  //on test l'echec pour toute les pieces en utilisant 
  //int echec = //true si le roi est en echec apres le mouvement 
  //car apres on dois remettre le plateau comme avant donc on dois apeller 
  //une fonction maintenant pour pouvoir renvoyer plus tard le bon return
  int echec = risquePourRoi(partie, roiX, roiY);

  //on remet le tableau comme avant (même chose mais dans l'autre sens)
  partie->echiquier[coup.yFrom][coup.xFrom] = partie->echiquier[coup.yTo][coup.xTo];
  partie->echiquier[coup.yTo][coup.xTo].p = suivant;

  return echec; //true si le roi est en echec apres le mouvement 
}

int risquePourRoi(Partie* partie, int roiX, int roiY){
  for(int i = 0; i < NB_LIGNE; i++){
    for(int j = 0; j < NB_LIGNE; j++){
      if(partie->echiquier[i][j].c != partie->joueur_actif){
                Coup coup_potentiel = {x, y, roiX, roiY};
                if(verifier_coup(partie, coup_potentiel)){
                    return 1; // risque pour le roi
                }
      }
    }
  }
  return 0; // pas de risque pour le roi
}
