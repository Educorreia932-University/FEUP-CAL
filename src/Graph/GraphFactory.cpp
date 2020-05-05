
#include "GraphFactory.h"
#include "Utils.h"

#define MEAN_VEL 40 /** the mean velocity in the graph*/

void GraphFactory::openFile(const string &filename, ifstream &inFile) {
    inFile.open(filename.c_str());

    if (!inFile.is_open())
        ERROR("Not possible to open file of vertex");
}

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
        istringstream(tmp) >> id;
        getline(is, tmp, TOKEN);
        istringstream(tmp) >> lon;
        getline(is, tmp, TOKEN);
        istringstream(tmp) >> lat;

        graph.addVertex(id, lon, lat);
    }
}

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

        getline(is, tmp, TOKEN);        //source id
        istringstream(tmp) >> source;
        getline(is, tmp, TOKEN);        //destine id
        istringstream(tmp) >> dest;
        getline(is, tmp, TOKEN);        //maxspeed in the road
        istringstream(tmp) >> maxspeed;
        getline(is, tmp, TOKEN);        //osmid
        istringstream(tmp) >> osmid;
        getline(is, tmp, TOKEN);        //lenght of the road
        istringstream(tmp) >> length;
        getline(is, name, TOKEN);       //name of the road
        getline(is, oneway, TOKEN);     //"True" case it's one way, "False" otherwise

        double weight = safeDivision(length, maxspeed, MEAN_VEL);
        graph.addEdge(source, dest, weight, name);

        if (oneway == "False") {
            graph.addEdge(dest, source, weight, name);
        }
        // cout << source << " " << dest << endl;
        is.clear();
    }
}