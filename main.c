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

    CARTE** test1 = creationMatrice();
    CARTE** test2 = creationMatrice();
    //printf("%d",test);
    remplirMatriceRandom(test1);
    remplirMatriceRandom(test2);
    //afficheMatrice(test1);
    //creationPile();
    pile* pileSimulation = NULL;
    push(&pileSimulation,test1);
    push(&pileSimulation,test2);
    //ush(&pileSimulation,10);
    view(pileSimulation);
    destructionMatrice(test1);
    destructionMatrice(test2);
    //destructionMatrice(map,longueur);


    return 0;
}
