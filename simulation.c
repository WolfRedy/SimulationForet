
#include <stdio.h>
#include <time.h> 
#include <stdbool.h>
#include <stdlib.h> 
#include "simulation.h"
#include "ext_glob.h"
#include "pile.h"
#include <assert.h>



CARTE** creationMatrice(){
    
    CARTE **foret = (CARTE**)malloc(sizeof(CARTE)*longueur);
    assert( foret != NULL );
    for (int i = 0;i<longueur;i++){
        foret[i] = (CARTE*)malloc(largeur*sizeof(CARTE));
    }
  return foret; 
}
LOCFEU* creationTableauFeu(){
    LOCFEU *tableau = (LOCFEU*)malloc(sizeof(LOCFEU)*(longueur*largeur)+1);
    return tableau;
}

void affichage_de_la_carte(CARTE **map){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            //ELEMENTS currentElement = map[i][j].type;
            if(map[i][j].etat==1){
                printf("\033[0;31m"); 
            }else{
                editColor(map[i][j].type);
            }
            

            printf(" %c",map[i][j].type);
        }
        printf("\033[0m");
        printf("\n");
    }
}
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

void remplir_la_carte_manuel(CARTE **map) {
    //La carte au départ n'est que du sol dans le mode manuel:
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
    printf("La création de la carte est finie.\n");
    printf("------------------------------------------------O\n");

}
/*-----------------------------------------------------*/
void remplirMatriceRandom(CARTE **map){
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

                case 6:
                    map[i][j].type=EAU;
                    map[i][j].degree=0;
                    break;
                /*case 7:
                    map[i][j].type=CENDRES;
                    map[i][j].degree=1;
                    break;
                case 8:
                    map[i][j].type=CENDRES_ETEINTES;
                    map[i][j].degree=0;
                    break;*/
    }
    
        }
    }

}
void destructionMatrice(CARTE **map){
    for(int i=0;i<longueur;i++){
        free(map[i]);
    }
    free(map);
}

int chercheVoisinage(CARTE** carte, LOCFEU* tableau){
    LOCFEU* tempTab = creationTableauFeu();
    int indexTab=0;
    int tempX;
    int tempY;
    int indexEndTab = endOfTab(tableau);
    int cursor = 0;
    while(tableau[cursor].exit!=-1){
        tempX = tableau[cursor].x;
        tempY = tableau[cursor].y;
        for(int i = -1; i<2; i++){
            for(int j = -1; j<2 ;j++){
                if(tableau[cursor].exit==-1){
                        tableau[cursor+1].exit=0;
                        goto endOfFor;
                    }
                //if(isInBound(tempX +i, tempY +j) && carte[tempX + i][tempY + j].etat != 1 && carte[tempX + i][tempY + j].type != SOL && carte[tempX + i][tempY + j].type != EAU ){
                if(isInBound(tempX +i, tempY +j) && carte[tempX + i][tempY + j].etat != 1){
                    if(setFire(tempX + i,tempY + j,carte)){
                        tempTab[indexTab].x = tempX + i;
                        tempTab[indexTab].y = tempY + j; //faire en sorte que ça ajoute a la suite de l'autre tableau
                        indexTab++;
                    }
                    //typeToAsh(tempX + i,tempY + j,carte);
                    //decrementDegree(tempX + i,tempY + j,carte);
                    
                    //carte[tempX + i][tempY + j].etat = 1;
                    //carte[tempX + i][tempY + j].type = FEU;
                    
                }
            }
        }
        cursor++;

    }
    endOfFor: 

    tempTab[indexTab].exit = -1;
    tableau[indexEndTab].exit=0;
    copyTab(tempTab, tableau);
    //tableau[indexTab + 1].exit=0;
    editMap(carte);
    return indexTab;
}
void copyTab(LOCFEU *tempTab, LOCFEU *newVersionTab){
    int index = 0;
    while(tempTab[index].exit!=-1){//Le probleme est sque je vais trop loin, while exit !=-1
        newVersionTab[index].x=tempTab[index].x;
        newVersionTab[index].y=tempTab[index].y;
        //newVersionTab[index].exit=-1;
        index++;
    }
    newVersionTab[index].exit = -1;
}
void showTab(LOCFEU *tableau){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        printf("Coordonnées du tableau n°%d :%d-%d\n",index,tableau[index].x,tableau[index].y);
    }
}
void cutTab(LOCFEU *tab, int cutIndex){
    int index = 0;
    for(index; index<cutIndex; index++){
        tab[index].x=tab[index].x;
        tab[index].x=tab[index].y;
    }
    tab[index].exit = -1;
    
}
int endOfTab(LOCFEU *tableau){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        if(tableau[index].exit==-1){
            return index;
        }
    }
}

void nextMap(CARTE **initialMap, CARTE **emptyMap){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            emptyMap[i][j].type = initialMap[i][j].type;
            emptyMap[i][j].etat = initialMap[i][j].etat;
            emptyMap[i][j].degree = initialMap[i][j].degree;
        }
    }
}

bool isInBound(int x, int y){
    if(x>=longueur || y>=largeur || x<0 || y<0){
        return false;
    }
    return true;
}

void typeToAsh(int x, int y, CARTE **infoMap){
    //printf("%d",infoMap[x][y].degree);
    if(infoMap[x][y].degree == 1){
         infoMap[x][y].type=CENDRES;

    } else if(infoMap[x][y].degree == 0 /*&& infoMap[x][y].type != SOL && infoMap[x][y].type != EAU*/){
        
        if(infoMap[x][y].type == SOL || infoMap[x][y].type == EAU){
            return;
        }
        
         infoMap[x][y].type=CENDRES_ETEINTES;
    }
    
}

void decrementDegree(int x, int y, CARTE **infoMap){
    int actualDegree = infoMap[x][y].degree;
    actualDegree = actualDegree - 1;
    infoMap[x][y].degree = actualDegree;
    printf("%d", actualDegree);
    
}

bool setFire(int x, int y, CARTE **map){
    bool isInFire = false;
    if (map[x][y].degree > 0){
        map[x][y].etat = 1;
        //decrementDegree(x,y,map);
        //typeToAsh(x,y,map);
        isInFire = true;
    } 
    else { // if degree == 0 && etat 1
        map[x][y].etat = 0;
    }
    
    //typeToAsh(x,y,map);
    return isInFire;
}
void editMap(CARTE **infoMap){
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
            }
            
        }
    }
}


