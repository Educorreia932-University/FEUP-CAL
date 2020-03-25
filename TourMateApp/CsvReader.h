#ifndef TOURMATEAPP_CSVREADER_H
#define TOURMATEAPP_CSVREADER_H

#include <string>
#include "Graph.h"
#include <fstream>

class CsvReader {
protected:
    CsvReader()= default;
    virtual void read(std::string file, Graph* graph) = 0;
};

class NodeRead: CsvReader{
public:
    void read(std::string file, Graph *graph);

};

class EdgeRead: CsvReader{
public:
    void read(std::string file, Graph *graph);
};

#endif //TOURMATEAPP_CSVREADER_H
