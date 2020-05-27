#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include "Edge.h"
#include "Utils.h"

using namespace std;


/**
 * @file Vertex.h
 */
class Vertex {
public:

    double lat;                 /*<Latitude */
    double lon;                 /*<Longitude*/

    /**
     * @brief Constructor
     */
    Vertex(const ulli &id);

    /**
     * @brief Creates a vertex storing the latitude and longitude
     * @param id The id of the vertex
     * @param lon Longitude of the vertex
     * @param lat Latitude of the vertex
     */
    Vertex(const ulli &id, double lon, double lat);

    /**
     * @return Get the id of the vertex
     */
    ulli getID() const;
    /**
     * @brief Get all the adjacent edges
     * @return Return the edges
     */
    vector<Edge> getAdj() const;

    /**
     * @brief Operator required by the sort and mutable priority queue
     * @param vertex
     * @return
     */
    bool operator<(Vertex &vertex) const; // required by the sort and mutable priorityQueue

    friend class Graph;

private:
    ulli id;                /*< Id of the vertex*/
    vector<Edge> adj;       /*< Outgoing edges*/
    double dist = 0;
    Vertex *path = NULL;

    void addEdge(Vertex *dest, double w, const string &streetName = "");
};

#endif // VERTEX_h