#include <Graph/Graph.h>
#include <Graph/Vertex.h>
#include <graphviewer.h>
#include "UserInterface.h"

void clearScreen() {
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif
}

int UserInterface::showMainMenu() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Show the graph." << endl
         << "0) Exit" << endl
         << endl;

    return readOption(0, 1);
}

void UserInterface::mainMenuSelection(int selected) {
    switch (selected) {
        case 1:
            showGraph();
            break;
        case 0:
            return;
    }

    mainMenuSelection(showMainMenu());
}

UserInterface::UserInterface(Graph* graph): graph(graph) {

}

int readOption(int min, unsigned int max) {
    int option;

    while (true) {
        cout << "Your option: ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        }

        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << endl
                 << "Invalid input. Please try again:" << endl
                 << endl;
        }
    }
}

void UserInterface::showGraph() {
    auto gv = new GraphViewer(900, 900, false);
    gv->setBackground("../data/map.png");
    gv->createWindow(900, 900);

    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    gv->defineEdgeCurved(false);

    for (Capsule c : graph->getVertexSet()) {
        Vertex* v = c.getVertex();

        gv->addNode(
                v->getID(),
                (v->lon - min_lon) / (max_lon - min_lon) * 900,
                (v->lat - min_lat) / (max_lat - min_lat) * 900
        );

        gv->setVertexSize(v->getID(), 6);
    }

    int edge_id = 0;

    for (Capsule c : graph->getVertexSet()) {
        Vertex* v = c.getVertex();

        for (const Edge& w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);
            edge_id++;
        }
    }

    gv->rearrange();

    cout << "Press a key to exit." << endl;
    getchar();

    gv->closeWindow();
}



