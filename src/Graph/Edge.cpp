#include "Edge.h"

/**
 * @file Edge.cpp
 * @brief File containing the implementation for the edges
 */


/**
 * @brief Constructor for edge
 * @param d Destine vertex
 * @param w Weight
 */
Edge::Edge(Vertex* d, double w): dest(d), weight(w) {}

/**
 * @brief Constructor for the edge
 * @param d Destine vertex
 * @param w Weight
 * @param sn Name of the street
 */
Edge::Edge(Vertex* d, double w, const std::string& sn): dest(d), weight(w), streetName(sn) {}

/**
 * @brief Get function
 * @return returns the destine vertex
 */
Vertex *Edge::getDest() const {
    return dest;
}
