#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "Edge.h"

using namespace std;

class Vertex {
    public:
        Vertex(int id);
        unsigned int getID() const;
        double getDist() const;
        Vertex *getPath() const;

        bool operator<(Vertex & vertex) const; // required by MutablePriorityQueue
        friend class Graph;
    private:
        unsigned int id;		// content of the vertex
        vector<Edge> adj;		// outgoing edges

        double dist = 0;
        Vertex* path = NULL;

        bool visited = false;		// auxiliary field
        bool processing = false;	// auxiliary field

        void addEdge(Vertex *dest, double w);
};

#endif // VERTEX_h