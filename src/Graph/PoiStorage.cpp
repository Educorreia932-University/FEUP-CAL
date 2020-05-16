
#include "PoiStorage.h"

PoiStorage::PoiStorage(const string& cityName){
    this->cityName = cityName;
}

bool PoiStorage::readPois() {
    string fileName = "../data/POI_" + cityName + ".txt";
    ifstream inFile(fileName.c_str());

    string line;
    string tmp;
    string name;                //stores temporally the name of a poi
    ulli id, time;              //stores temporally the id of a poi and the time in minutes

    const char TOKEN = ',';

    if (!inFile.is_open()) {
        inFile.close();
        return false;
    }

    while (getline(inFile, line)) {
        stringstream is(line);


        getline(is, name, TOKEN);
        getline(is, tmp, TOKEN);
        stringstream(tmp) >> id;
        getline(is, tmp, TOKEN);
        stringstream(tmp) >> time;


        POIs.insert(pair<string, POI*>(name, new POI(id, name, time)));


    }

    inFile.close();

    return true;
}

map<string, POI*> PoiStorage::getMap() const {
    return POIs;
}