#ifndef _PILE_H_
#define _PILE_H_
#include "simulation.h"
typedef struct pile
        {
                CARTE** adresseCarte;
                LOCFEU* tabCoordFeu;
                int nbFlames;
                struct pile *prec;
        } pile ;

void view(pile *p);
void push(pile **laPile, CARTE **map, LOCFEU *tableauFeu,int nbFlames);
void pop(pile **laPile);

#endif