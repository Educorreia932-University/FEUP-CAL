#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "Utils.h"
#include "Storage/PoiStorage.h"

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

/**
 * @file Graph.h
 * @brief File containing Graph class responsible for storing the graph of the city 
 */ 
class Graph {
private:
    vector<Vertex *> vertexSet;     /*< Containg all the vertexes in the graph */
    double **dist = nullptr; 		/*< dist */
    int **pred = nullptr; 			/*< pred*/

    friend class FloydStorage;
public:
    /**
     * @brief Default destructor
     */
    ~Graph();
    /**
     * @brief Get vertexSet vector
     * @return Return vertexSet vector containing all the vertex in the graph
     */
    vector<Vertex *> getVertexSet();

    /**
     * @brief Finds a specific vertex in the vertexSet vector
     * @param in ID of the vertex
     * @return Vertex
     */
    Vertex *findVertex(const ulli &in) const;
	/**
	 * @brief sorts the vertices according to the id's so that it can perform binary search to find a vertex Id 
	 */ 
    void sortVertexSet();
    /**
     * @brief Adds a vertex to the graph
     * @param in Id of the vertex
     * @return true case the vertex has been added. False otherwise.
     */
    bool addVertex(const ulli &in);

    /**
     * @brief Adds a vertex to the graph
     * @param in Id of the vertex
     * @param lon Longitude
     * @param lat Latitude
     * @return true case the vertex has been added, false otherwise.
     */
    bool addVertex(const ulli &in, const double lon, const double lat);

    /*
     * @brief Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName = "");

	/**
	 * @brief Finds the index of an ID in the vertexSet
	 * @param in It's the id of the vertex 
	 */ 
    inline ulli findVertexIdx(const ulli &in) const;

    /**
     * Before the execution of the proper algorithm of floyd warshall, it will check if matrix is not saved in a specific file
     * @param cityName Each city has a file called matrix_<cityName>_dest and matrix_<cityName>_pred
     */
    void handleFloydWarshall(const string& cityName);

    /**
     * @brief Application of the floydWarshall algorithm 
     */
    void floydWarshallShortestPath();
	
	/**
	 * @brief Get the path 
	 * @return Returns a vector containing the ID's of the vertexes to pass by 
	 **/ 
    vector<ulli> getFloydWarshallPath(const ulli &origin, const ulli &dest) const;

    /**
     * @brief Calculates the path given the points of interest using the greedy strategy
     * @param origin ID of the point where the person is 
     * @param poi list of the ID's of the points of interest, the first element of this array MUST be the origin itself
     * @param maxTime the maximum time the user has to spend doing the  touristic circuit
     * @return returns the path as an array of IDS
     */
    vector<ulli> trajectoryOrder(ulli origin, vector<POI*> &poi, double maxTime);

/*
     * @brief Auxiliar function to trajectoryPath. It gets the index of the next poi to be visited in the array setVertex
     * @param origin ID of the actual position
     * @param poi list of the POIS INDEX's which the user wants to visit
	 * @param visited BOOLEAN array containing the POI's already visited. The index = 0 is already visited by default, since it's the origin
	 * @param maxTime The maximum time the user has to spend in tourism
     * @return it returns next poi index to be visited. The index is relative to the array setVertex 
     */
    ulli nextPoi(const ulli &origin, vector<POI*> &poi, vector<bool> visited, double& maxTime);

    /**
     * @brief Function that treat data for the recursive function for the problem of traveling salesperson
     * @param origin Origin node
     * @param poi Vector of the points of interest (POI) to visit
     * @param time Total time that the person has to visit the points of interest
     * @return Returns the IDs of each vertex to be visit in order
     */
    vector<ulli> travelingSalesperson_preProcess(vector<POI> poi, double time );
    /**
     * @brief Recursive function to solve the traveling salesperson problem with dynamic programming approach
     * @param actualPoint The actual point of interest (POI) to be analysed
     * @param poi Vector containing all the POI's to be visited
     * @param available Algorithm feature: tells how many non visited POI's has left
     * @param minDistance Algorithm feature: min distance until now. The algorithm updates this variable
     * @param time Algorithm feature: the time that has left to visit the remaining features
     * @param nodes Algorithm features: number of nodes visited
     * @return Returns the ID's of each Vertex to be visited in order
     */
    vector<ulli> travelingSalesperson(lli actualPoint, vector<POI> poi, lli available, double & minDistance, double time, int& nodes);

};

#endif //GRAPH_H
