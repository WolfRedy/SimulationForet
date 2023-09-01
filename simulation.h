#include <stdio.h>
#include <stdlib.h>


typedef enum {SOL = '+', ARBRE = '*', FEUILLE = ' ', ROCHE = '#', HERBE = 'x', EAU = '/', CENDRES = '-', CENDRES_ETEINTES = '@'}ELEMENTS;

typedef struct{

    ELEMENTS type;
    int degre;
    int etat;

}CARTE;

CARTE** creationMatrice(int longeur, int largeur);
void destructionMatrice(CARTE **map, int longueur);
void remplirMatriceRandom(CARTE **map, int longueur, int largeur);
void afficheMatrice(CARTE **map, int longueur, int largeur);
//int CHIFFRE_ALEATOIRE
