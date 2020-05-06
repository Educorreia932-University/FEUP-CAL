#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include "Edge.h"
#include "utils.h"

using namespace std;

class Vertex {
public:
    Vertex(const ulli &id);

    ulli getID() const;

    double getDist() const;

    Vertex *getPath() const;

    void addEdge(Vertex *dest, double w, const string &streetName = "");

    bool operator<(Vertex &vertex) const; // required by MutablePriorityQueue
    friend class Graph;

private:
    ulli id;                    // content of the vertex
    vector<Edge> adj;        // outgoing edges

    double dist = 0;
    Vertex *path = NULL;

    bool visited = false;        // auxiliary field
    bool processing = false;    // auxiliary field
};

#endif // VERTEX_h