#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"



void creationMatrice(int longeur, int largeur){
    

    CARTE **foret = (CARTE**)malloc(sizeof(CARTE)*longeur);

    for (int i = 0;i<longeur;i++){
        foret[i] = (CARTE*)malloc(largeur*sizeof(CARTE));
    }

    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < longeur; j++) {
            printf("%c ", ARBRE);
        }
        printf("\n");
    }

    for(int i=0;i<longeur;i++){
        free(foret[i]);
    }

    free(foret);
/*
for (int i = 0; i <taille ; i++) {
    n = rand() % 8 + 1;
    printf("%d\n", n);
  }
  */
}




void matriceManu (){




}

