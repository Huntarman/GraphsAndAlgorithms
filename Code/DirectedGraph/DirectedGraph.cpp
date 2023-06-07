//
// Created by micha on 27.05.2023.
//

#include "DirectedGraph.h"
#include "iostream"
#include "../ComponentsGraph/PriorityQueue.h"
#include "random"

std::random_device rand_dev1;
std::mt19937 generator1(rand_dev1());
std::uniform_int_distribution<int> distribution1(1, 100);

DirectedGraph::DirectedGraph(){
    this->edges = (Edge*) malloc(0);
    this->vortices = (Vortex*) malloc(0);
    this->SPP = (VortexPath*) malloc(0);
    this->next_ID = 0;
    this->edgeAmount = 0;
    this->edgeCap = 0;
}
void DirectedGraph::addEdge(Edge edge) {
    if (edge.source > next_ID-1 || edge.destination > next_ID-1){
        std::cout<<"Can't add edge!\n";
        return;
    }
    edgeAmount++;
    edges = (Edge*) realloc(edges, edgeAmount*sizeof(Edge));
    edges[edgeAmount-1] = edge;
    vortices[edge.source].addEdge(edge);
}

void DirectedGraph::addMultipleEdges(double percentage) {
    bool availMatrix[next_ID][next_ID];
    for (int i = 0; i < next_ID;i++){
        for (int j = 0; j<next_ID;j++){
            if (j != i ) availMatrix[i][j] = true;
            else availMatrix[i][j] = false;
        }
    }

    if (percentage >= 1.0){
        for (int i = 0; i<next_ID;i++){
            for (int j = 0; j < next_ID; j++) {
                if (availMatrix[i][j]) {
                    addEdge(Edge(i, j, distribution1(generator1)));
                    availMatrix[i][j] = false;
                }
            }
        }
        return;
    }
    //Tutaj algorytm upewnia sie ze wszystkie wierzcholki beda mialy przynajmniej jedno polaczenie
    for (int i = 0; i<next_ID;i++){
        addEdge(Edge(i, (i+1) % next_ID, distribution1(generator1)));
        availMatrix[i][(i+1)%next_ID] = false;
    }
    //tworzenie krawedzi laczace 2 losowe wierzcholki
    while(percentage >= (double)edgeAmount/(double)edgeCap){

        //jesli jz wypelnilismy wiekszosc mozliwych krawedzi, algorytm zmniejsza swoja losowosc, aby nie utknac
        if((double)edgeAmount/(double)edgeCap > 0.95){
            int i = next_ID-1;
            while(percentage >= (double)edgeAmount/(double)edgeCap){
                for (int j = 0; j < next_ID; j++) {
                    if (availMatrix[i][j]){
                        addEdge(Edge(i,j,distribution1(generator1)));
                        availMatrix[i][j] = false;
                    }
                }
                i--;
            }
            continue;
        }

        int x = distribution1(generator1) % next_ID;
        int y = distribution1(generator1) % next_ID;
        if (availMatrix[x][y]){
            addEdge(Edge(x,y,distribution1(generator1)));
            availMatrix[x][y] = false;
        }

    }
}

void DirectedGraph::addVortex() {
    edgeCap += next_ID*2;
    next_ID++;
    vortices = (Vortex*) realloc(vortices, next_ID * sizeof(Vortex));
    vortices[next_ID-1] = Vortex(next_ID-1);
}

void DirectedGraph::addMultipleVortices(int n) {
    for (int i = 0; i < n; i++) addVortex();
}

void DirectedGraph::printGraphList() {
    if (next_ID == 0){
        std::cout<<"Graph Empty\n";
        return;
    }
    for (int i = 0; i < next_ID; i++){
        vortices[i].printEdges();
        std::cout<<"\n";
    }
}

void DirectedGraph::printGraphMatrix() {
    if (next_ID == 0){
        std::cout<<"Graph Empty\n";
        return;
    }
    printMatrix(vortices,next_ID);
}

void DirectedGraph::printMatrix(Vortex *listVor, int n) {
    std::cout<<"\t";
    for (int i = 0; i < n; i++) {
        std::cout<<i<<"\t";
    }
    std::cout<<"\n";
    for (int i = 0; i < n; i++){
        std::cout<<i<<"\t";
        int list[n];
        for (int j = 0; j<n;j++){
            list[j] = 0;
        }
        for (int k = 0; k < listVor[i].getEdgeAmount(); k++) {
            list[listVor[i].edges[k].destination] = listVor[i].edges[k].capacity;
        }
        for (int j = 0; j < n; j++) {
            if (j == i) std::cout<<"-\t";
            else{
                std::cout<<list[j]<<"\t";
            }
        }
        std::cout<<"\n";
    }
}

void DirectedGraph::SPPDijkstra() {
    SPPDijkstra(distribution1(generator1)%next_ID);
}

