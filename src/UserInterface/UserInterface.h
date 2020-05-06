#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include <iostream>
#include "Graph/Graph.h"

using namespace std;

class UserInterface {
    private:
        Graph* graph;
    public:
        UserInterface(Graph* graph);
        int showMainMenu();
        void mainMenuSelection(int selected);
        void showGraph();
};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
