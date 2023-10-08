#include "simulation.h"
#include "menu.h"
#include "pile.h"
#define _MAIN_
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#include "ext_glob.h"
#include <stdio.h>
#include <stdlib.h>




int main()
{
    int longueur = 0;
    int largeur = 0;
    int nombreIteration;
    int nbFlames;

    printf("choisisez le nombre d'iterations \n");
    scanf("%d",&nombreIteration);
    
    affichageMenu();
    choixTaille();

    ELEMENTS laValeurModif;
    CARTE** carteInitial = creationMatrice();
    remplirMatriceRandom(carteInitial);
    affichage_de_la_carte(carteInitial);

    LOCFEU* coordFeu = creationTableauFeu();
    int x,y;
    printf("Coordonnée x du départ de feu");
    scanf("%d",&x);//optimiser ça plus tard
    printf("Coordonnée y du départ de feu");
    scanf("%d",&y);
    coordFeu->x=x;
    coordFeu->y=y;
    coordFeu[1].exit=-1;
    nbFlames = chercheVoisinage(carteInitial,coordFeu);
    //chercheVoisinage(pileSimulation->adresseCarte,pileSimulation->tabCoordFeu);
    //affichage_de_la_carte(pileSimulation->adresseCarte);
    affichage_de_la_carte(carteInitial);
    pile* pileSimulation = NULL;
    push(&pileSimulation,carteInitial, coordFeu, nbFlames);
    //showTab(coordFeu);
    //showTab(pileSimulation->tabCoordFeu);
    view(pileSimulation);
    
    printf("STOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP");
    CARTE** carteSuivante = NULL;
    LOCFEU* tableauSuivant = NULL;
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
            //printf("%x",&pileSimulation);
            //printf("%x",pileSimulation->adresseCarte);
            //destructionMatrice(pileSimulation->adresseCarte);
            pop(&pileSimulation);
            //lui donner l'adresse du premier element de la pille
            printf("CA A MARCHE");
            //On doit redonner une adresse a test2
            view(pileSimulation);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i--;
        }else if(choix =='2'){
            printf("\nVous avez choisi de modifier une valeur\n");
            
        }else if(choix == '3'){
            
            printf("\nVous avez choisi d'avancer\n");
            printf("%x",&pileSimulation);
            
            carteSuivante = creationMatrice();
            nextMap(pileSimulation->adresseCarte,carteSuivante);
            tableauSuivant = creationTableauFeu();
            copyTab(pileSimulation->tabCoordFeu, tableauSuivant);

            nbFlames = chercheVoisinage(carteSuivante,tableauSuivant);
            //remplirMatriceRandom(carteSuivante);
            push(&pileSimulation,carteSuivante, tableauSuivant, nbFlames);
            //view(pileSimulation);
            affichage_de_la_carte(pileSimulation->adresseCarte);
            i++;
            
        }
        
    }
  
    destructionMatrice(carteInitial);
    return 0;
}
