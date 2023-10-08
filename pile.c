#include <stdio.h>
#include <stdlib.h>
#include "ext_glob.h"
#include "pile.h"
#include "simulation.h" 

void push(pile **laPile, CARTE **map, LOCFEU *tableauFeu, int newFlames){
//void push(pile **laPile, int valeur){
    pile *elementCourant = malloc(sizeof(pile));
    if(!elementCourant) exit(EXIT_FAILURE);
    //elementCourant->adresseCarte = map;
    elementCourant->adresseCarte = map;
    elementCourant->prec = *laPile;
    elementCourant->tabCoordFeu = tableauFeu;
    elementCourant->nbFlames = newFlames;
    *laPile = elementCourant;
    //printf("\n aaa %x aaa \n",map);
}

//CARTE** pop(pile **laPile){
void pop(pile **laPile){
    destructionMatrice((*laPile)->adresseCarte);
    LOCFEU *oldTab;
    //int index = endOfTab((*laPile)->tabCoordFeu);
    //cutTab((*laPile)->tabCoordFeu, ((*laPile)->nbFlames )- index);
    CARTE **map;
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