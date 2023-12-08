#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#include "ext_glob.h"
#include "dijkstra.h"

void launchDijkstra(MAP** map) {
    MAP** dijkstraMap = create2DTable();
    nextMap(map, dijkstraMap);
    int positionDestinationX = 0;
    int positionDestinationY = 0;
    printf("Merci de rentrer votre point de destination au format: <x y> \nExemple: 2 5\n");
    scanf("%d %d",&positionDestinationX,&positionDestinationY);
    Vertex source = createVertex(positionFlameX, positionFlameY);
    Vertex destination = createVertex(positionDestinationX, positionDestinationY);
    dijkstraMap[positionFlameX][positionFlameY].type = 'F';
    dijkstraMap[positionFlameX][positionFlameY].etat = 1;
    dijkstraMap[positionDestinationX][positionDestinationY].type = 'F';
    dijkstraMap[positionDestinationX][positionDestinationY].etat = -1;
    
    affichage_de_la_carte(dijkstraMap);
    dijkstra(dijkstraMap, source, destination);
   
    free2DTable(dijkstraMap);
    return 0;
}

Vertex createVertex(int x, int y) {
    Vertex Vertex;
    Vertex.x = x;
    Vertex.y = y;
    return Vertex;
}
void initToZero(int** distance, int** visited, Vertex source){
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            distance[i][j] = INT_MAX;
            visited[i][j] = 0;
        }
    }
    distance[source.x][source.y] = 0;
}

void isReached(Vertex source, Vertex destination, int** distance){
    if (distance[destination.x][destination.y] != INT_MAX){
        printf("Distance de %d éléments entre [%d,%d] et [%d,%d] !\n",distance[destination.x][destination.y], source.x, source.y, destination.x, destination.y);
    }
    else{
        printf("Impossible, aucun chemin possible entre [%d,%d] et [%d,%d]\n",source.x, source.y, destination.x, destination.y);
    }
}
void dijkstra(MAP** map, Vertex source, Vertex destination) {

    int** visited = ( int **) malloc(longueur * sizeof( int*));
    assert( visited != NULL );
    for(int index = 0;index < longueur;index++) {
        visited[index] = (int*) malloc(largeur * sizeof(int));
        assert( visited[index] != NULL );
    }

    int** distance = ( int **) malloc(longueur * sizeof( int*));
    assert( distance != NULL );
    for(int index = 0;index < longueur;index++) {
        distance[index] = (int*) malloc(largeur * sizeof(int));
        assert( distance[index] != NULL );
    }

    initToZero(distance, visited,source);

    for (int index = 0; index < longueur * largeur - 1; index++){
        int smartDistance = INT_MAX;
        Vertex myVertex;
        for (int i = 0; i < longueur; i++) {
            for (int j = 0; j < largeur; j++) {
                if (visited[i][j] == 0 && distance[i][j] < smartDistance) {
                    smartDistance = distance[i][j];
                    myVertex = createVertex(i, j);
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
    affichage_de_la_carte(map);
    isReached(source, destination, distance);
}
