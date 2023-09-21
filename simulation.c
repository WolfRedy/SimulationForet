
#include <stdio.h>
#include <time.h> 
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
            printf(" %c",map[i][j].type);
        }
        printf("\n");
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
    //printf("TETETTETE %c TETETETE", SOL);
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            map[i][j].etat=0;
            int r = rand()%8+1;
            switch(r){
                case 1:
                    map[i][j].type=SOL;
                    break;
                case 2:
                    map[i][j].type=ARBRE;

                    break;
                case 3:
                    map[i][j].type=FEUILLE;

                    break;
                case 4:
                    map[i][j].type=ROCHE;

                    break;
                case 5:
                    map[i][j].type=HERBE;

                case 6:
                    map[i][j].type=EAU;
                    break;
                case 7:
                    map[i][j].type=CENDRES;
                    break;
                case 8:
                    map[i][j].type=CENDRES_ETEINTES;
                    break;
    }
    
        }
    }

    //printf("\n %d \n",map[1][1].degre);
    //printf("\n %c \n",map[1][1].type);
}
void destructionMatrice(CARTE **map){
    //printf("%d",map);
    for(int i=0;i<longueur;i++){
        free(map[i]);
    }
    free(map);
    //printf("test");
}

void chercheVoisinage(CARTE** carte, LOCFEU* tableau){
    
    LOCFEU* tempTab = creationTableauFeu();
    
    int indexTab=0;
    int tempX;
    int tempY;
    printf("%d\n",tableau[indexTab].exit);
    while(tableau[indexTab].exit!=-1){
        printf("A");
        tempX = tableau[indexTab].x;
        tempY = tableau[indexTab].y;
        for(int i = -1; i<2; i++){
            for(int j = -1; j<2 ;j++){
                printf("%d\n",carte[tempX + i][tempY + j].etat);
                if(carte[tempX + i][tempY + j].etat != -1 && (i!=0 || j!=0) && carte[tempX + i][tempY + j].type != SOL && carte[tempX + i][tempY + j].type != EAU){
                    //printf("BBB");
                    tempTab[indexTab].x = tempX + i;
                    tempTab[indexTab].y = tempY + j;
                    carte[tempX + i][tempY + j].etat = 1;
                    carte[tempX + i][tempY + j].type = FEU;
                }
            }
        }
        //printf("%d",indexTab);
        indexTab++;
    }
    copyTab(tempTab, tableau);
    //tableau[indexTab + 1].exit=0;
    

}
void copyTab(LOCFEU *tempTab, LOCFEU *newVersionTab){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        newVersionTab[index].x=tempTab[index].x;
        newVersionTab[index].y=tempTab[index].y;
    }
    newVersionTab[index].exit = -1;
}
void showTab(LOCFEU *tableau){
    int index = 0;
    for(index; index<(longueur*largeur)+1;index++){
        printf("Coordonnées du tableau n°%d :%d-%d\n",index,tableau[index].x,tableau[index].y);
    }
}



