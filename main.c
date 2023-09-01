#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "menu.h"

int main()
{
    affichageMenu();
    int longueur;
    int largeur;
    choixTaille(&longueur,&largeur);
    //printf("%d %d \n", longueur, largeur);

    CARTE** test = creationMatrice(longueur, largeur);
    //printf("%d",test);
    remplirMatriceRandom(test,  longueur,  largeur);
    afficheMatrice(test,  longueur,  largeur);
    destructionMatrice(test, longueur);
    //destructionMatrice(map,longueur);


    return 0;
}
