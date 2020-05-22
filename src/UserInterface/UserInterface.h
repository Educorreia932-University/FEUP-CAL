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

        // Settings
        bool showAll = false;
        double maxTime = INF;


        void showMainMenu();
        void showGraph(const vector<ulli>& res);
        POI* showPOIs(vector<POI*> toVisit);
        void POIsSelection();
        void showSettings();
        void settingsSelection();
    public:
        UserInterface(Graph* graph, PoiStorage *poiStorage);
        void mainMenuSelection();
        /**
         * @brief Visual menu for the user set the amount of time it has to spend making tourism
         */
        void setAmountOfTime_Interface();


};

int readOption(int min, unsigned int max);

void pause();

#endif //TOURMATEAPP_USERINTERFACE_H
