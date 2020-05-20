#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include "Graph/Graph.h"
#include "Graph/PoiStorage.h"
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

        void showMainMenu();
        void showGraph(const vector<ulli>& res);
        ulli showPOIs(vector<ulli> toVisit);
        void POIsSelection();
        void showSettings();
        void settingsSelection();
    public:
        UserInterface(Graph* graph, PoiStorage *poiStorage);
        void mainMenuSelection();
};

int readOption(int min, unsigned int max);

void pause();

#endif //TOURMATEAPP_USERINTERFACE_H
