#include "simulation.h"
#include "menu.h"
#include "pile.h"
#define _MAIN_
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#include "ext_glob.h"
#include <stdio.h>
#include <stdlib.h>




int main()
{

    pile* pileSimulation = NULL;
    ELEMENTS laValeurModif;

    size();
    MAP** carteInitial = affichageMenu();
    affichage_de_la_carte(carteInitial);
    FLAMES* coordFeu = initFlame(carteInitial);
    affichage_de_la_carte(carteInitial);

    push(&pileSimulation,carteInitial, coordFeu);

    int nbIterations = iterations();
    menuSimulation(pileSimulation, carteInitial, nbIterations);
  
    free2DTable(carteInitial);
    return 0;
}
