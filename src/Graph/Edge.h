#ifndef EDGE_H
#define EDGE_H

#include <string>
#include "Utils.h"
/**
 * @file Edge.h
 * @brief File containing the implementation of the edges for the graph
 */


class Vertex;
class Edge {
    public:

        /**
        * @brief Constructor for edge
        * @param d Destine vertex
        * @param w Weight
        */
        Edge(Vertex* d, double w);


        /**
        * @brief Constructor for the edge
        * @param d Destine vertex
        * @param w Weight
        * @param sn Name of the street
        */
        Edge(Vertex* d, double w, const std::string& streetName);
        friend class Graph;
        friend class Vertex;

        /**
         * @brief Get function
         * @return returns the destine vertex
         */
        Vertex* getDest() const;
    private:
        Vertex* dest;           /*<destination vertex*/
        double weight;          /*<edge weight*/
        std::string streetName; /*<name of the street*/
};

#endif //EDGE_H