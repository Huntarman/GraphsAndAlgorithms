#include <iostream>
#include "ComponentsBasic/Edge.h"
#include "ComponentsBasic/Vortex.h"
#include "Graph/Graph.h"
#include "DirectedGraph/DirectedGraph.h"
#include <fstream>
#include <windows.h>
#include "random"
using std::cout;

void createFile(int vortexAmount, int edgeAmount, bool undirected);
void undirectedGraph();
void directedGraph();
void directedGraphTest(int size);
void undirectedGraphTest(int size);
void StartCounter();
double GetCounter();

long long CounterStart = 0;
double PCFreq = 0.0;
std::random_device rand_dev2;
std::mt19937 generatorMain(rand_dev2());
std::uniform_int_distribution<int> distributionMain(1, 100);

int main() {

    while(true){
        cout<<"___MENU___\n";
        cout<<"1 - UNDIRECTED GRAPH - MST\n";
        cout<<"2 - DIRECTED GRAPH - SPP\n";
        cout<<"3 - GENERATE FILE\n";
        cout<<"4 - EXIT\n";
        cout<<"Input: ";
        int a;
        std::cin>>a;
        getchar();
        system("cls");
        switch (a) {
            case 1:
                undirectedGraph();
                system("cls");
                break;

            case 2:
                directedGraph();
                system("cls");
                break;

            case 3:
                cout<<"NOTE: The graph that would be created from the file generated by this function\n";
                cout<<"will always create a graph where all vertices are connected; if edge amount is small\n";
                cout<<"enough, the function will add all required edges anyway.\n";
                cout<<"If the edge amount is too big, the function will not go over the density of 100%.\n";
                int b;
                cout<<"How many vortices: ";
                std::cin>>b;
                int c;
                cout<<"\nHow many edges: ";
                std::cin>>c;
                int d;
                cout<<"\n1 - Directed graph\n2 - Undirected graph\n";
                std::cin>>d;
                if(d == 1) createFile(b,c, false);
                else if (d == 2) createFile(b,c, true);
                else cout<<"Incorrect input";
                break;

            case 4:
                exit(0);

            default:
                cout<<"Wrong Input!\n";
                getchar();
                getchar();
                system("cls");
                break;
        }
    }
}

void undirectedGraph() {
    Graph graph = Graph();
    while (true){
        cout<<"Graph - List:\n";
        graph.printGraphList();
        cout<<"\nGraph - Matrix:\n";
        graph.printGraphMatrix();
        cout<<"\nMST - List:\n";
        graph.printMSTList();
        cout<<"\nMST - Matrix:\n";
        graph.printMSTMatrix();
        cout<<"MST cost: "<<graph.mst_weight<<"\n";
        int cond = 0;
        cout<<"\n___UNDIRECTED_GRAPH___\n";
        cout<<"1 - Add vortex\n";
        cout<<"2 - Add multiple vortices\n";
        cout<<"3 - Add edge\n";
        cout<<"4 - Add density\n";
        cout<<"5 - Create graph from file\n";
        cout<<"NOTE - These algorithm's will not work properly or at all, if all vortices aren't connected!\n";
        cout<<"6 - Kruskal's algorithm (from list)\n";
        cout<<"7 - Kruskal's algorithm (from matrix)\n";
        cout<<"8 - Prime's algorithm (from list)\n";
        cout<<"9 - Prime's algorithm (from matrix)\n";
        cout<<"0 - Return to menu\n";
        cout<<"10 - tests\n";
        std::cin>>cond;
        switch (cond) {
            case 1:
                graph.addVortex();
                break;

            case 2:
                int n;
                cout<<"How many: ";
                std::cin>>n;
                graph.addMultipleVortices(n);
                break;

            case 3:
                int source, destination, capacity;
                cout<<"Source: ";
                std::cin>>source;
                cout<<"\nDestination: ";
                std::cin>>destination;
                cout<<"\nWeight: ";
                std::cin>>capacity;
                graph.addEdge(Edge(source,destination,capacity));
                graph.createMatrix();
                break;

            case 4:
                double den;
                cout<<"Density: ";
                std::cin>>den;
                graph.addMultipleEdges(den);
                graph.createMatrix();
                break;

            case 5: {
                std::ifstream readfile("graph.txt");
                int vortexAmount,edgeAmount;
                readfile>>vortexAmount;
                readfile>>edgeAmount;
                graph.addMultipleVortices(vortexAmount);
                for (int i = 0; i < edgeAmount; ++i) {
                    int a,b,c;
                    readfile>>a>>b>>c;
                    graph.addEdge(Edge(a,b,c));
                }
                readfile.close();
                graph.createMatrix();
            }
                break;

            case 6:
                graph.mstKruskal();
                break;

            case 7:
                graph.mstKruskalMatrix();
                break;

            case 8:
                graph.mstPrim();
                break;

            case 9:
                graph.mstPrimMatrix();
                break;

            case 0:
                return;

            case 10:
                int size;
                cout<<"Graph size: ";
                std::cin>>size;
                undirectedGraphTest(size);
                system("cls");
                break;

            default:
                cout<<"Wrong input!\n";
        }
        getchar();
        getchar();
        system("cls");
    }
}

