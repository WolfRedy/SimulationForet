#ifndef _SIMULATION_H_
#define _SIMULATION_H_


typedef enum {SOL = '+', ARBRE = '*', FEUILLE = ' ', ROCHE = '#', HERBE = 'x', EAU = '/', CENDRES = '-', CENDRES_ETEINTES = '@'}ELEMENTS;

typedef struct{

    ELEMENTS type;
    int degre;
    int etat;

}CARTE;

typedef struct pile
        {
                int valeur;
                struct pile *prec;
        } pile ;

CARTE** creationMatrice();
void destructionMatrice(CARTE **map);
void remplirMatriceRandom(CARTE **map);
void afficheMatrice(CARTE **map);
//int CHIFFRE_ALEATOIRE
#endif