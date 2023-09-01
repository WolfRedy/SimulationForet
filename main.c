#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

int main()
{
    int longeur;
    int largeur;
    printf("Choisir la longeur : \n");
    scanf("%d", &longeur);
    printf("Choisir la largeur : \n");
    scanf("%d", &largeur);
    
    creationMatrice(longeur, largeur);




    return 0;
}
