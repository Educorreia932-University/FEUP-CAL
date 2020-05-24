
#include "GraphFactory.h"
#include "Utils.h"

#define MEAN_VEL            40                 /*< the mean velocity in the graph*/

/**
 * @file GraphFactory.cpp
 * @brief file responsible for reading the edges and notes. With this it generates a new graph
 */

/**
 * @brief Open a file
 * @param filename Name of the file
 * @param inFile File stream
 */
void GraphFactory::openFile(const string &filename, ifstream &inFile) {
    inFile.open(filename.c_str());

    if (!inFile.is_open())
        ERRORS("Not possible to open file of vertex");
}

/**
 * @brief read all the vertex of a nodes_<city>.csv file
 * @param filename name of the file to read
 */
void GraphFactory::readVertex(const string &filename) {
    static const char TOKEN = ',';
    string line, tmp;
    ifstream inFile;
    openFile(filename, inFile);

    ulli id;
    double lon, lat;

    while (getline(inFile, line)) {
        istringstream is(line);

        getline(is, tmp, TOKEN);
        istringstream(tmp) >> id;                   /*<Set the ID */
        getline(is, tmp, TOKEN);
        istringstream(tmp) >> lon;                  /*<Set the longitude*/
        getline(is, tmp, TOKEN);
        istringstream(tmp) >> lat;                  /*<Set the latitude*/

        graph.addVertex(id, lon, lat);
    }
    graph.sortVertexSet();                          /*< Sort to be able to use binary search*/
}


/**
 * @brief Read all the edges of a file
 * @param Filename Name of the file
 */
void GraphFactory::readEdges(const string &filename) {
    string osmid, name, oneway, line, tmp;
    float maxspeed, length;
    ulli source, dest;
    const char TOKEN = ',';

    ifstream inFile;
    openFile(filename, inFile);
    getline(inFile, line);

    while (getline(inFile, line)) {
        istringstream is(line);

        getline(is, tmp, TOKEN);        /*< Set the source ID*/
        istringstream(tmp) >> source;
        getline(is, tmp, TOKEN);        /*< Set the destine ID*/
        istringstream(tmp) >> dest;
        getline(is, tmp, TOKEN);        /*< Set the max speed of the road*/
        istringstream(tmp) >> maxspeed;
        getline(is, tmp, TOKEN);        /*< Set the osmid of the edge*/
        istringstream(tmp) >> osmid;
        getline(is, tmp, TOKEN);        /*< Set the length of the road*/
        istringstream(tmp) >> length;
        getline(is, name, TOKEN);       /*< Set the name of the road*/
        getline(is, oneway, TOKEN);     /*< True case it's one way, false otherwise*/

        double weight = safeDivision(maxspeed, length, MEAN_VEL);
        graph.addEdge(source, dest, weight, name);

        if (oneway == "False") {
            graph.addEdge(dest, source, weight, name);
        }
        is.clear();
    }

}

