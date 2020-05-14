#ifndef SRC_FLOYDSTORAGE_H
#define SRC_FLOYDSTORAGE_H

#include <sstream>
#include <string>
#include <fstream>
#include "Graph.h"
using namespace std;

/**
 * @file FloydStorage.h
 * @brief this file is responsible to load the floydWarshall matrix case it exists. It has also a function which the graph should ask
 * to know if it's necessary to execute the floydWarshall algorithm
 */
class FloydStorage {
private:
    Graph* graph;
public:
    FloydStorage(Graph* graph);
    /**
     * Based on the existence of files matrix_<cityName>_dest and matrix_<cityName>_pred will return false (to execute floyd) or it will just load those files
     * @return true case exist the file, false otherwise
     */
    bool isToExecuteFloyd(const string& cityName);

    bool readDest(const string& cityName);
    bool readPred(const string& cityName);

    void storeDest(const unsigned int& size, const string& cityName);
    void storePred(const unsigned int& size, const string& cityName);
};


#endif //SRC_FLOYDSTORAGE_H
