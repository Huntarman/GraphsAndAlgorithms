//
// Created by micha on 23.05.2023.
//

#ifndef SDIZO_PROJECT_2_UNIONFIND_H
#define SDIZO_PROJECT_2_UNIONFIND_H


#include <iostream>

class UnionFind {
private:
    int* parent;
    int* rank;

public:
    UnionFind(int n);
    int find(int x);
    bool unionSets(int x, int y);
};




#endif //SDIZO_PROJECT_2_UNIONFIND_H
