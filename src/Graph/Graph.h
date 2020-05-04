#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "Utils.h"
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <string>

using namespace std;

class Graph {
    private:
        vector<Vertex*> vertexSet;
        vector<vector<double>> dist;
        vector<vector<Vertex*>> pred;
    public:
        Vertex* findVertex(const ulli &in) const;
        bool addVertex(const ulli &in);
        bool addEdge(const ulli &sourc, const ulli &dest, double w, const string& streetName = "");
        int getNumVertex() const;
        vector<Vertex*> getVertexSet() const;

        void unweightedShortestPath( const ulli &s);
        void dijkstraShortestPath( const ulli &s);
        void bellmanFordShortestPath( const ulli &s);
        vector<int> getPathTo(const ulli &dest) const;

        void floydWarshallShortestPath();
        vector<int> getfloydWarshallPath(const ulli &origin, const ulli &dest) const;
};

#endif //GRAPH_H