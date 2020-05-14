#ifndef SRC_FLOYDSTORAGE_H
#define SRC_FLOYDSTORAGE_H

#include <string>

using namespace std;

/**
 * @file FloydStorage.h
 * @brief this file is responsible to load the floydWarshall matrix case it exists. It has also a function which the graph should ask
 * to know if it's necessary to execute the floydWarshall algorithm
 */
class floydStorage {

private:
    bool openFile(const string& filename, ifstream& inFile);
public:
    /**
     * Based on the existence of files matrix_<cityName>_dest and matrix_<cityName>_pred
     * @return true case exist the file, false otherwise
     */
    bool isToExecuteFloyd();
    void readDest(int size);
    void readPred(int size);

    void storeDest(int size);
    void storePred(int size);
};


#endif //SRC_FLOYDSTORAGE_H
