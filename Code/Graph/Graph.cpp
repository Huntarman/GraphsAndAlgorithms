//
// Created by micha on 23.05.2023.
//

#include "Graph.h"
#include "iostream"
#include "../ComponentsGraph/UnionFind.h"
#include "../ComponentsGraph/PriorityQueue.h"
#include "random"
std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> distribution(1, 100);

Graph::Graph() {
    this->next_ID = 0;
    this->edgeAmount = 0;
    this->edgeCap = 0;
    this->vortices = (Vortex*) malloc(0);
    this->edges = (Edge*) malloc(0);
    this->MST = (Vortex*) malloc(0);
    IncidenceMatrix = (Edge*) malloc(0);
}
void Graph::addVortex() {
    auto newVortex = Vortex(next_ID);
    edgeCap += next_ID;
    next_ID++;
    vortices = (Vortex*) realloc(vortices, next_ID * sizeof(Vortex));
    vortices[next_ID-1] = newVortex;
}
void Graph::addMultipleVortices(int amount){
    for (int i = 0; i<amount; i++) {
        addVortex();
    }
}

void Graph::addEdge(Edge edge) {
    if (edge.source > next_ID-1 || edge.destination > next_ID-1){
        std::cout<<"Can't add edge!\n";
        return;
    }
    edgeAmount++;
    edges = (Edge*) realloc(edges, edgeAmount * sizeof(Edge));
    edges[edgeAmount-1] = edge;

    vortices[edge.source].addEdge(edge);
    vortices[edge.destination].addEdge(Edge(edge.destination,edge.source,edge.capacity));
}

void Graph::printGraphList() {
    if (next_ID == 0){
        std::cout<<"Graph Empty\n";
        return;
    }
    for (int i = 0; i < next_ID; i++) {
        vortices[i].printEdges();
        std::cout<<"\n";
    }
}

void Graph::addMultipleEdges(double percentage) {
    bool availMatrix[next_ID][next_ID];

    for (int i = 0; i < next_ID;i++){
        for (int j = 0; j<next_ID;j++){
            if (j != i ) availMatrix[i][j] = true;
            else availMatrix[i][j] = false;
        }
    }
    //Jesli wypelnienie ejst rowne 100%, algorytm po prostu tworzy graf pelny
    if (percentage >= 1.0){
        for (int i = 0; i<next_ID-1;i++){
            for (int j = i+1; j < next_ID; j++) {
                if (availMatrix[i][j]) {
                    addEdge(Edge(i, j, distribution(generator)));
                    availMatrix[i][j] = false;
                    availMatrix[j][i] = false;
                }
            }
        }
        return;
    }
    //Tutaj algorytm upewnia sie ze wszystkie wierzcholki beda mialy przynajmniej jedno polaczenie
    for (int i = 0; i<next_ID-1;i++){
        addEdge(Edge(i, (i+1) % next_ID, distribution(generator)));
        availMatrix[i][(i+1)%next_ID] = false;
        availMatrix[(i+1)%next_ID][i] = false;
    }
    //tworzenie krawedzi laczace 2 losowe wierzcholki
    while(percentage >= (double)edgeAmount/(double)edgeCap){

        //jesli jz wypelnilismy wiekszosc mozliwych krawedzi, algorytm zmniejsza swoja losowosc, aby nie utknac
        if((double)edgeAmount/(double)edgeCap > 0.95){
            int i = next_ID-1;
            while(percentage >= (double)edgeAmount/(double)edgeCap){
                for (int j = 0; j < next_ID; j++) {
                    if (availMatrix[i][j]){
                        addEdge(Edge(i,j,distribution(generator)));
                        availMatrix[i][j] = false; availMatrix[j][i] = false;
                    }
                }
                i--;
            }
            continue;
        }

        int x = distribution(generator)%next_ID;
        int y = distribution(generator)%next_ID;
        if (availMatrix[x][y]){
            addEdge(Edge(x,y,distribution(generator)%100 + 1));
            availMatrix[x][y] = false; availMatrix[y][x] = false;
        }

    }
    //for (int i = 0; i<next_ID;i++){
    //    for (int j = 0; j < next_ID; j++) {
    //        std::cout<<availMatrix[i][j]<<" ";
    //    }
    //    std::cout<<"\n";
    //}
}

void Graph::mstKruskal() {
    //its alive!!
    PriorityQueue queue;
    for (int i = 0; i < next_ID; i++){
        for (int j = 0; j < vortices[i].getEdgeAmount(); j++) {
            queue.push(vortices[i].edges[j]);
        }
    }
    int mstEdgesCount = 0;
    Edge* mstEdges = (Edge*) malloc(0);
    int i = 0;
    while (mstEdgesCount != next_ID - 1){
        mstEdgesCount++;
        mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        mstEdges[mstEdgesCount-1] = queue.top();
        queue.pop();
        if (hasCycle(mstEdges,mstEdgesCount)){
            mstEdgesCount--;
            mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        }
        i++;
    }
    EDGESMST = mstEdges;
}

void Graph::mstKruskalMatrix() {
    //its dead!!
    PriorityQueue queue;
    for (int i = 0; i < next_ID; i++){
        for (int j = 0; j < edgeAmount; j++) {
            if (IncidenceMatrix[i * edgeAmount + j].capacity != 0) {
                queue.push(IncidenceMatrix[i * edgeAmount + j]);
            }
        }
    }
    int mstEdgesCount = 0;
    Edge* mstEdges = (Edge*) malloc(0);
    int i = 0;
    while (mstEdgesCount != next_ID - 1){
        mstEdgesCount++;
        mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        mstEdges[mstEdgesCount-1] = queue.top();
        queue.pop();
        if (hasCycle(mstEdges,mstEdgesCount)){
            mstEdgesCount--;
            mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        }
        i++;
    }
    EDGESMST = mstEdges;
}

