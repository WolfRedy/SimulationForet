#include "simulation.h"
#include "menu.h"
#define _MAIN_
#include "ext_glob.h"
#include <stdio.h>
#include <stdlib.h>




int main()
{
    int longueur = 0;
    int largeur = 0;
    affichageMenu();
    choixTaille();
    //printf("%d %d \n", longueur, largeur);

    CARTE** test = creationMatrice();
    //printf("%d",test);
    remplirMatriceRandom(test);
    afficheMatrice(test);
    destructionMatrice(test);
    //destructionMatrice(map,longueur);


    return 0;
}
