//
// Created by micha on 27.05.2023.
//
#include "iostream"
#include "VortexPath.h"

void VortexPath::print() {
    std::cout<<"ID:"<<id<<"| ";
    if (parent == -1){
        std::cout<<"Path not found!\n";
        return;
    }
    std::cout<<"D:"<< pathWeight<< " P:";
    if (parent == -2){
        std::cout<<"-";
    }
    else std::cout<<parent;
    std::cout<<"\n";
}

VortexPath::VortexPath(int id, int weight, int parent) {
    this->id = id;
    this->pathWeight = weight;
    this->parent = parent;
}
