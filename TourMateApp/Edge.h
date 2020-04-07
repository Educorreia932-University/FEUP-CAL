#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge {
    public:
        Edge(Vertex* d, double w);
        friend class Graph;
        friend class Vertex;
    private:
        Vertex* dest;      // destination vertex
        double weight;         // edge weight
};

#endif //EDGE_H