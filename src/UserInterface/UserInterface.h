#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include <iostream>
#include "Graph/Graph.h"

using namespace std;

class UserInterface {
    private:
        Graph* graph;
        vector<ulli> res;
    public:
        UserInterface(Graph* graph);
        int showMainMenu();
        void mainMenuSelection(int selected);
        vector<ulli> showPOIs();
        void POIsSelection(vector<ulli> POIs);
        void showGraph(const vector<ulli>& res);
};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
