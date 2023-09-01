#include <stdio.h>
#include <stdlib.h>


typedef enum {SOL = '+', ARBRE = '*', FEUILLE = ' ', ROCHE = '#', HERBE = 'x', EAU = '/', CENDRES = '-', CENDRES_ETEINTES = '@'}ELEMENTS;

typedef struct{

    ELEMENTS type;
    int degre;
    int etat;

}CARTE;

void MATRICE_ALEATOIRE();
//int CHIFFRE_ALEATOIRE
