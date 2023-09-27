#ifndef _SIMULATION_H_

#define _SIMULATION_H_
//#include "pile.h"
#include <stdbool.h>
typedef enum {SOL = '+', ARBRE = '*', FEUILLE = ' ', ROCHE = '#', HERBE = 'x', EAU = '/', CENDRES = '-', CENDRES_ETEINTES = '@', FEU = 'F'}ELEMENTS;

typedef struct{

    ELEMENTS type;
    int degre;
    int etat;

}CARTE;

typedef struct{
    int x;
    int y;
    int exit;
}LOCFEU;

CARTE** creationMatrice();
LOCFEU* creationTableauFeu();
int chercheVoisinage(CARTE** carte, LOCFEU* tableau);
void destructionMatrice(CARTE **map);
void remplir_la_carte_manuel(CARTE **map);
void remplirMatriceRandom(CARTE **map);
void affichage_de_la_carte(CARTE **map);
void copyTab(LOCFEU *tempTab, LOCFEU *newVersionTab);
void showTab(LOCFEU *tableau);
int endOfTab(LOCFEU *tableau);
void nextMap(CARTE **initialMap, CARTE **emptyMap);
bool isInBound(int x, int y);
//int CHIFFRE_ALEATOIRE
#endif