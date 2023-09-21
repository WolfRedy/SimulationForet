#include <stdio.h>
#include <stdlib.h>
#include "ext_glob.h"
#include "pile.h"
#include "simulation.h" 

void push(pile **laPile, CARTE **map, LOCFEU *tableauFeu){
//void push(pile **laPile, int valeur){
    pile *elementCourant = malloc(sizeof(pile));
    if(!elementCourant) exit(EXIT_FAILURE);
    //elementCourant->adresseCarte = map;
    elementCourant->adresseCarte = map;
    elementCourant->prec = *laPile;
    elementCourant->tabCoordFeu = tableauFeu;
    *laPile = elementCourant;
    //printf("\n aaa %x aaa \n",map);
}

//CARTE** pop(pile **laPile){
void pop(pile **laPile){
    
    CARTE **map;
    pile *tmp;
    
    //if(!*laPile) return NULL;
    
    tmp = (*laPile)->prec;
    map = (*laPile)->adresseCarte;
    //printf("\n ee %x eee\n",*tmp);
    //printf(" \n ee %x eee \n",map);
    
    free(*laPile);
    *laPile = tmp;
    //return map;
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