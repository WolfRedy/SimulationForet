#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#include "simulation.h"
typedef struct {
    int x; 
    int y;
}Vertex;
void launchDijkstra(MAP** map);
Vertex createVertex(int x, int y);
void initToZero(int** distance, int** visited, Vertex source);
int** createVisited();
int** createDistance();
void dijkstra(MAP** map, Vertex source, Vertex destination) ;
void isReached(Vertex source, Vertex destination, int** distance);


#endif