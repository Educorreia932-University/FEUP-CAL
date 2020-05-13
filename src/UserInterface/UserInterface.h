#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include "Graph/Graph.h"

#include <iostream>
#include <map>

using namespace std;

class UserInterface {
    private:
        Graph* graph;
        vector<ulli> res;
        map<string, ulli> POIs;
    public:
        UserInterface(Graph* graph);
        int showMainMenu();
        void mainMenuSelection(int selected);
        ulli showPOIs();
        void POIsSelection();
        void showGraph(const vector<ulli>& res);
};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
