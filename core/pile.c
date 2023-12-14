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
             printf("\n %d Adresse %x \n Coord :%d,%d ",i,p->adresseCarte,p->tabCoordFeu->x,p->tabCoordFeu->y);
             p = p->prec;
             i++;
          }
}