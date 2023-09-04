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
                CARTE** adresseCarte;
                struct pile *prec;
        } pile ;
void view(pile *p);
void push(pile **laPile, CARTE** carte);
CARTE** creationMatrice();
void destructionMatrice(CARTE **map);
void remplirMatriceRandom(CARTE **map);
void afficheMatrice(CARTE **map);
//int CHIFFRE_ALEATOIRE
#endif