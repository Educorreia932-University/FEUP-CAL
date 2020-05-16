#include "UserInterface.h"

#include <Graph/Graph.h>
#include <Graph/Vertex.h>
#include <graphviewer.h>


void clearScreen() {
#ifdef __unix__
    system("clear");
#endif

#ifdef _WIN32
    system("cls");
#endif
}

void UserInterface::showMainMenu() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Choose a tourist route         [1]" << endl
         << " Show the map                   [2]" << endl
         << " Adjust the settings            [3]"
         << endl    // Like disabling showing all of the edges and showing only those who are part of the route
         << " Exit                           [0]" << endl
         << endl;

}

void UserInterface::mainMenuSelection() {
    while (true) {
        showMainMenu();
        int option = readOption(0, 2);

        switch (option) {
            case 1:
                cout << "Calculating..." << endl;
                graph->handleFloydWarshall("PORTO");
                POIsSelection();
                break;
            case 2:
                showGraph(res);
                break;
            case 0:
                return;

        }
    }
}

POI* UserInterface::showPOIs() {
    clearScreen();
    int index = 0;

    //printing the point of interest
    cout << "\t POINTS OF INTEREST \t" << endl;
    cout << "============================================" << endl;
    for (pair<string, POI*>p : poiStorage->getMap()) {
        cout << left << setw(40) << p.first << "[" << index << "]" << endl;
        index++;
    }
    cout << left << setw(40) << "None" << "[" << index << "]" << endl;
    cout << endl;

    index = 0;
    int selected = readOption(0, poiStorage->getMap().size());

    for (pair<string, POI*> p : poiStorage->getMap()) {
        if (index == selected)
            return p.second;

        index++;
    }

    return nullptr;
}

void UserInterface::POIsSelection() {
    vector<POI* > toVisit = {};

    POI* selected;

    while ((selected = showPOIs()) != nullptr)
        toVisit.push_back(selected);

    //case there isn't sufficient pois to visit, i.e 1 or 2, the program will go back to the MainMenu
    if (toVisit.empty() || toVisit.size() == 1) return;

    getchar();

    res = graph->trajectoryOrder(toVisit[0]->getID(), toVisit);
    getchar(); //to be deleted later

}

UserInterface::UserInterface(Graph *graph, PoiStorage *poiStorage) : graph(graph), poiStorage(poiStorage) {}

int readOption(int min, unsigned int max) {
    int option;

    while (true) {
        cout << "Your option: ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << endl
                 << "Invalid input. Please try again:" << endl
                 << endl;
        }
    }
}

void UserInterface::showGraph(const vector<ulli> &res) {
    auto gv = new GraphViewer(900, 900, false);
#ifdef __unix__
    gv->setBackground("../../data/map.png");
#else
    gv->setBackground("../data/map.png");
#endif
    gv->createWindow(900, 900);

    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    gv->defineEdgeCurved(false);

    for (Vertex *v : graph->getVertexSet()) {
        gv->setVertexSize(v->getID(), 6);

        gv->addNode(
                v->getID(),
                (v->lon - min_lon) / (max_lon - min_lon) * 900,
                (v->lat - min_lat) / (max_lat - min_lat) * 900
        );
    }

    int edge_id = 0;

    for (Vertex *v : graph->getVertexSet()) {
        for (const Edge &w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);

            if (find(res.begin(), res.end(), v->getID()) != res.end()
                && find(res.begin(), res.end(), w.getDest()->getID()) != res.end()) {
                gv->setVertexColor(v->getID(), "red");
                gv->setVertexSize(v->getID(), 10);
                gv->setEdgeThickness(edge_id, 5);
            }

            edge_id++;
        }
    }

    gv->rearrange();
    cout << "Press a key to exit." << endl;
    getchar();

}