void Graph::printMSTList() {
    if (!MSTcreated){
        std::cout<<"MST not created yet!\n";
        return;
    }
    for (int i = 0; i < next_ID; i++) {
        MST[i].printEdges();
        std::cout<<"\n";
    }
}

bool Graph::hasCycle(Edge* edges, int edgeCount) {
    UnionFind unionFind(next_ID);

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].source;
        int v = edges[i].destination;
        if (!unionFind.unionSets(u, v)) {
            return true;
        }
    }
    return false;
}

void Graph::mstPrim() {
    mstPrim(distribution(generator)%next_ID);
}
void Graph::mstPrimMatrix() {
    mstPrimMatrix(distribution(generator)%next_ID);
}
void Graph::printMatrix(Edge* listVor, int n) {
    std::cout<<"E:\t";
    for (int j = 0; j < n; ++j) {
        std::cout<<j<<"\t";
    }
    std::cout<<"\n";
    for (int i = 0; i < next_ID; ++i) {
        std::cout<<"V:"<<i<<"|\t";
        for (int j = 0; j < n; ++j) {
            std::cout<<listVor[ i * n + j].capacity<<"\t";
        }
        std::cout<<"\n";
    }
}

void Graph::createMST(){
    delete[] MST;
    mst_weight = 0;
    MSTcreated = true;
    MST = (Vortex*) malloc(next_ID*sizeof(Vortex));
    for (int i = 0; i < next_ID; i++) {
        MST[i] = Vortex(i);
    }
    for (int j = 0; j < next_ID - 1; j++) {
        mst_weight += EDGESMST[j].capacity;
        int a = EDGESMST[j].source;
        int b = EDGESMST[j].destination;
        int c = EDGESMST[j].capacity;
        MST[a].addEdge(Edge(a,b,c));
        MST[b].addEdge(Edge(b,a,c));
    }
}

void Graph::printGraphMatrix() {
    if (next_ID == 0){
        std::cout<<"Graph Empty\n";
        return;
    }
    printMatrix(IncidenceMatrix, edgeAmount);
}

void Graph::mstPrim(int start) {
    if (start < 0 || start >= next_ID){
        std::cout<<"Incorrect vortex chosen!\n";
        return;
    }
    int mstEdgesCount = 0;
    int vorID = start;
    PriorityQueue prioQu = PriorityQueue();
    Edge* mstEdges = (Edge*) malloc(0);
    while (mstEdgesCount != next_ID - 1){
        if (!vortices[vorID].visited) {
            vortices[vorID].visited = true;
            for (int i = 0; i < vortices[vorID].getEdgeAmount(); i++) {
                prioQu.push(vortices[vorID].edges[i]);
            }
        }
        mstEdgesCount++;
        mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        mstEdges[mstEdgesCount-1] = prioQu.top();
        vorID = mstEdges[mstEdgesCount-1].destination;
        prioQu.pop();
        if (hasCycle(mstEdges,mstEdgesCount)){
            mstEdgesCount--;
            mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        }
    }
    EDGESMST = mstEdges;
    unvisit();
}
void Graph::mstPrimMatrix(int start) {
    if (start < 0 || start >= next_ID){
        std::cout<<"Incorrect vortex chosen!\n";
        return;
    }
    int mstEdgesCount = 0;
    int vorID = start;
    PriorityQueue prioQu = PriorityQueue();
    Edge* mstEdges = (Edge*) malloc(0);
    while (mstEdgesCount != next_ID - 1){
        if (!vortices[vorID].visited) {
            vortices[vorID].visited = true;
            for (int i = 0; i < edgeAmount; i++) {
                if (IncidenceMatrix[vorID * edgeAmount + i].capacity == 0) continue;
                prioQu.push(IncidenceMatrix[vorID * edgeAmount + i]);
            }
        }
        mstEdgesCount++;
        mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        mstEdges[mstEdgesCount-1] = prioQu.top();
        vorID = mstEdges[mstEdgesCount-1].destination;
        prioQu.pop();
        if (hasCycle(mstEdges,mstEdgesCount)){
            mstEdgesCount--;
            mstEdges = (Edge*) realloc( mstEdges,mstEdgesCount * sizeof(Edge));
        }
    }
    EDGESMST = mstEdges;
    unvisit();
}
void Graph::createMatrix() {
    delete[] IncidenceMatrix;
    IncidenceMatrix =(Edge*) malloc( next_ID * edgeAmount * sizeof(Edge));
    for (int i = 0; i < next_ID; ++i) {
        for (int j = 0; j < edgeAmount; ++j) {
            IncidenceMatrix[ i * (edgeAmount) + j] = nullEdge;
        }
    }
    for (int j = 0; j < edgeAmount; ++j) {
        IncidenceMatrix[edges[j].source * edgeAmount + j] = edges[j];
        IncidenceMatrix[edges[j].destination * edgeAmount + j] = Edge(edges[j].destination,edges[j].source,edges[j].capacity);
    }
}

void Graph::unvisit() {
    for (int i = 0; i < next_ID; ++i) {
        vortices[i].visited = false;
    }
}
