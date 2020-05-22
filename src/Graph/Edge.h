#ifndef EDGE_H
#define EDGE_H

#include <string>
#include "Utils.h"
/**
 * @file Edge.h
 * @brief File containing the implementation of the edges for the graph
 */


class Vertex;
class Edge {
    public:
        Edge(Vertex* d, double w);
        Edge(Vertex* d, double w, const std::string& streetName);
        friend class Graph;
        friend class Vertex;
        Vertex* getDest() const;
    private:
        Vertex* dest;           // destination vertex
        double weight;          // edge weight
        std::string streetName;
};

#endif //EDGE_H