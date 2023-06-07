//
// Created by micha on 27.05.2023.
//

#ifndef SDIZO_PROJECT_2_VORTEXPATH_H
#define SDIZO_PROJECT_2_VORTEXPATH_H


class VortexPath {
public:
    int id;
    int pathWeight;
    int parent;
    bool visited = false;
public:
    VortexPath(int id, int weight, int parent);
    void print();
};


#endif //SDIZO_PROJECT_2_VORTEXPATH_H
