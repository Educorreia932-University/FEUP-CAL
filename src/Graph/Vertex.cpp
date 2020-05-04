#include "Vertex.h"

Vertex::Vertex(const ulli& id): id(id) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex* d, double w, const string& streetName) {
    adj.push_back(Edge(d, w, streetName));
}


bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

ulli Vertex::getID() const {
    return this->id;
}

double Vertex::getDist() const {
    return this->dist;
}

Vertex* Vertex::getPath() const {
    return this->path;
}

vector<Edge> Vertex::getAdj() const {
    return adj;
}

