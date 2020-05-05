#ifndef TOURMATEAPP_GRAPHFACTORY_H
#define TOURMATEAPP_GRAPHFACTORY_H

#include "utils.h"
#include "Graph.h"
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

class GraphFactory {
    Graph graph;
public:
    void openFile(const string& filename, ifstream& inFile);
    void readVertex(const string& filename);
    void readEdges(const string& filename);
};


#endif //TOURMATEAPP_GRAPHFACTORY_H
