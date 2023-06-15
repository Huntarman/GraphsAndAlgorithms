//
// Created by micha on 24.05.2023.
//

#include "PriorityQueue.h"
#include "iostream"

PriorityQueue::PriorityQueue() {
    this->heap = (Edge*) malloc(0);
    this->size = 0;
}

Edge PriorityQueue::top() {
    return heap[0];
}

void PriorityQueue::push(Edge edge) {
    int i, j;
    i = size; size++;
    heap = (Edge*) realloc(heap, size * sizeof(Edge));
    j = (i-1)/2;
    while (i != 0 && (heap[j].capacity > edge.capacity)){
        heap[i] = heap[j];
        i = j;
        j = (i-1)/2;
    }
    heap[i] = edge;
}

void PriorityQueue::pop() {
    int i,j;

    if (size != 0){
        size--;
        Edge pom = heap[size];
        i = 0;
        j = 1;
        while(j < size){
            if((j + 1)< size && (heap[j+1].capacity < heap[j].capacity)) j++;
            if(pom.capacity <= heap[j].capacity) break;
            heap[i] = heap[j];
            i = j;
            j = j*2 + 1;
        }
        heap[i] = pom;
        heap = (Edge*) realloc(heap, size * sizeof(Edge));
    }
}

void PriorityQueue::printQueue(){
    for(int i = 0; i < size; i++){
        std::cout<<heap[i].source<<"|"<<heap[i].destination<<"|"<<heap[i].capacity<<"\n";
    }
    std::cout<<"\n";
}

VortexPath PriorityQueue::topSPP() {
    return SPPnext[0];
}

void PriorityQueue::pushSPP(VortexPath path) {
    int i, j;
    i = sizeSPP; sizeSPP++;
    SPPnext = (VortexPath*) realloc(SPPnext, sizeSPP * sizeof(VortexPath));
    j = (i-1)/2;
    while (i != 0 && (SPPnext[j].pathWeight > path.pathWeight)){
        SPPnext[i] = SPPnext[j];
        i = j;
        j = (i-1)/2;
    }
    SPPnext[i] = path;
}

void PriorityQueue::popSPP() {
    int i,j;

    if (sizeSPP != 0){
        sizeSPP--;
        VortexPath pom = SPPnext[sizeSPP];
        i = 0;
        j = 1;
        while(j < sizeSPP){
            if((j + 1)< sizeSPP && (SPPnext[j+1].pathWeight < SPPnext[j].pathWeight)) j++;
            if(pom.pathWeight <= SPPnext[j].pathWeight) break;
            SPPnext[i] = SPPnext[j];
            i = j;
            j = j*2 + 1;
        }
        SPPnext[i] = pom;
        SPPnext = (VortexPath*) realloc(SPPnext, sizeSPP * sizeof(VortexPath));
    }
}

PriorityQueue::PriorityQueue(bool spp) {
    this->SPPnext = (VortexPath*) malloc(0);
    this->sizeSPP = 0;
}

void PriorityQueue::printQueueSPP() {

    for(int i = 0; i < sizeSPP; i++){
        std::cout<<SPPnext[i].pathWeight<<"\n";
    }
    std::cout<<"\n";
}
