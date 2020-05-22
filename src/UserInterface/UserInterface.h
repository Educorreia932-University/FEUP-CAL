#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include "Graph/Graph.h"
#include "Storage/PoiStorage.h"
#include "Utils.h"
#include <iostream>
#include <locale>
#include <iomanip>
#include <map>
#include <graphviewer.h>

using namespace std;

class UserInterface {
    private:
        Graph* graph;
        vector<ulli> res1; // Nearest neighbor
        vector<ulli> res2; // Dynamic approach
        PoiStorage* poiStorage;

        // Settings
        bool showAll = false;
        double maxTime = INF;
        int animationDelay = 100;

        void showMainMenu();
        void showMap();
        void showRoute(GraphViewer* gv, vector<ulli> res, string color);
        void graphSelection();
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
