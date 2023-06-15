//
// Created by micha on 27.05.2023.
//

#ifndef SDIZO_PROJECT_2_DIRECTEDGRAPH_H
#define SDIZO_PROJECT_2_DIRECTEDGRAPH_H


#include "../ComponentsBasic/Vortex.h"
#include "../ComponentsBasic/Edge.h"
#include "../ComponentsDirectedGraph/VortexPath.h"

class DirectedGraph {
public:
    Vortex* vortices;
    Edge* edges;
    VortexPath* SPP;
    int next_ID;
    int edgeAmount;
    int edgeCap;
    bool SPPcreated = false;
    Edge nullEdge = Edge(0,0,0);
    Edge* IncidenceMatrix;

public:
    DirectedGraph();
    void addEdge(Edge edge);
    void addMultipleEdges(double percentage);
    void addVortex();
    void addMultipleVortices(int n);
    void printGraphList();
    void printGraphMatrix();
    void SPPDijkstra();
    void SPPDijkstraMatrix();
    void SPPDijkstra(int start);
    void SPPDijkstraMatrix(int start);
    void SPPBelFord();
    void SPPBelFordMatrix();
    void SPPBelFord(int start);
    void SPPBelFordMatrix(int start);
    void printSPPList();
    void createMatrix();
    void printSPPcost();

private:
    void printMatrix(Edge* listVor, int n);
    void unvisit();
};


#endif //SDIZO_PROJECT_2_DIRECTEDGRAPH_H
