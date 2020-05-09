#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "utils.h"
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;


class Graph {
private:
    vector<Vertex*> vertexSet;    // vertex set
    double **dist = nullptr; // dist
    int **pred = nullptr; // path
public:

    Vertex *findVertex(const ulli &in) const;

    bool addVertex(const ulli &in);

    bool addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName = "");

    ~Graph();

    inline ulli findVertexIdx(const ulli &in) const;

    void floydWarshallShortestPath();

    vector<ulli> getFloydWarshallPath(const ulli &origin, const ulli &dest) const;
};

#endif //GRAPH_H