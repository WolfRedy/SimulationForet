#ifndef _PILE_H_
#define _PILE_H_
#include <stdio.h>
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
void saveStack(pile *p,FILE *file, int iterations);
void cleanStack(pile **p, MAP** initialMap);

#endif