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
    public:
        UserInterface(Graph* graph, PoiStorage * poiStorage);
        int showMainMenu();
        void mainMenuSelection(int selected);
        ulli showPOIs();
        void POIsSelection();
        void showGraph(const vector<ulli>& res);
};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
