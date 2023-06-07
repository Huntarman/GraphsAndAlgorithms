//
// Created by micha on 23.05.2023.
//

#include "UnionFind.h"
//todo refractor
bool UnionFind::unionSets(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) {
            return false;  // Cycle detected
        }

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }

        return true;  // No cycle detected
}

int UnionFind::find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
}

UnionFind::UnionFind(int n) {
        parent = (int*) malloc(sizeof(int)*n);
        rank = (int*) malloc(sizeof(int)*n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
}
