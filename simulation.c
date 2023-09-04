
#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 
#include "simulation.h"
#include "ext_glob.h"


CARTE** creationMatrice(){
    
    CARTE **foret = (CARTE**)malloc(sizeof(CARTE)*longueur);

    for (int i = 0;i<longueur;i++){
        foret[i] = (CARTE*)malloc(largeur*sizeof(CARTE));
    }

  
  printf("%d",foret);
  return foret;
   
}

void afficheMatrice(CARTE **map){
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
            printf(" %c",map[i][j].type);
        }
        printf("\n");
    }
}

void remplirMatriceRandom(CARTE **map){
    srand(time(NULL));
    //printf("TETETTETE %c TETETETE", SOL);
    for (int i = 0; i<longueur; i++){
        for (int j = 0; j<largeur;j++){
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




void matriceManu (){




}

