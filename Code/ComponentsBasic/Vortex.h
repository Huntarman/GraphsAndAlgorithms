//
// Created by micha on 23.05.2023.
//

#ifndef SDIZO_PROJECT_2_VORTEX_H
#define SDIZO_PROJECT_2_VORTEX_H


#include "Edge.h"

class Vortex {
public:
    int index;
    Edge* edges;
    Edge* edgesMatrix;
    long edgeAmountVortex;
    bool visited = false;
public:
    Vortex(int index);
    void addEdge(Edge edge);
    void deleteEdges();
    void printEdges();
    long getEdgeAmount();
};


#endif //SDIZO_PROJECT_2_VORTEX_H
