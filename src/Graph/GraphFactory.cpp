
#include "GraphFactory.h"
#include "Utils.h"

#define MEAN_VEL 40 /** the mean velocity in the graph*/

void GraphFactory::openFile(const string &filename, ifstream &inFile) {
    inFile.open(filename.c_str());

    if (!inFile.is_open())
        ERROR("Not possible to open file of vertex");
}

void GraphFactory::readVertex(const string &filename) {
    ifstream inFile;
    ulli id;
    openFile(filename, inFile);

    while (inFile >> id)
        graph.addVertex(id);
}

void GraphFactory::readEdges(const string &filename) {
    string osmid, name, oneway, line, tmp;
    float maxspeed, length;
    ulli source, dest;
    char token = ',';

    ifstream inFile;
    openFile(filename, inFile);
    getline(inFile, line);

    while (getline(inFile, line)) {
        istringstream is(line);

        getline(is, tmp, token);        //source id
        istringstream(tmp) >> source;
        getline(is, tmp, token);        //destine id
        istringstream(tmp) >> dest;
        getline(is, tmp, token);        //maxspeed in the road
        istringstream(tmp) >> maxspeed;
        getline(is, tmp, token);        //osmid
        istringstream(tmp) >> osmid;
        getline(is, tmp, token);        //lenght of the road
        istringstream(tmp) >> length;
        getline(is, name, token);       //name of the road
        getline(is, oneway, token);     //"True" case it's one way, "False" otherwise

        double weight = safeDivision(length, maxspeed, MEAN_VEL);
        graph.addEdge(source, dest, weight, name);

        if (oneway == "False") {
            graph.addEdge(dest, source, weight, name);
        }
        // cout << source << " " << dest << endl;
        is.clear();
    }
}