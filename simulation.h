#ifndef _SIMULATION_H_

#define _SIMULATION_H_
//#include "pile.h"
#include <stdbool.h>
typedef enum {SOL = '+', ARBRE = '*', FEUILLE = ' ', ROCHE = '#', HERBE = 'x', EAU = '/', CENDRES = '-', CENDRES_ETEINTES = '@', FEU = 'F'}ELEMENTS;

typedef struct{

    ELEMENTS type;
    int degree;
    int etat;

}MAP;

typedef struct{
    int x;
    int y;
    int exit;
}FLAMES;

MAP** create2DTable();
FLAMES* createFlamesTable();
int searchNeighbourhood(MAP** map, FLAMES* flamesTable);
void free2DTable(MAP **map);
void remplir_la_carte_manuel(MAP **map);
void initRandom2DTable(MAP **map);
void affichage_de_la_carte(MAP **map);
void copyTab(FLAMES *tempTab, FLAMES *newVersionTab);
void showTab(FLAMES *tableau);
int endOfTab(FLAMES *tableau);
void nextMap(MAP **initialMap, MAP **emptyMap);
bool isInBound(int x, int y);
void cutTab(FLAMES *tab, int cutIndex);
void editColor(ELEMENTS currentElement);
void editMap(MAP **infoMap);
bool setFire(int x, int y, MAP **map);
void decrementDegree(int x, int y, MAP **infoMap);
void typeToAsh(int x, int y, MAP **infoMap);
//int CHIFFRE_ALEATOIRE
#endif