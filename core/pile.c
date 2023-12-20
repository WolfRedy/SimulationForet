#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ext_glob.h"
#include "pile.h"
#include "../simulation/simulation.h" 

void push(pile **laPile, MAP **map, FLAMES *tableauFeu){
    pile *elementCourant = malloc(sizeof(pile));
    if(!elementCourant) exit(EXIT_FAILURE);
    elementCourant->adresseCarte = map;
    elementCourant->prec = *laPile;
    elementCourant->tabCoordFeu = tableauFeu;
    //elementCourant->nbFlames = newFlames;
    *laPile = elementCourant;
}

void pop(pile **laPile){
    free2DTable((*laPile)->adresseCarte);
    FLAMES *oldTab;
    MAP **map;
    pile *tmp;
    
    tmp = (*laPile)->prec;
    map = (*laPile)->adresseCarte;
    
    free(*laPile);
    *laPile = tmp;
}
void view(pile *p){
    int i = 0;
        while(p)
          {
             //printf("\n %d Adresse %x \n Coord :%d,%d ",i,p->adresseCarte,p->tabCoordFeu->x,p->tabCoordFeu->y);
             p = p->prec;
             i++;
          }
}
void saveStack(pile *p,FILE *file, int iterations){
    int i = 0;
    int index = iterations;
    while (p) {
        saveToFile(p->adresseCarte, file, index);
        p = p->prec;
        index--;
        i--;
    }
}
void cleanStack(pile **p, MAP** initialMap){
    pile *tmp;
    while((*p)->adresseCarte != initialMap){
        tmp = (*p)->prec;
        free(*p);
        *p = tmp;
    }
}