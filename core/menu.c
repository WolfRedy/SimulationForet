#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

//#include <conio.h>
#include "ext_glob.h"


#include "pile.h"
#include "menu.h"
#include "../simulation/dijkstra.h"
#include "../simulation/simulation.h"
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }

pile* pileToSave;
int iterationsNeeded;
void launchMenu(){
    char map[20][20];


    pile* pileSimulation = NULL;
    MAP** carteInitial = initMap(); // Create the first map
    affichage_de_la_carte(carteInitial);
    FLAMES* coordFeu = initFlame(carteInitial); // Create the first table of flames
    affichage_de_la_carte(carteInitial);
    push(&pileSimulation,carteInitial, coordFeu);
    iterationsNeeded = autoFindIterations(pileSimulation,carteInitial);
    modSimulation(pileSimulation, carteInitial, iterations());
    
    
}

MAP** initMap() {
    size();
    while(1) {
//Menu du progamme:
        int choix;
        printf("\n");
        printf("O - ");
        //printf("Emulation d'Incendie en Milieu Forestier:\n");
        printf("\033[0;4mEmulation d'Incendie en Milieu Forestier:\033[0m\n");
        printf("\n///////////////////////////////////////////////\n");
        printf("Press 1 - Remplissage aleatoire de la foret\n");
        printf("Press 2 - Remplissage manuel\n");
        printf("Press 3 - Remplissage via un fichier\n");
        printf("Press 4 - Quitter\n");
        printf("///////////////////////////////////////////////\n");
        printf("--> Enter votre choix:\n");

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
                remplir_la_carte_manuel(carteInitial);
                return carteInitial;
                break;
            }
            case 3: {
                printf("\n\033[0;1mAttention, pour respecter la structure du fichier\033[0m, inspectez le fichier exemple_structure.txt pour réaliser votre carte ! \n");
                //printf("\nAttention, pour respecter la structure du fichier, inspectez le fichier exemple_structure.txt pour réaliser votre carte ! \n");
                printf("Vous pouvez aussi \033[0;1mcopier/coller\033[0m la forêt d'une étape provenant d'un fichier de sauvegarde !\n");
                //printf("\033[0;1mcopier/coller\033[0m\n");
                printf("--> Indiquer le chemin complet de votre fichier sous la forme : \n-->/home/<user>/....\n");
                char filename[20];
                CLEAR_STDIN;
                scanf("%19s", filename);
                FILE *file = fopen(filename, "r");
                if (file == NULL) {
                    fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
                    break;
                }
                initTableFromFile(carteInitial, file);         
                return carteInitial;
                break;
            }
            case 4: {
                printf("Exit\n");
                exit(0);
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
    if (longueur == 0 && largeur == 0){
        printf("\n--> Choisir la longeur : \n");
        scanf("%d", &longueur);
        printf("--> Choisir la largeur : \n");
        scanf("%d", &largeur);
    }
    
}

FLAMES* initFlame(MAP** initialMap){
    FLAMES* coordFeu = createFlamesTable();
    int flameX,flameY;
    printf("--> Coordonnée x du départ de feu\n");
    CLEAR_STDIN;
    scanf("%d",&positionFlameX);
    printf("--> Coordonnée y du départ de feu\n");
    CLEAR_STDIN;
    scanf("%d",&positionFlameY);
    while(!isInBound(positionFlameX,positionFlameY)){
        printf("### Error - Out Of Bound ###\n");
        printf("--> Coordonnée x du départ de feu\n");
        CLEAR_STDIN;
        scanf("%d",&positionFlameX);
        printf("--> Coordonnée y du départ de feu\n");
        CLEAR_STDIN;
        scanf("%d",&positionFlameY);  
    }
    coordFeu->x=positionFlameX;
    coordFeu->y=positionFlameY;
    coordFeu[1].exit=-1;
    initialMap[positionFlameX][positionFlameY].type = 'F';
    initialMap[positionFlameX][positionFlameY].degree = 5;
    initialMap[positionFlameX][positionFlameY].etat = 1; 
    editMap(initialMap);
    return coordFeu;
}

int iterations(){
    int nbIterations;

    printf("--> Choisisez le nombre d'iterations \n");
    scanf("%d",&nbIterations);
    return nbIterations;
}

void modSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration){
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
        printf("Press 4 - Revenir en arrière\n");
        printf("Press 5 - Sauvegarder dans un file votre progression\n");
        printf("Press 6 - Quitter\n");
        printf("///////////////////////////////////////////////\n");
        printf("--> Enter votre choix:\n");

        CLEAR_STDIN;
        scanf("%d", &choix);
        switch (choix) {
            case 1: {
                printf("Début simulation manuel...\n");
                manualSimulation(pileSimulation, carteInitial, nombreIteration);
                break;
            }
            case 2: {
                printf("Début simulation automatique...\n");
                automaticSimulation(pileSimulation, carteInitial, nombreIteration);
                break;
            }
            case 3: {
                printf("Plus cours chemin - Algorithme de Dijkstra\n");
                launchDijkstra( carteInitial);
                break;
            }
            case 4: {
                free2DTable(carteInitial);
                launchMenu();
                break;
            }
            case 5: {
                saveExperience(pileToSave,nombreIteration);
                break;
            }
            case 6: {
                printf("Merci d'avoir utilisé notre application ! \n");
                free2DTable(carteInitial);
                cleanStack(&pileToSave, carteInitial);
                exit(1);
                return;
            }
            default:
                printf("### wrong Input ###\n");
                break;
        }
    }
}
void saveExperience(pile* pileSimulation, int nombreIteration){
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fileToSave[50];
    strftime(fileToSave, sizeof(fileToSave), "sauvegarde_%Y_%m_%d_%H:%M:%S.txt", tm_info);
    FILE *file = fopen(fileToSave, "w");
    if (file == NULL) {
        fprintf(stderr, "### Impossible d'ouvrir le file de sauvegarde. ###\n");
        return;
    }
    saveStack(pileSimulation, file, nombreIteration);
    fclose(file);
    printf("Informations sauvegardées dans votre fichier --> %s\n", fileToSave);
}
void manualSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration){
    MAP** carteSuivante = NULL;
    FLAMES* tableauSuivant = NULL;
    cleanStack(&pileSimulation,carteInitial);
    char choix;
    int i = 1;
    while(i<nombreIteration){
        
        printf("\n ------%d\n",i);
        if (i>0){
            printf("\n 1 - Revenir en arrière\n");
           
        }
        printf("\n 2 - Modifer le type d'une valeur\n");
        printf("\n 3 - Avancer \n");
        
        CLEAR_STDIN;
        scanf("%c",&choix);

        if(choix == '1' && i>0 ){
            printf("\nVous avez choisi de revenir en arrière\n");
            pop(&pileSimulation);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i--;
        }else if(choix =='2'){
            printf("\nVous avez choisi de modifier une valeur\n");
            int editPositionX;
            int editPositionY;
            printf("--> Coordonnée X de votre élément\n");
            CLEAR_STDIN;
            scanf("%d",&editPositionX);
            printf("--> Coordonnée Y de votre élément\n");
            CLEAR_STDIN;
            scanf("%d",&editPositionY);
            while(!isInBound(editPositionX,editPositionY)){
                printf("### Error : Positions Out Of Bound ! ###\nWrite new positions :\n");
                printf("--> Coordonnée X de votre élément\n");
                CLEAR_STDIN;
                scanf("%d",&editPositionX);
                printf("--> Coordonnée Y de votre élément\n");
                CLEAR_STDIN;
                scanf("%d",&editPositionY);
            }

            printf("Information actuel à la postion (%d,%d)\n\n",editPositionX,editPositionY); 
            printf("\n|-- TYPE : %c\n",pileSimulation->adresseCarte[editPositionX][editPositionY].type );
            printf("|-- DEGREE : %d\n",pileSimulation->adresseCarte[editPositionX][editPositionY].degree );
            printf("|-- ETAT : %d\n",pileSimulation->adresseCarte[editPositionX][editPositionY].etat );
            char editType;
            int editDegree;
            int editState;
            printf("--> Edit this position (%d,%d)\n",editPositionX,editPositionY); 
            printf("|-- TYPE : ? \n"); 
            CLEAR_STDIN;
            while (1) {
                if (scanf("%c",&editType) == 1 && editType == '/' || editType == '+' || editType == '-' || editType == '@' || editType == 'F' ||editType == '#' ||editType == '*') {
                    break;
                } else {
                    CLEAR_STDIN;
                    printf("### Error : Veuillez un élément valide ###\n");
                }
            }
            printf("|-- DEGREE : ? \n");
             CLEAR_STDIN;
            while (1) {
                if (scanf("%d",&editDegree) == 1 && editDegree >= 0 && editDegree <= 5) {
                    break;
                } else {
                    CLEAR_STDIN;
                    printf("### Error : Veuillez rentrer une valeur entre 0 et 5 ###\n");
                }
            }
            printf("|-- ETAT : ? \n");
            CLEAR_STDIN;
            while (1) {
                if (scanf("%c",&editState) == 1 && editState >= 0 && editState <= 1) {
                    break;
                } else {
                    CLEAR_STDIN;
                    printf("### Error : Veuillez rentrer une valeur entre 0 et 1 ###\n");
                }
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
            searchNeighbourhood(carteSuivante,tableauSuivant);
            if(isFinished(carteSuivante,pileSimulation->adresseCarte)){
                i=nombreIteration;
                pileToSave = pileSimulation;
                return;
            }
            push(&pileSimulation,carteSuivante, tableauSuivant);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i++;
        }
    }
    pileToSave = pileSimulation;
}
void automaticSimulation(pile* pileSimulation, MAP** carteInitial, int nombreIteration){
    MAP** carteSuivante = NULL;
    FLAMES* tableauSuivant = NULL;
    cleanStack(&pileSimulation,carteInitial);
    for(int index = 1; index<nombreIteration+1; index++){
        //sleep(1);
        carteSuivante = create2DTable();
        nextMap(pileSimulation->adresseCarte,carteSuivante);
        tableauSuivant = createFlamesTable();
        copyTab(pileSimulation->tabCoordFeu, tableauSuivant);
        searchNeighbourhood(carteSuivante,tableauSuivant);
        if(isFinished(carteSuivante,pileSimulation->adresseCarte)){
                pileToSave = pileSimulation;
                index=nombreIteration;
                return;
        }
        push(&pileSimulation,carteSuivante, tableauSuivant);
        printf("\n ------%d\n",index);
        affichage_de_la_carte(pileSimulation->adresseCarte);
    }
    pileToSave = pileSimulation;
}
int autoFindIterations(pile* pileSimulation, MAP** carteInitial){
    int choix;
    printf("Souhaitez vous connaître le nombre d'itérations nécessaires pour brûler complètement une forêt à partir de votre départ de feu ?\n0 -> non\n1 -> oui\n");
    CLEAR_STDIN;
    scanf("%d", &choix);
    cleanStack(&pileSimulation,carteInitial);

    MAP** carteSuivante = NULL;
    FLAMES* tableauSuivant = NULL;
    int index = 1;
    while(1){
        carteSuivante = create2DTable();
        nextMap(pileSimulation->adresseCarte,carteSuivante);
        tableauSuivant = createFlamesTable();
        copyTab(pileSimulation->tabCoordFeu, tableauSuivant);

        searchNeighbourhood(carteSuivante,tableauSuivant);
        if(isFinished(carteSuivante,pileSimulation->adresseCarte)){
            if(choix==1){
                printf("Nombre d'itérations nécessaires -> %d\n", index);
            }
            return index;
        }

        push(&pileSimulation,carteSuivante, tableauSuivant);
        index++;
    } 
}