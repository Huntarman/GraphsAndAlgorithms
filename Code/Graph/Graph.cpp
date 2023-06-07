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
    delete[] MST;
    MSTcreated = true;
    PriorityQueue queue;
    for (int i = 0; i < next_ID; i++){
        for (int j = 0; j < vortices[i].getEdgeAmount(); j++) {
            queue.push(vortices[i].edges[j]);
        }
    }
    int mstEdgesCount = 0;
    MST = (Vortex*) malloc(next_ID * sizeof(Vortex));
    Edge* mstEdges = (Edge*) malloc(0);
    for (int i = 0; i<next_ID;i++) {
        MST[i] = Vortex(i);
    }
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
    for (int j = 0; j < mstEdgesCount; j++) {
        mst_weight += mstEdges[j].capacity;
        int a = mstEdges[j].source;
        int b = mstEdges[j].destination;
        int c = mstEdges[j].capacity;
        MST[a].addEdge(Edge(a,b,c));
        MST[b].addEdge(Edge(b,a,c));
    }
}

void Graph::mstKruskalMatrix() {
    //its dead!!
    delete[] MST;
    MSTcreated = true;
    PriorityQueue queue;
    for (int i = 0; i < next_ID; i++){
        for (int j = 0; j < next_ID; j++) {
            if (vortices[i].edgesMatrix[j].capacity == -1) continue;

            queue.push(vortices[i].edgesMatrix[j]);
        }
    }
    int mstEdgesCount = 0;
    MST = (Vortex*) malloc(next_ID * sizeof(Vortex));
    Edge* mstEdges = (Edge*) malloc(0);
    for (int i = 0; i<next_ID;i++) {
        MST[i] = Vortex(i);
    }
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
    for (int j = 0; j < mstEdgesCount; j++) {
        mst_weight += mstEdges[j].capacity;
        int a = mstEdges[j].source;
        int b = mstEdges[j].destination;
        int c = mstEdges[j].capacity;
        MST[a].addEdge(Edge(a,b,c));
        MST[b].addEdge(Edge(b,a,c));
    }
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
void Graph::printMatrix(Vortex* listVor, int n) {
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

void Graph::printMSTMatrix() {
    if (!MSTcreated){
        std::cout<<"MST not created yet!\n";
        return;
    }
    printMatrix(MST, next_ID);
}

void Graph::printGraphMatrix() {
    if (next_ID == 0){
        std::cout<<"Graph Empty\n";
        return;
    }
    printMatrix(vortices, next_ID);
}

void Graph::mstPrim(int start) {
    if (start < 0 || start >= next_ID){
        std::cout<<"Incorrect vortex chosen!\n";
        return;
    }
    delete[] MST;
    MSTcreated = true;
    MST = (Vortex*) malloc(next_ID*sizeof(Vortex));
    for (int i = 0; i < next_ID; i++) {
        MST[i] = Vortex(i);
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

    for (int i = 0; i < next_ID-1; i++) {
        mst_weight += mstEdges[i].capacity;
        int a = mstEdges[i].source; int b = mstEdges[i].destination; int c = mstEdges[i].capacity;
        MST[a].addEdge(Edge(a,b,c));
        MST[b].addEdge(Edge(b,a,c));
    }
    unvisit();
}
void Graph::mstPrimMatrix(int start) {
    if (start < 0 || start >= next_ID){
        std::cout<<"Incorrect vortex chosen!\n";
        return;
    }
    delete[] MST;
    MSTcreated = true;
    MST = (Vortex*) malloc(next_ID*sizeof(Vortex));
    for (int i = 0; i < next_ID; i++) {
        MST[i] = Vortex(i);
    }
    int mstEdgesCount = 0;
    int vorID = start;
    PriorityQueue prioQu = PriorityQueue();
    Edge* mstEdges = (Edge*) malloc(0);
    while (mstEdgesCount != next_ID - 1){
        if (!vortices[vorID].visited) {
            vortices[vorID].visited = true;
            for (int i = 0; i < next_ID; i++) {
                if (vortices[vorID].edgesMatrix[i].capacity == 0) continue;
                prioQu.push(vortices[vorID].edgesMatrix[i]);
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

    for (int i = 0; i < next_ID-1; i++) {
        mst_weight += mstEdges[i].capacity;
        int a = mstEdges[i].source; int b = mstEdges[i].destination; int c = mstEdges[i].capacity;
        MST[a].addEdge(Edge(a,b,c));
        MST[b].addEdge(Edge(b,a,c));
    }
    unvisit();
}
void Graph::createMatrix() {
    for (int i = 0; i < next_ID; ++i) {
        vortices[i].createEdgeMatrix(next_ID,nullEdge);
    }
}

void Graph::unvisit() {
    for (int i = 0; i < next_ID; ++i) {
        vortices[i].visited = false;
    }
}
