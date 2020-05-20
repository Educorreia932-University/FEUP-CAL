
#include "PoiStorage.h"

PoiStorage::PoiStorage(const string& cityName){
    this->cityName = cityName;
}

bool PoiStorage::readPois() {
    string fileName = "../data/POI_" + cityName + ".txt";
    ifstream inFile(fileName.c_str());

    string line;
    string tmp;
    string name;        //stores temporally the name of a poi
    ulli id;            //stores temporally the id of a poi

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

        POIs.insert(pair<string, ulli>(name, id));
    }

    inFile.close();

    return true;
}

map<string, ulli> PoiStorage::getMap() const {
    return POIs;
}

string PoiStorage::findPOI(ulli id) const {
    for (const auto & POI : POIs)
        if (POI.second == id)
            return POI.first;

    return "";
}
