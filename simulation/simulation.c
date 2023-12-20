
#include <stdio.h>
#include <time.h> 
#include <stdbool.h>

#include <stdlib.h> 
#include "simulation.h"
#include "../core/ext_glob.h"
#include "../core/pile.h"
#include <assert.h>

#include <ncurses.h>


/*
create2DTable : create a dynamic 2-Dimension table
@param void
@return MAP**
*/
MAP** create2DTable(){
    
    MAP **forest = (MAP**)malloc(sizeof(MAP)*longueur);
    assert( forest != NULL );
    for (int i = 0;i<longueur;i++){
        forest[i] = (MAP*)malloc(largeur*sizeof(MAP));
        assert( forest[i] != NULL );
    }
  return forest; 
}

/*
createFireTable : create a dynamic table for flames positions
@param void
@return FLAMES* 
*/
FLAMES* createFlamesTable(){
    FLAMES *table = (FLAMES*)malloc(sizeof(FLAMES)*(longueur*largeur)+1);
    return table;
}
void saveToFile(MAP **map, FILE *file, int index) {
    fprintf(file, "----- ---- Etape %d ---- -----\n",index);
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            fprintf(file, "%c",map[i][j].type);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}
void initTableFromFile(MAP **initialMap, FILE *file){
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            int caractere = getc(file);
            while (caractere == '\n' || caractere == '\r') {
                caractere = getc(file);
            }
            if (caractere == EOF) {
                fprintf(stderr, "Le fichier ne contient pas suffisamment de caractères.\n");
                fclose(file);
                return; 
            }
            createFromCharacter((char)caractere, initialMap, i, j);
        }
    }
}
void createFromCharacter(char currentChar, MAP **map,int i, int j){
    switch(currentChar){
                case '+':
                    map[i][j].type=SOL;
                    map[i][j].degree=0;
                    break;
                case '*':
                    map[i][j].type=ARBRE;
                    map[i][j].degree=4;
                    break;
                case ' ':
                    map[i][j].type=FEUILLE;
                    map[i][j].degree=2;

                    break;
                case '#':
                    map[i][j].type=ROCHE;
                    map[i][j].degree=5;

                    break;
                case 'x':
                    map[i][j].type=HERBE;
                    map[i][j].degree=3;

                case '/':
                    map[i][j].type=EAU;
                    map[i][j].degree=0;
                    break;
                case '-':
                    map[i][j].type=CENDRES;
                    map[i][j].degree=1;
                    break;
                case '@':
                    map[i][j].type=CENDRES_ETEINTES;
                    map[i][j].degree=0;
                    break;
                case 'F':
                    map[i][j].type=FEU;
                    map[i][j].degree=2;
                    map[i][j].etat=1;
                    
                    break;
                default:
                    map[i][j].type=HERBE;
                    map[i][j].degree=3;
            }
}

void affichage_de_la_carte(MAP **map){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            int etat = map[i][j].etat;
            switch(etat){
                case 1:
                    printf("\033[0;31m"); 
                    break;
                case -1: //depart
                    printf("\e[1;92m");
                    break;
                case -5: //destination
                    printf("\033[0;31m");
                default:
                    editColor(map[i][j].type);
            }
            printf(" %c",map[i][j].type);
        }
        printf("\033[0m");
        printf("\n");
    }
    
}

/*
editColor : Change the ascii color for an element in the map
@param currentElement : current element in the map
@return void 
*/
void editColor(ELEMENTS currentElement){
    switch(currentElement){
        case SOL:
            printf("\033[0;37m");
            break;
        case ARBRE:
            printf("\033[0;32m");
            break;
        case FEUILLE:
            printf("\033[0;32m");
            break;
        case ROCHE:
            printf("\033[0;30m");
            break;
        case HERBE:
            printf("\033[0;32m");
            break;
        case EAU:
            printf("\033[0;34m");
            break;
        case CENDRES:
            printf("\033[0;30m");
            break;
        case CENDRES_ETEINTES:
            printf("\033[0;30m");
        default:
            printf("\033[0;37m");

    }    
}

void remplir_la_carte_manuel(MAP **map) {
    //La MAP au départ n'est que du sol dans le mode manuel:
    int choix;
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            map[i][j].type = SOL;
        }
    }
    
    //Matrice remplie de manière manuel:
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            printf("[1] - SOL [+] , [2] - ARBRE [*], [3] - FEUILLE [ ], [4] - ROCHE [#]\n");
            printf("[5] - HERBE [x], [6] - EAU [/], [7] - CENDRES [-], [8] - CENDRES_ETEINTES [@]\n");
            scanf("%d", &choix);
            switch (choix) {
                        case 1:
                            map[i][j].type = SOL;
                            break;
                        case 2:
                            map[i][j].type = ARBRE;
                            break;
                        case 3:
                            map[i][j].type = FEUILLE;
                            break;
                        case 4:
                            map[i][j].type = ROCHE;
                            break;
                        case 5:
                            map[i][j].type = HERBE;
                            break;
                        case 6:
                            map[i][j].type = EAU;
                            break;
                        case 7:
                            map[i][j].type = CENDRES;
                            break;
                        case 8:
                            map[i][j].type = CENDRES_ETEINTES;
                            break;
                        default :
                            map[i][j].type = SOL;
                    }
                    printf("Vous avez appuyé la touche [%d].\n", choix);
                    printf("L'élément [%c] est sur la case [%d][%d].\n", map[i][j].type, i, j);
                    printf("------------------------------------------------O\n");
                    affichage_de_la_carte(map);
            }
        }
    printf("La création de la MAP est finie.\n");
    printf("------------------------------------------------O\n");

}
/*-----------------------------------------------------*/

