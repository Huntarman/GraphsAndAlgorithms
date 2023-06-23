//
// Created by micha on 24.05.2023.
//

#ifndef SDIZO_PROJECT_2_PRIORITYQUEUE_H
#define SDIZO_PROJECT_2_PRIORITYQUEUE_H


#include "../ComponentsBasic/Edge.h"
#include "../ComponentsDirectedGraph/VortexPath.h"

class PriorityQueue {
public:
    Edge* heap;
    VortexPath* SPPnext;
    int size;
    int sizeSPP;
public:
    PriorityQueue();
    explicit PriorityQueue(bool spp);
    Edge top();
    VortexPath topSPP();
    void push(Edge edge);
    void pushSPP(VortexPath path);
    void pop();
    void popSPP();
    void printQueueSPP();
    void printQueue();
};


#endif //SDIZO_PROJECT_2_PRIORITYQUEUE_H