void DirectedGraph::SPPDijkstra(int start) {
    delete[] SPP;
    SPPcreated = true;
    SPP = (VortexPath*) malloc( next_ID * sizeof(VortexPath));
    for (int i = 0; i < next_ID; i++){
        SPP[i] = VortexPath(i, INT32_MAX, -1);
    }
    SPP[start].parent = -2;
    SPP[start].pathWeight = 0;

    int idCurr = start;
    for (int i = 0; i < next_ID; i++){
        SPP[idCurr].visited = true;
        for (int j = 0; j < vortices[idCurr].getEdgeAmount(); j++){
            Edge pom = vortices[idCurr].edges[j];
            if((SPP[idCurr].pathWeight + pom.capacity) < SPP[pom.destination].pathWeight){
                SPP[pom.destination].pathWeight = SPP[idCurr].pathWeight + pom.capacity;
                SPP[pom.destination].parent = idCurr;
            }
        }
        PriorityQueue prioQu = PriorityQueue(false);

        for(int j = 0; j < next_ID; j++){
            if (SPP[j].visited) continue;
            if (SPP[j].parent == -1) continue;
            prioQu.pushSPP(SPP[j]);
        }
        idCurr = prioQu.topSPP().id;
    }
    unvisit();
}

void DirectedGraph::SPPBelFord() {
    SPPBelFord(distribution1(generator1)%next_ID);
}

void DirectedGraph::SPPBelFord(int start) {
    delete[] SPP;
    SPPcreated = true;
    SPP = (VortexPath*) malloc( next_ID * sizeof(VortexPath));
    for (int i = 0; i < next_ID; i++){
        SPP[i] = VortexPath(i, INT32_MAX, -1);
    }
    SPP[start].parent = -2;
    SPP[start].pathWeight = 0;

    for (int i = 0; i < next_ID - 1; i++){
        int changes = 0;
        for(int j = 0; j < next_ID; j++){

            if (SPP[j].parent == -1) continue;

            for (int k = 0; k < vortices[j].getEdgeAmount(); k++) {
                Edge pom = vortices[j].edges[k];
                if((SPP[j].pathWeight + pom.capacity) < SPP[pom.destination].pathWeight){
                    SPP[pom.destination].pathWeight = SPP[j].pathWeight + pom.capacity;
                    SPP[pom.destination].parent = j;
                    changes++;
                }
            }

        }
        if (changes == 0) return;
    }
}

void DirectedGraph::printSPPList() {
    if (!SPPcreated){
        std::cout<<"SPP not created yet!\n";
        return;
    }
    for (int i = 0; i < next_ID; i++){
        SPP[i].print();
    }
}

void DirectedGraph::SPPDijkstraMatrix() {
    SPPDijkstraMatrix(distribution1(generator1)%next_ID);
}

void DirectedGraph::SPPBelFordMatrix() {
    SPPBelFordMatrix(distribution1(generator1)%next_ID);
}

void DirectedGraph::SPPBelFordMatrix(int start) {
    delete[] SPP;
    SPPcreated = true;
    SPP = (VortexPath*) malloc( next_ID * sizeof(VortexPath));
    for (int i = 0; i < next_ID; i++){
        SPP[i] = VortexPath(i, INT32_MAX, -1);
    }
    SPP[start].parent = -2;
    SPP[start].pathWeight = 0;

    for (int i = 0; i < next_ID - 1; i++){
        int changes = 0;
        for(int j = 0; j < next_ID; j++){

            if (SPP[j].parent == -1) continue;

            for (int k = 0; k < next_ID; k++) {
                Edge pom = vortices[j].edgesMatrix[k];
                if(pom.capacity == -1) continue;
                if((SPP[j].pathWeight + pom.capacity) < SPP[pom.destination].pathWeight){
                    SPP[pom.destination].pathWeight = SPP[j].pathWeight + pom.capacity;
                    SPP[pom.destination].parent = j;
                    changes++;
                }
            }

        }
        if (changes == 0) return;
    }
}

void DirectedGraph::SPPDijkstraMatrix(int start) {
    delete[] SPP;
    SPPcreated = true;
    SPP = (VortexPath*) malloc( next_ID * sizeof(VortexPath));
    for (int i = 0; i < next_ID; i++){
        SPP[i] = VortexPath(i, INT32_MAX, -1);
    }
    SPP[start].parent = -2;
    SPP[start].pathWeight = 0;

    int idCurr = start;
    for (int i = 0; i < next_ID; i++){
        SPP[idCurr].visited = true;
        for (int j = 0; j < next_ID; j++){
            Edge pom = vortices[idCurr].edgesMatrix[j];
            if (pom.capacity == -1) continue;

            if((SPP[idCurr].pathWeight + pom.capacity) < SPP[pom.destination].pathWeight){
                SPP[pom.destination].pathWeight = SPP[idCurr].pathWeight + pom.capacity;
                SPP[pom.destination].parent = idCurr;
            }
        }
        PriorityQueue prioQu = PriorityQueue(false);

        for(int j = 0; j < next_ID; j++){
            if (SPP[j].visited) continue;
            if (SPP[j].parent == -1) continue;
            prioQu.pushSPP(SPP[j]);
        }
        idCurr = prioQu.topSPP().id;
    }
    unvisit();
}

void DirectedGraph::createMatrix() {
    for (int i = 0; i < next_ID; ++i) {
        vortices[i].createEdgeMatrix(next_ID,nullEdge);
    }
}

void DirectedGraph::unvisit() {
    for (int i = 0; i < next_ID; ++i) {
        vortices[i].visited = false;
    }
}

void DirectedGraph::printSPPcost() {
    if (!SPPcreated) return;
    int cost = 0;
    for (int i = 0; i < next_ID; ++i) {
        cost += SPP[i].pathWeight;
    }
    std::cout<<"Cost: "<<cost<<"\n";
}
