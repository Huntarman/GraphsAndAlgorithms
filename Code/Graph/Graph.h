//
// Created by micha on 23.05.2023.
//

#ifndef SDIZO_PROJECT_2_GRAPH_H
#define SDIZO_PROJECT_2_GRAPH_H


#include "../ComponentsBasic/Vortex.h"
#include "../ComponentsBasic/Edge.h"

class Graph {
public:
    int next_ID;
    int edgeAmount;
    int edgeCap = 0;
    Vortex* vortices;
    Edge* edges;
    Vortex* MST;
    bool MSTcreated = false;
    Edge nullEdge = Edge(0,0,-1);
    int mst_weight=0;

public:
    Graph();
    void addVortex();
    void addMultipleVortices(int amount);
    void addEdge(Edge edge);
    void addMultipleEdges(double percentage);
    void printGraphList();
    void printMSTList();
    void printGraphMatrix();
    void printMSTMatrix();
    void mstKruskal();
    void mstKruskalMatrix();
    void mstPrim();
    void mstPrimMatrix();
    void mstPrim(int start);
    void mstPrimMatrix(int start);
    void createMatrix();

private:
    bool hasCycle(Edge* edges, int edgeCount);
    void printMatrix(Vortex* listVor, int n);
    void unvisit();
};


#endif //SDIZO_PROJECT_2_GRAPH_H
