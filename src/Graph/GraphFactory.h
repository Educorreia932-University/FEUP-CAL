#ifndef TOURMATEAPP_GRAPHFACTORY_H
#define TOURMATEAPP_GRAPHFACTORY_H

#include "Utils.h"
#include "Graph.h"
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;
/**
 * @file GraphFactory.h
 * @brief File containing the class GraphFactory responsible for creating the graph by reading information for files .csv
 * */ 

class GraphFactory {
    private:

    /**
     * @brief Open a file
     * @param filename Name of the file
     * @param inFile File stream
     */
        void openFile(const string& filename, ifstream& inFile);
    public:

    /**
     * @brief read all the vertex of a nodes_<city>.csv file
     * @param filename name of the file to read
     */
    void readVertex(const string& filename);
    /**
    * @brief Read all the edges of a file
    * @param Filename Name of the file
    */
    void readEdges(const string& filename);
    Graph graph;
    };


#endif //TOURMATEAPP_GRAPHFACTORY_H
