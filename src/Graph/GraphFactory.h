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
        void openFile(const string& filename, ifstream& inFile);
    public:
        void readVertex(const string& filename);
        void readEdges(const string& filename);
        Graph graph;
};


#endif //TOURMATEAPP_GRAPHFACTORY_H
