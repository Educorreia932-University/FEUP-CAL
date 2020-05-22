#include "Edge.h"

/**
 * @file Edge.cpp
 * @brief File containing the implementation for the edges
 */



Edge::Edge(Vertex* d, double w): dest(d), weight(w) {}

Edge::Edge(Vertex* d, double w, const std::string& sn): dest(d), weight(w), streetName(sn) {}

Vertex *Edge::getDest() const {
    return dest;
}
