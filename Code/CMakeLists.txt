cmake_minimum_required(VERSION 3.24)
project(SDiZO_Project_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SDiZO_Project_2 main.cpp ComponentsBasic/Vortex.cpp ComponentsBasic/Vortex.h ComponentsBasic/Edge.cpp ComponentsBasic/Edge.h Graph/Graph.cpp Graph/Graph.h ComponentsGraph/UnionFind.cpp ComponentsGraph/UnionFind.h ComponentsGraph/PriorityQueue.cpp ComponentsGraph/PriorityQueue.h DirectedGraph/DirectedGraph.cpp DirectedGraph/DirectedGraph.h ComponentsDirectedGraph/VortexPath.cpp ComponentsDirectedGraph/VortexPath.h)
