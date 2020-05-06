
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "GraphFactory.h"

using namespace std;

int main() {
    UserInterface ui;
    //ui.mainMenuSelection(ui.showMainMenu());
    auto *g = new GraphFactory();
    g->readVertex("../../MapExtraction/nodes.csv");
    return 0;
}
