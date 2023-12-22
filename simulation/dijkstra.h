#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#include "simulation.h"
#define NAME_LEN 25
typedef struct {
    int x; 
    int y;
    char vertexName[NAME_LEN];
}Vertex;
void launchDijkstra(MAP** map);
Vertex createVertex(int x, int y);
void initToZero(int** distance, int** visited, Vertex source);
int** createInt2DTable();
void dijkstra(MAP** map, Vertex source, Vertex destination) ;
void isReached(MAP** map, Vertex source, Vertex destination, int** distance);
#endif