#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include "Graph/Graph.h"
#include "Graph/PoiStorage.h"
#include "Utils.h"
#include <iostream>
#include <locale>
#include <iomanip>
#include <map>

using namespace std;

class UserInterface {
    private:
        Graph* graph;
        vector<ulli> res;
        PoiStorage* poiStorage;
        bool showAll = false;
        double maxTime = INF;
        void settingsSelection();
    public:
        UserInterface(Graph* graph, PoiStorage * poiStorage);
        void showMainMenu();
        void mainMenuSelection();
        POI* showPOIs();
        void POIsSelection();
        void showGraph(const vector<ulli>& res);
        /**
         * @brief Visual menu for the user set the amount of time it has to spend making tourism
         */
        void setAmountOfTime_Interface();

};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
