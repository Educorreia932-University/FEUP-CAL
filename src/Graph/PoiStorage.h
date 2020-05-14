#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Utils.h"
using namespace std;

#ifndef SRC_POISTORAGE_H
#define SRC_POISTORAGE_H


/**
 * @file PoiStorage
 * @brief This class is responsible for reading and store the touristic points of a city from a file which name is POI_<cityName>
 * @brief Also, the file must be in the format "poi_name, id"
 */
class PoiStorage {
    map<string, ulli> POIs;
    string cityName;
public:
    explicit PoiStorage(const string& cityName);
    bool readPois();
    map<string, ulli> getMap() const;
};


#endif //SRC_POISTORAGE_H
