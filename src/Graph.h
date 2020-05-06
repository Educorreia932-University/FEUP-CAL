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
#include <unordered_set>

using namespace std;

//declaring the hashTable
//Since it's not good practice to use pointers at a hashtable, we are encapsulating
class Capsule {
private:
    Vertex *v;
public:
    Capsule(Vertex *v) {
        this->v = v;
    }

    Vertex *getVertex() const {
        return v;
    }
};

struct VertexHash {
    int operator()(const Capsule &ca) const {
        return 0;
    }

    bool operator()(Capsule ca1, Capsule ca2) const {
        return ca1.getVertex()->getID() == ca2.getVertex()->getID();
    }
};

typedef unordered_set<Capsule, VertexHash, VertexHash> tabHVertex;

class Graph {
private:
    tabHVertex vertexSet;    // vertex set
    vector<vector<double>> dist;
    vector<vector<Vertex *>> pred;
    double **W = nullptr; // dist
    int **P = nullptr; // path
public:

    Vertex *findVertex(const ulli &in) const;

    bool addVertex(const Capsule &in);

    bool addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName = "");

    int getNumVertex() const;

    tabHVertex getVertexSet() const;

    void unweightedShortestPath(const ulli &s);

    void dijkstraShortestPath(const ulli &s);

    void bellmanFordShortestPath(const ulli &s);

    vector<int> getPathTo(const ulli &dest) const;

    ~Graph();

    int findVertexIdx(const int &in) const;

    void floydWarshallShortestPath();

    vector<int> getFloydWarshallPath(const ulli &origin, const ulli &dest) const;
};

#endif //GRAPH_H