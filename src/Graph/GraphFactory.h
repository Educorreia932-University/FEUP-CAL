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

class GraphFactory {
    private:
        void openFile(const string& filename, ifstream& inFile);
    public:
        void readVertex(const string& filename);
        void readEdges(const string& filename);
        Graph graph;
};


#endif //TOURMATEAPP_GRAPHFACTORY_H