void directedGraph() {
    DirectedGraph graph = DirectedGraph();
    while (true){
        cout<<"Graph - List:\n";
        graph.printGraphList();
        cout<<"\nGraph - Matrix:\n";
        graph.printGraphMatrix();
        cout<<"\nMST - List:\n";
        graph.printSPPList();
        graph.printSPPcost();
        int cond = 0;
        cout<<"\n___DIRECTED_GRAPH___\n";
        cout<<"1 - Add vortex\n";
        cout<<"2 - Add multiple vortices\n";
        cout<<"3 - Add edge\n";
        cout<<"4 - Add density\n";
        cout<<"5 - Create graph from file\n";
        cout<<"NOTE - These algorithm's will not work properly or at all, if all vortices aren't connected!\n";
        cout<<"6 - Dijkstra's algorithm (from list)\n";
        cout<<"7 - Dijkstra's algorithm (from matrix)\n";
        cout<<"8 - Belmon-Ford's algorithm (from list)\n";
        cout<<"9 - Belmon-Ford's algorithm (from matrix)\n";
        cout<<"0 - Return to menu\n";
        cout<<"10 - tests\n";
        std::cin>>cond;
        switch (cond) {
            case 1:
                graph.addVortex();
                break;

            case 2:
                int n;
                cout<<"How many: ";
                std::cin>>n;
                graph.addMultipleVortices(n);
                break;

            case 3:
                int source, destination, capacity;
                cout<<"Source: ";
                std::cin>>source;
                cout<<"\nDestination: ";
                std::cin>>destination;
                cout<<"\nWeight: ";
                std::cin>>capacity;
                graph.addEdge(Edge(source,destination,capacity));
                graph.createMatrix();
                break;

            case 4:
                double den;
                cout<<"Density: ";
                std::cin>>den;
                graph.addMultipleEdges(den);
                graph.createMatrix();
                break;

            case 5: {
                std::ifstream readfile("graph.txt");
                int vortexAmount,edgeAmount;
                readfile>>vortexAmount;
                readfile>>edgeAmount;
                graph.addMultipleVortices(vortexAmount);
                for (int i = 0; i < edgeAmount; ++i) {
                    int a,b,c;
                    readfile>>a>>b>>c;
                    graph.addEdge(Edge(a,b,c));
                }
                readfile.close();
                graph.createMatrix();
            }
                break;

            case 6: {
                int index;
                cout<<"Index of vortex: ";
                std::cin>>index;
                graph.SPPDijkstra(index);
                break;
            }

            case 7:{
                int index;
                cout<<"Index of vortex: ";
                std::cin>>index;
                graph.SPPDijkstraMatrix(index);
                break;
            }

            case 8:{
                int index;
                cout<<"Index of vortex: ";
                std::cin>>index;
                graph.SPPBelFord(index);
                break;
            }

            case 9:{
                int index;
                cout<<"Index of vortex: ";
                std::cin>>index;
                graph.SPPBelFordMatrix(index);
                break;
            }

            case 10:
                int size;
                cout<<"Graph size: ";
                std::cin>>size;
                directedGraphTest(size);
                system("cls");
                return;
            case 0:
                return;

            default:
                cout<<"Wrong input!\n";
        }
        getchar();
        getchar();
        system("cls");
    }
}

