#include "FloydStorage.h"

/**
 * @file FloydStorage.cpp
 * @brief this file is responsible to load the floydWarshall matrix case it exists. It has also a function which the graph should ask
 * to know if it's necessary to execute the floydWarshall algorithm
 */

/*TODO: fix the path for linux*/

bool FloydStorage::isToExecuteFloyd(const string &cityName) {
    //checks the files are available
    if (!readDest(cityName)) return true;
    return !readPred(cityName);

}

FloydStorage::FloydStorage(Graph *graph) {
    this->graph = graph;
}

bool FloydStorage::readDest(const string &cityName) {
    string tmp;
    string aux;
    unsigned int size = 0;
    const char TOKEN = ' ';

    ifstream inFile;
    string fileName = "../data/matrix_" + cityName + "_dest";
    inFile.open(fileName.c_str());

    if (!inFile.is_open()) return false;

    try {
        //get the size of the matrix
        getline(inFile, tmp);
        size = stoi(tmp);

        graph->dist = new double *[size];

        int line = 0;
        while (getline(inFile, tmp)) {
            istringstream is(tmp);
            graph->dist[line] = new double[size];
            for (int col = 0; col < size; col++) {
                getline(is, aux, TOKEN);
                istringstream(aux) >> graph->dist[line][col];
            }
            line++;
        }

        inFile.close();
    } catch (...) {
        ERROR("Error trying to read dest file");
        inFile.close();
        return false;
    }

    return true;
}

bool FloydStorage::readPred(const string &cityName) {
    string fileName = "../data/matrix_" + cityName + "_pred";
    string aux;
    string tmp;
    unsigned int size = 0;

    const char TOKEN = ' ';

    ifstream inFile;
    inFile.open(fileName.c_str());

    if (!inFile.is_open()) return false;

    try {
        //get the size of the matrix
        getline(inFile, tmp);
        size = stoi(tmp);

        graph->pred = new int *[size];
        int line = 0;
        graph->pred[line] = new int[size];
        while (getline(inFile, tmp)) {
            istringstream is(tmp);
            graph->pred[line] = new int[size];
            for (int col = 0; col < size; col++) {
                getline(is, aux, TOKEN);
                istringstream(aux) >> graph->pred[line][col];
            }
            line++;
        }
        inFile.close();
    } catch (...) {
        ERROR("Error trying to read pred file");
        inFile.close();
        return false;
    }

    return true;
}

void FloydStorage::storeDest(const unsigned int &size, const string &cityName) {
    string fileName = "../data/matrix_" + cityName + "_dest";
    ofstream distFile(fileName.c_str());
    //writes the dimension of the matrix
    distFile << size << endl;

    //writes the content of the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            distFile << graph->dist[i][j] << " ";
        }
        distFile << endl;
    }
    distFile.close();
}

void FloydStorage::storePred(const unsigned int &size, const string &cityName) {

    string fileName = "../data/matrix_" + cityName + "_pred";
    ofstream predFile(fileName.c_str());

    //writes the dimension of the matrix
    predFile << size << endl;

    //writes the content of the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            predFile << graph->pred[i][j] << " ";
        }
        predFile << endl;
    }
    predFile.close();
}

