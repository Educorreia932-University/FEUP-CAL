#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>

using namespace std;

class Graph {
    private:
        vector<Vertex*> vertexSet;    // vertex set
        vector<vector<double>> dist;
        vector<vector<Vertex*>> pred;
    public:
        Vertex* findVertex(const int &id) const;
        bool addVertex(const int &id);
        bool addEdge(const int &sourc, const int &dest, double w);
        int getNumVertex() const;
        vector<Vertex*> getVertexSet() const;

        void unweightedShortestPath(const int &s);
        void dijkstraShortestPath(const int &s);
        void bellmanFordShortestPath(const int &s);
        vector<int> getPathTo(const int &dest) const;

        void floydWarshallShortestPath();
        vector<int> getfloydWarshallPath(const int &origin, const int &dest) const;
};

#endif //GRAPH_H