void createFile(int vortexAmount, int edgeAmount, bool undirected) {
    int edgecap = 0;
    int edgeIndex = 0;

    for (int i = 0; i < vortexAmount; i++) {
        edgecap += i;
    }
    if (!undirected) edgecap *= 2;
    if (edgeAmount > edgecap) edgeAmount = edgecap;
    if (edgeAmount < vortexAmount-1) edgeAmount = vortexAmount - 1;
    int edges[edgeAmount][3];
    int edgesLeft = edgeAmount;

    bool availMatrix[vortexAmount][vortexAmount];

    for (int i = 0; i < vortexAmount; i++) {
        for (int j = 0; j < vortexAmount; j++) {
            if (j != i) availMatrix[i][j] = true;
            else availMatrix[i][j] = false;
        }
    }
    //ale spaggeti
    if (edgesLeft >= edgecap) {
        for (int i = 0; i < vortexAmount; i++) {
            for (int j = 0; j < vortexAmount; j++) {
                if (availMatrix[i][j]) {
                    edges[edgeIndex][0] = i;
                    edges[edgeIndex][1] = j;
                    edges[edgeIndex++][2] = distributionMain(generatorMain);
                    availMatrix[i][j] = false;
                    if (undirected) availMatrix[j][i] = false;
                }
            }
        }
    }

    else{

        for (int i = 0; i < vortexAmount; i++) {
            edgesLeft--;
            edges[edgeIndex][0] = i;
            edges[edgeIndex][1] = (i + 1) % vortexAmount;
            edges[edgeIndex++][2] = distributionMain(generatorMain);
            availMatrix[i][(i + 1) % vortexAmount] = false;
            if (undirected) {
                availMatrix[(i + 1) % vortexAmount][i] = false;
            }
        }

        while (edgesLeft > 0){

            if((double)(edgeAmount - edgesLeft)/(double)edgecap > 0.95){
                int i = vortexAmount - 1;
                while(edgesLeft > 0){
                    for (int j = 0; j < vortexAmount; j++) {
                        if (availMatrix[i][j]){
                            edgesLeft--;
                            edges[edgeIndex][0]=i;
                            edges[edgeIndex][1]=j;
                            edges[edgeIndex++][2]=distributionMain(generatorMain);
                            availMatrix[i][j] = false;
                            if (undirected) availMatrix[j][i] = false;
                        }
                    }
                    i--;
                }
                continue;
            }

            int x = distributionMain(generatorMain) % vortexAmount;
            int y = distributionMain(generatorMain) % vortexAmount;
            if (availMatrix[x][y]){
                edgesLeft--;
                edges[edgeIndex][0]=x;
                edges[edgeIndex][1]=y;
                edges[edgeIndex++][2]=distributionMain(generatorMain);
                availMatrix[x][y] = false;
                if (undirected) availMatrix[y][x] = false;
            }
        }

    }

    std::ofstream file("graph.txt");
    file<<vortexAmount<<" "<<edgeAmount<<"\n";
    for (int i = 0; i < edgeAmount; i++) {
        file<<edges[i][0]<<" "<<edges[i][1]<<" "<<edges[i][2]<<"\n";
    }
    file.close();
}

void StartCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000000.0;//czas w mikrosekundach
    //PCFreq = double(li.QuadPart)/1000.0;//czas w milisekundach
    //PCFreq = double(li.QuadPart);//czas w sekundach
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

void undirectedGraphTest(int graph_size) {
    double densities[4] = {0.25, 0.50, 0.75, 0.99};
    std::ofstream file ("kruskal.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            Graph graph2 = Graph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            StartCounter();
            graph2.mstKruskal();
            a = GetCounter();
            file<<a<<";";
        }
        file<<"\n";
    }
    file.close();
    cout<<"Got here\n";
    std::ofstream file2 ("kruskalMatrix.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            Graph graph2 = Graph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            graph2.createMatrix();
            StartCounter();
            graph2.mstKruskalMatrix();
            a = GetCounter();
            file2<<a<<";";
        }
        file2<<"\n";
    }
    file2.close();
    cout<<"Got here\n";
    std::ofstream file3 ("prim.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            Graph graph2 = Graph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            StartCounter();
            graph2.mstPrim();
            a = GetCounter();
            file3<<a<<";";
        }
        file3<<"\n";
    }
    file3.close();
    cout<<"Got here\n";
    std::ofstream file4 ("primMatrix.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            Graph graph2 = Graph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            graph2.createMatrix();
            StartCounter();
            graph2.mstPrimMatrix();
            a = GetCounter();
            file4<<a<<";";
        }
        file4<<"\n";
    }
    file4.close();
    cout<<"Got here\n";
}

void directedGraphTest(int graph_size) {
    double densities[4] = {0.25, 0.50, 0.75, 0.99};
    std::ofstream file ("Dijkstra.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            DirectedGraph graph2 = DirectedGraph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            StartCounter();
            graph2.SPPDijkstra();
            a = GetCounter();
            file<<a<<";";
        }
        file<<"\n";
    }
    file.close();
    cout<<"Got here\n";
    std::ofstream file2 ("DijkstraMatrix.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            DirectedGraph graph2 = DirectedGraph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            graph2.createMatrix();
            StartCounter();
            graph2.SPPDijkstraMatrix();
            a = GetCounter();
            file2<<a<<";";
        }
        file2<<"\n";
    }
    file2.close();
    cout<<"Got here\n";
    std::ofstream file3 ("Belford.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            DirectedGraph graph2 = DirectedGraph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            StartCounter();
            graph2.SPPBelFord();
            a = GetCounter();
            file3<<a<<";";
        }
        file3<<"\n";
    }
    file3.close();
    cout<<"Got here\n";
    std::ofstream file4 ("BelFordMatrix.csv");
    for (int i = 0; i < 100; ++i) {
        for (double density : densities) {
            double a;
            DirectedGraph graph2 = DirectedGraph();
            graph2.addMultipleVortices(graph_size);
            graph2.addMultipleEdges(density);
            graph2.createMatrix();
            StartCounter();
            graph2.SPPBelFordMatrix();
            a = GetCounter();
            file4<<a<<";";
        }
        file4<<"\n";
    }
    file4.close();
    cout<<"Got here\n";
}