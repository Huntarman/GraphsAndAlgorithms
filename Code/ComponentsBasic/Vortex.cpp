//
// Created by micha on 23.05.2023.
//

#include "Vortex.h"
#include "iostream"

Vortex::Vortex(int index) {
    this->index = index;
    edgeAmountVortex = 0;
    edges = (Edge *) malloc(0 * sizeof(Edge));
    edgesMatrix = (Edge *) malloc(0 * sizeof(Edge));
}

void Vortex::addEdge(Edge edge) {
    edgeAmountVortex++;
    edges = (Edge *) realloc(edges, edgeAmountVortex * sizeof(Edge));
    edges[edgeAmountVortex-1] = edge;
}
void Vortex::printEdges() {
    std::cout<<"V:"<<index<<"[";
    for (int i = 0; i<edgeAmountVortex; i++){
        if(i != edgeAmountVortex-1) std::cout<<edges[i].destination<<":"<<edges[i].capacity<<", ";
        else std::cout<<edges[i].destination<<":"<<edges[i].capacity;
    }
    std::cout<<"]";
}

void Vortex::deleteEdges() {
    free(edges);
    edges = (Edge*) malloc(0);
    edgeAmountVortex = 0;
}

void Vortex::createEdgeMatrix(int size, Edge nullEdge) {
    delete[] edgesMatrix;
    edgesMatrix = (Edge*) malloc( size * sizeof(Edge));

    for (int i = 0; i < size; i++) {
        edgesMatrix[i] = nullEdge;
    }
    for (int i = 0; i < edgeAmountVortex; i++) {
        Edge pom = edges[i];
        edgesMatrix[pom.destination] = pom;
    }
}

long Vortex::getEdgeAmount() {
    return edgeAmountVortex;
}
