#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Utils.h"
using namespace std;

#ifndef SRC_POISTORAGE_H
#define SRC_POISTORAGE_H

class POI;
/**
 * @file PoiStorage
 * @brief This file contains the classes: PoiStorage and POI
 **/

/*
 * @brief This class is responsible for reading and store the touristic points of a city from a file which name is POI_<cityName>
 * @brief Also, the file must be in the format "poi_name, id"
 */

class PoiStorage {

    map<string, POI*> POIs;     /*< map containing the name of the points of interest and its ID*/
    string cityName;
public:
    explicit PoiStorage(const string& cityName);
	/*
	 * @brief It reads the file containing the pois
	 */
    bool readPois();
    map<string, POI*> getMap() const;
    POI * findPOI(ulli id) const;
};


/**
 * @brief This is a data class responsible for storing the POIS information
 */
class POI {
    private:
        ulli id;
        string name;        /*<Name of the POI*/
        ulli time;          /*<Time that a person spends in a POI*/
        ulli index;         /*<position of the poi in the setVertex => to be used at trajectory order*/
        bool visited;       /*<Variable used in the dynamic programming approach*/
    public:
        POI(ulli id, const string& name, ulli time): id(id), name(name), time(time){index = 0;};
        void setVisited(bool visited){this->visited = visited; }
        bool getVisited(){return visited;}
        ulli getID() {return id;}
        string getName() const {return name;} ;
        ulli getTime(){return time;}
        ulli getIndex(){return index;}
        void setIndex(ulli index){this->index = index;}
};

#endif //SRC_POISTORAGE_H
