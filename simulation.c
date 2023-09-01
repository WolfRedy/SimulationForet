#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"



void MATRICE_ALEATOIRE(){

    int longeur;
    int largeur;

    printf("Choisir la longeur : ");
    scanf("%d", &longeur);
    printf("Choisir la largeur : ");
    scanf("%d", &largeur);

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

