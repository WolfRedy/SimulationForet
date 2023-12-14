#ifndef _PILE_H_
#define _PILE_H_
#include "../simulation/simulation.h"
typedef struct pile
        {
                MAP** adresseCarte;
                FLAMES* tabCoordFeu;
                int nbFlames;
                struct pile *prec;
        } pile ;

void view(pile *p);
void push(pile **laPile, MAP **map, FLAMES *tableauFeu);
void pop(pile **laPile);

#endif