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
#include <unordered_set>

using namespace std;


class Graph {
    private:
        vector<Vertex*> vertexSet;    // vertex set
        double **dist = nullptr; // dist
        int **pred = nullptr; // path
    public:
        ~Graph();
        Vertex *findVertex(const ulli &in) const;
        bool addVertex(const ulli &in);
        bool addVertex(const ulli &in, const double lon, const double lat);
        bool addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName = "");
        inline ulli findVertexIdx(const ulli &in) const;
        void floydWarshallShortestPath();
        vector<ulli> getFloydWarshallPath(const ulli &origin, const ulli &dest) const;

        /**
         * Calculates the path given the points of interest using the greedy strategy
         * @param origin point where the person is
         * @param poi list of the id's of the points of interest
         * @return visiting order of the points of interest
         */
        vector<ulli> trajectoryOrder(ulli origin, vector<ulli>& poi);

        /**
         * Auxiliar function to trajectoryPath. It gets the next poi to be visited
         * @param origin actual position
         * @param poi poi's left to visit
         * @return id of the next poi to be visited
         */
        ulli nextPoi(const ulli& origin, vector<ulli>& poi, vector<bool> visited);

        vector<Vertex*> getVertexSet();
};

#endif //GRAPH_H