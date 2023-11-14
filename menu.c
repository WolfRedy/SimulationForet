#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ext_glob.h"
#include "simulation.h"
#include "pile.h"
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }



MAP** affichageMenu() {
    while(1) {
//Menu du progamme:
        int choix;
        printf("\n");
        printf("O - ");
        printf("Emulation d'Incendie en Milieu Forestier:\n");
        printf("///////////////////////////////////////////////\n");
        printf("Press 1 - Remplissage aleatoire de la foret\n");
        printf("Press 2 - Remplissage manuel\n");
        printf("Press 3 - Quitter\n");
        printf("///////////////////////////////////////////////\n");
        printf("Enter votre choix:\n");

        CLEAR_STDIN;
        scanf("%d", &choix);
        MAP** carteInitial = create2DTable();
        switch (choix) {
            case 1: {
                printf("Remplissage aleatoire de la foret en cours...\n");
                initRandom2DTable(carteInitial);
                return carteInitial;
                break;
            }
            case 2: {
                printf("Remplissage manuel en cours ...\n");
                return choix = 2;
                break;
            }
            case 3: {
                printf("Exit\n");
                return choix = 3;
                break;
            }
            default:
                printf("wrong Input\n");
                //return 0;
                break;
        }
    }
}

void size(){
    int valeur = 0;
    printf("Choisir la longeur : \n");
    scanf("%d", &valeur);
    longueur = valeur;
    printf("Choisir la largeur : \n");
    scanf("%d", &valeur);
    largeur = valeur;
}

FLAMES* initFlame(MAP** initialMap){
    FLAMES* coordFeu = createFlamesTable();
    int positionFlameX,positionFlameY;
    printf("Coordonnée x du départ de feu");
    CLEAR_STDIN;
    scanf("%d",&positionFlameX);//optimiser ça plus tard
    printf("Coordonnée y du départ de feu");
    CLEAR_STDIN;
    scanf("%d",&positionFlameY);
    while(!isInBound(positionFlameX,positionFlameY)){
        printf("Error - Out Of Bound\n");
        printf("Coordonnée x du départ de feu");
        CLEAR_STDIN;
        scanf("%d",&positionFlameX);//optimiser ça plus tard
        printf("Coordonnée y du départ de feu");
        CLEAR_STDIN;
        scanf("%d",&positionFlameY);  
    }
    coordFeu->x=positionFlameX;
    coordFeu->y=positionFlameY;
    coordFeu[1].exit=-1;
    initialMap[positionFlameX][positionFlameY].type = '*';
    initialMap[positionFlameX][positionFlameY].degree = 4;
    initialMap[positionFlameX][positionFlameY].etat = 1;//Faire le cas si ça tombe sur de l'eau
    editMap(initialMap);
    return coordFeu;
}

int iterations(){
    int nbIterations;
    printf("choisisez le nombre d'iterations \n");
    scanf("%d",&nbIterations);//verify 
    return nbIterations;
}

void menuSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration, int nbFlames){
    while(1) {
//Menu du progamme:
        int choix;
        printf("\n");
        printf("1 - ");
        printf("Choix du mode de la simulation : \n");
        printf("///////////////////////////////////////////////\n");
        printf("Press 1 - Simulation Manuel\n");
        printf("Press 2 - Simulation automatique\n");
        printf("Press 3 - Plus court chemin\n");
        printf("///////////////////////////////////////////////\n");
        printf("Enter votre choix:\n");

        CLEAR_STDIN;
        scanf("%d", &choix);
        switch (choix) {
            case 1: {
                printf("Début simulation manuel...\n");
                manualSimulation(pileSimulation, carteInitial, nombreIteration, nbFlames);
                return;
                break;
            }
            case 2: {
                printf("Début simulation automatique...\n");
                //return choix = 2;
                break;
            }
            case 3: {
                printf("Plus cours chemin\n");
                return choix = 3;
                break;
            }
            default:
                printf("wrong Input\n");
                //return 0;
                break;
        }
    }
}

void manualSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration, int nbFlames){
    MAP** carteSuivante = NULL;
    FLAMES* tableauSuivant = NULL;
    char choix;
    int i = 0;
    while(i<nombreIteration){
        
        printf("\n ------%d\n",i);
        if (i>0){
            printf(" \n 1 - Revenir en arrière\n");
           
        }
        printf("\n 2 - Modifer le type d'une valeur\n");
        printf("\n 3 - Avancer \n");
        
        CLEAR_STDIN;
        scanf("%c",&choix);
       
        if(choix == '1'){
            printf("\nVous avez choisi de revenir en arrière\n");
            pop(&pileSimulation);
            //view(pileSimulation);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i--;
        }else if(choix =='2'){
            printf("\nVous avez choisi de modifier une valeur\n");
            int editPositionX;
            int editPositionY;
            CLEAR_STDIN;
            scanf("%d",&editPositionX);// Vérifier si c'est dans la bordure
            CLEAR_STDIN;
            scanf("%d",&editPositionY);
            while(!isInBound(editPositionX,editPositionY)){
                printf("Error : Positions Out Of Bound !\nWrite new positions :\n");
                CLEAR_STDIN;
                scanf("%d",&editPositionX);// Vérifier si c'est dans la bordure
                CLEAR_STDIN;
                scanf("%d",&editPositionY);
            }
            //printf("%d %d",editPositionX,editPositionY);

            printf("Information actuel à la postion (%d,%d)\n\n",editPositionX,editPositionY); 
            printf("TYPE : %c\n",pileSimulation->adresseCarte[editPositionX][editPositionY].type );
            printf("DEGREE : %d\n",pileSimulation->adresseCarte[editPositionX][editPositionY].degree );
            printf("STATE : %d\n",pileSimulation->adresseCarte[editPositionX][editPositionY].etat );
            char editType;
            int editDegree;
            int editState;
            printf("Edit this position (%d,%d)\n",editPositionX,editPositionY); // Test to change the position
            //CLEAR_STDIN;
            printf("TYPE : ? \n"); // Test good type
            CLEAR_STDIN;
            scanf("%c",&editType);
            printf("DEGREE : ? \n");// Test 0-5
            CLEAR_STDIN;
            scanf("%d",&editDegree);
            printf("STATE : ? \n"); // Test 0 or 1 
            CLEAR_STDIN;
            while(scanf("%c",&editState) || editState > 1 || editState < 0){
                printf("La valeur doit être 0 ou 1");
            }
            pileSimulation->adresseCarte[editPositionX][editPositionY].type = editType;
            pileSimulation->adresseCarte[editPositionX][editPositionY].degree = editDegree;
            pileSimulation->adresseCarte[editPositionX][editPositionY].etat = editState;

            
        }else if(choix == '3'){
            
            printf("\nVous avez choisi d'avancer\n");
            
            carteSuivante = create2DTable();
            nextMap(pileSimulation->adresseCarte,carteSuivante);
            tableauSuivant = createFlamesTable();
            copyTab(pileSimulation->tabCoordFeu, tableauSuivant);

            nbFlames = searchNeighbourhood(carteSuivante,tableauSuivant);
            push(&pileSimulation,carteSuivante, tableauSuivant);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i++;
            
        }
        
    }
}