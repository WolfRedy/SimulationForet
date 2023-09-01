#include <stdlib.h>
#include <stdio.h>

int affichageMenu() {
    while(1) {
//Menu du progamme:
        int choix;
        printf("\n");
        printf("O - ");
        printf("Emulation d'Incendie en Milieu Forestier:\n");
        printf("///////////////////////////////////////////////\n");
        printf("Press 1 - Remplissage aleatoire de la foret\n");
        printf("Press 2 - Remplissage manuel\n");
        printf("Press 3 - Quitter\n");
        printf("///////////////////////////////////////////////\n");
        printf("Enter votre choix:\n");

        scanf("%d", &choix);

//Choix:
        switch (choix) {
            case 1: {
                printf("Remplissage aleatoire de la foret en cours...\n");
                return choix = 1;3;
                break;
            }
            case 2: {
                printf("Remplissage manuel en cours ...\n");
                return choix = 2;
                break;
            }
            case 3: {
                printf("Exit\n");
                return choix = 3;
                break;
            }
            default:
                printf("wrong Input\n");
                return 0;
                break;

        }
    }
}

void choixTaille(int * longu, int * larg){
    printf("Choisir la longeur : \n");
    scanf("%d", longu);
    printf("Choisir la largeur : \n");
    scanf("%d", larg);
}