/*
initRandom2DTable : fill randomly the 2D table
@param map : a void map
@return void 
*/
void initRandom2DTable(MAP **map){
    srand(time(NULL));
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            map[i][j].etat=0;
            int r = rand()%6+1;
            switch(r){
                case 1:
                    map[i][j].type=SOL;
                    map[i][j].degree=0;
                    break;
                case 2:
                    map[i][j].type=ARBRE;
                    map[i][j].degree=4;
                    break;
                case 3:
                    map[i][j].type=FEUILLE;
                    map[i][j].degree=2;
                    break;
                case 4:
                    map[i][j].type=ROCHE;
                    map[i][j].degree=5;
                    break;
                case 5:
                    map[i][j].type=HERBE;
                    map[i][j].degree=3;
                    break;

                case 6:
                    map[i][j].type=EAU;
                    map[i][j].degree=0;
                    break;
            }
    
        }
    }

}

/*
free2DTable : free correctly a dynamic 2D table
@param map : a map
@return void 
*/
void free2DTable(MAP **map){
    for(int i=0;i<longueur;i++){
        free(map[i]);
    }
    free(map);
}

/*
searchNeighbourhood : travel the flames table and search in a 3x3 zone to set Fire
@param map : the current map
@param flamesTable : store the different positions of the flames
@return number of flames 
*/
int searchNeighbourhood(MAP** map, FLAMES* flamesTable){
    FLAMES* tempTab = createFlamesTable();
    int indexTab=0;
    int tempX;
    int tempY;
    int indexEndTab = endOfTab(flamesTable);
    int cursor = 0;
    while(flamesTable[cursor].exit!=-1){
        tempX = flamesTable[cursor].x;
        tempY = flamesTable[cursor].y;
        for(int i = -1; i<2; i++){
            for(int j = -1; j<2 ;j++){
                if(flamesTable[cursor].exit==-1){
                        flamesTable[cursor+1].exit=0;
                        goto endOfFor;
                    }
                if(isInBound(tempX +i, tempY +j) && map[tempX + i][tempY + j].etat != 1){
                    if(setFire(tempX + i,tempY + j,map)){
                        tempTab[indexTab].x = tempX + i;
                        tempTab[indexTab].y = tempY + j; 
                        indexTab++;
                    }
                }
            }
        }
        cursor++;

    }
    endOfFor: 

    tempTab[indexTab].exit = -1;
    flamesTable[indexEndTab].exit=0;

    copyTab(tempTab, flamesTable);
    editMap(map);
    return indexTab;
}
void copyTab(FLAMES *tempTab, FLAMES *newVersionTab){
    int index = 0;
    while(tempTab[index].exit!=-1){//Le probleme est sque je vais trop loin, while exit !=-1
        newVersionTab[index].x=tempTab[index].x;
        newVersionTab[index].y=tempTab[index].y;
        //newVersionTab[index].exit=-1;
        index++;
    }
    newVersionTab[index].exit = -1;
}
void showTab(FLAMES *tableau){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        printf("Coordonnées du tableau n°%d :%d-%d\n",index,tableau[index].x,tableau[index].y);
    }
}
void cutTab(FLAMES *tab, int cutIndex){
    int index = 0;
    for(index; index<cutIndex; index++){
        tab[index].x=tab[index].x;
        tab[index].x=tab[index].y;
    }
    tab[index].exit = -1;
    
}
int endOfTab(FLAMES *tableau){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        if(tableau[index].exit==-1){
            return index;
        }
    }
}

void nextMap(MAP **initialMap, MAP **emptyMap){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            emptyMap[i][j].type = initialMap[i][j].type;
            emptyMap[i][j].etat = initialMap[i][j].etat;
            emptyMap[i][j].degree = initialMap[i][j].degree;
        }
    }
}



void typeToAsh(int x, int y, MAP **infoMap){
    if(infoMap[x][y].degree == 1){
         infoMap[x][y].type=CENDRES;

    } else if(infoMap[x][y].degree == 0){
        
        if(infoMap[x][y].type == SOL || infoMap[x][y].type == EAU){
            return;
        }
        
         infoMap[x][y].type=CENDRES_ETEINTES;
         infoMap[x][y].etat=0;

    }
    
}

void decrementDegree(int x, int y, MAP **infoMap){
    int actualDegree = infoMap[x][y].degree;
    actualDegree = actualDegree - 1;
    infoMap[x][y].degree = actualDegree;
    
}

bool setFire(int x, int y, MAP **map){
    bool isInFire = false;
    if (map[x][y].degree > 0){
        map[x][y].etat = 1;
        isInFire = true;
    } 
    else { 
        map[x][y].etat = 0;
    }
    return isInFire;
}
void editMap(MAP **infoMap){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            if(infoMap[i][j].etat==1 && infoMap[i][j].degree>0){
                infoMap[i][j].degree--;
            }
            
            if(infoMap[i][j].degree == 1 && infoMap[i][j].etat==1){
                infoMap[i][j].type=CENDRES;
            }
            if(infoMap[i][j].degree == 0 && infoMap[i][j].etat==1){
                infoMap[i][j].type=CENDRES_ETEINTES;
                infoMap[i][j].etat=0;
            }
            
        }
    }
}
bool isFinished(MAP **currentMap, MAP **previousMap){
    bool state = false;
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            if(currentMap[i][j].degree!=previousMap[i][j].degree ){   
                return false;
            }
        }
    }
    return true;
}


