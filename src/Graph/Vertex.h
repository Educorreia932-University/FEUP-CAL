#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include "Edge.h"
#include "Utils.h"

using namespace std;

class Vertex {
    public:
        Vertex(const ulli &id, double lon, double lat);
        ulli getID() const;
        double getDist() const;
        Vertex *getPath() const;
        vector<Edge> getAdj() const;

        bool operator<(Vertex &vertex) const; // required by MutablePriorityQueue
        friend class Graph;
    private:
        double lon; // Longitude
        double lat; // Latitude

        ulli id;                    // content of the vertex
        vector<Edge> adj;        // outgoing edges

        double dist = 0;
        Vertex *path = NULL;

        bool visited = false;        // auxiliary field
        bool processing = false;    // auxiliary field

        void addEdge(Vertex *dest, double w, const string &streetName = "");
};

#endif // VERTEX_h