#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "Utils.h"
#include "PoiStorage.h"

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
    vector<Vertex *> vertexSet;     /** vertex set */
    double **dist = nullptr; 		/** dist */
    int **pred = nullptr; 			/** path */ 

    friend class FloydStorage;
public:
    ~Graph();

    vector<Vertex *> getVertexSet();
    Vertex *findVertex(const ulli &in) const;
	/**
	 * @brief sorts the vertices according to the id's so that it can perform binary search to find a vertex Id 
	 */ 
    void sortVertexSet();                   
    bool addVertex(const ulli &in);
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
     * @return returns the path as an array of IDS
     */
    vector<ulli> trajectoryOrder(ulli origin, vector<POI*> &poi);

/*
     * @brief Auxiliar function to trajectoryPath. It gets the index of the next poi to be visited in the array setVertex
     * @param origin ID of the actual position
     * @param poi list of the POIS INDEX's which the user wants to visit
	 * @param visited BOOLEAN array containing the POI's already visited. The index = 0 is already visited by default, since it's the origin 
     * @return it returns next poi index to be visited. The index is relative to the array setVertex 
     */
    ulli nextPoi(const ulli &origin, vector<POI*> &poi, vector<bool> visited);

};

#endif //GRAPH_H
