#ifndef _MENU_H_
#define _MENU_H_
#include "pile.h"
#include "../simulation/simulation.h"

MAP** initMap();
void size();
FLAMES* initFlame(MAP** initialMap);
int iterations();
void launchMenu();
void modSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration);
void manualSimulation(pile* pileSimulation,MAP** carteInitial,int nombreIteration);
void automaticSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration);
int autoFindIterations(pile* pileSimulation, MAP** carteInitial);
void saveExperience(pile* pileSimulation,int nombreIteration);
//void appDijkstra(carteInitial,pointD, pointA);
#endif
