// Help with https://rosettacode.org/wiki/Dijkstra%27s_algorithm#C and https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include "../core/ext_glob.h"
#include "dijkstra.h"
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }


void launchDijkstra(MAP** map) {
    MAP** dijkstraMap = create2DTable();
    nextMap(map, dijkstraMap);
    int positionDestinationX = 0;
    int positionDestinationY = 0;
    printf("--> Coordonnée x d'arrivé du feu\n");
    CLEAR_STDIN;
    scanf("%d",&positionDestinationX);
    printf("--> Coordonnée y d'arrivé du feu\n");
    CLEAR_STDIN;
    scanf("%d",&positionDestinationY); 

    while(!isInBound(positionDestinationX,positionDestinationY)){
        printf("### Error - Out Of Bound ###\n");
        printf("--> Coordonnée x d'arrivé du feu\n");
        CLEAR_STDIN;
        scanf("%d",&positionDestinationX);
        printf("--> Coordonnée y d'arrivé du feu\n");
        CLEAR_STDIN;
        scanf("%d",&positionDestinationY);  
    }
    Vertex source = createVertex(positionFlameX, positionFlameY);
    Vertex destination = createVertex(positionDestinationX, positionDestinationY);
    dijkstraMap[positionFlameX][positionFlameY].type = 'F';
    dijkstraMap[positionFlameX][positionFlameY].etat = 1;
    dijkstraMap[positionDestinationX][positionDestinationY].type = 'F';
    dijkstraMap[positionDestinationX][positionDestinationY].etat = -1;
    printf("--- Carte Initial ---\n");
    affichage_de_la_carte(dijkstraMap);
    dijkstra(dijkstraMap, source, destination);
    free2DTable(dijkstraMap);
}
/*
createVertex : create a Vertex with x and y coordinates
@param int x,y
@return Vertex
*/
Vertex createVertex(int x, int y) {
    Vertex Vertex;
    Vertex.x = x;
    Vertex.y = y;
    
    return Vertex;
}
/*
initToZero : initialize each element in distance2D to INT_MAX(inf) and each element of visited2D to 0
@param int** distance, int** visited
@param Vertex source : departure point
@return void
*/
void initToZero(int** distance, int** visited, Vertex source){
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            distance[i][j] = INT_MAX;
            visited[i][j] = 0;
        }
    }
    distance[source.x][source.y] = 0;
}

/*
isReached : initialize each element in distance2D to INT_MAX(inf) and each element of visited2D to 0
@param int** distance
@param MAP** map : the forest 2D table
@param Vertex source : departure point
@param Vertex destination : destination point
@return void
*/
void isReached(MAP** map, Vertex source, Vertex destination, int** distance){
    if (distance[destination.x][destination.y] != INT_MAX){
        printf("Distance de %d éléments entre [%d,%d] et [%d,%d] !\n",distance[destination.x][destination.y], source.x, source.y, destination.x, destination.y);
    }
    else{
        if(map[destination.x][destination.y].degree==0){
             printf("L'élément situé à [%d,%d] est non-inflammables\n",destination.x, destination.y);
        }else{
            printf("Impossible, aucun chemin possible entre [%d,%d] et [%d,%d]\n",source.x, source.y, destination.x, destination.y);
        }
        
    }
}

/*
createVisited : create a 2D int table
@param 
@return int**
*/
int** createInt2DTable(){
    int** int2DTable = ( int **) malloc(longueur * sizeof( int*));
    assert( int2DTable != NULL );
    for(int index = 0;index < longueur;index++) {
        int2DTable[index] = (int*) malloc(largeur * sizeof(int));
        assert( int2DTable[index] != NULL );
    }
    return int2DTable;
}

/*
dijkstra : main part of the algorithm of dijkstra
@param MAP** map, Vertex source, Vertex destination
@return void
*/
void dijkstra(MAP** map, Vertex source, Vertex destination) {
    /*a modified version of Dijkstra's algorithm, 
    exploring a 2D grid represented by the map array.*/
    int** visited = createInt2DTable();
    int** distance = createInt2DTable();
    initToZero(distance, visited,source);

    for (int index = 0; index < longueur * largeur - 1; index++){
        Vertex myVertex;
        bool carry = false;
        int smartDistance = INT_MAX;
        for (int i = 0; i < longueur; i++) {
            for (int j = 0; j < largeur; j++) {
                if (distance[i][j] < smartDistance && visited[i][j] == 0) {
                    myVertex = createVertex(i,j);
                    smartDistance = distance[i][j];
                }
            }
        }
        visited[myVertex.x][myVertex.y] = 1;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (isInBound(myVertex.x + i, myVertex.y + j) && distance[myVertex.x][myVertex.y] + 1 < distance[myVertex.x + i][myVertex.y + j] && visited[myVertex.x + i][myVertex.y + j] == 0 && distance[myVertex.x][myVertex.y] != INT_MAX ) {
                    MAP *adjacentVertex = &map[myVertex.x + i][myVertex.y + j];
                    if (adjacentVertex->degree > 0){
                        map[myVertex.x + i][myVertex.y + j].type = 'F';
                        distance[myVertex.x + i][myVertex.y + j] = distance[myVertex.x][myVertex.y] + 1;
                    }
                }
            }
        }
    }
    printf("--- Carte après dijkstra ---\n");
    affichage_de_la_carte(map);
    isReached(map, source, destination, distance);
}
