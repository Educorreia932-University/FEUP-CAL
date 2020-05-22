#include "UserInterface.h"

#include <graphviewer.h>
#include <chrono>

void clearScreen() {
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif
}

UserInterface::UserInterface(Graph *graph, PoiStorage *poiStorage) : graph(graph), poiStorage(poiStorage) {}
 
/*
 * ===  FUNCTIONALITY  ======================================================================
 *         Name:  DisplayMenu
 *  Description:  From here on we have the functionalities to display the main menu 
 * ==========================================================================================
 */
void UserInterface::showMainMenu() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Choose a tourist route         [1]" << endl
         << " Show the map                   [2]" << endl
         << " Adjust the settings            [3]" << endl    // Like disabling showing all of the edges and showing only those who are part of the route
         << " Set amount of time             [4]" << endl
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::mainMenuSelection() {
    bool calculated = false;

    while (true) {
        chrono::steady_clock::time_point begin;
        chrono::steady_clock::time_point end;

        showMainMenu();
        int option = readOption(0, 4);

        switch (option) {
            case 1:
                if (!calculated) {
                    cout << endl
                         << "Calculating..." << endl
                         << endl;

                    begin = chrono::steady_clock::now();

                    graph->handleFloydWarshall("PORTO");

                    end = chrono::steady_clock::now();

                    cout << "The algorithm was completed in "
                         << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0
                         << " seconds."
                         << endl
                         << endl;

                    pause();

                    calculated = true;
                }

                POIsSelection();

                break;
            case 2:
                cout << endl
                     << "Loading..."
                     << endl;
                showMap();
                break;
            case 3:
                settingsSelection();
                break;
            case 4:
                setAmountOfTime_Interface();
                maxTime = abs(checkNumber());
                break;
            default:
                return;
        }
    }
}

POI* UserInterface::showPOIs(vector<POI*> toVisit) {
    clearScreen();
    int index = 0;

    // Printing the points of interest
    cout << "\t POINTS OF INTEREST \t" << endl;
    cout << "============================================" << endl;

    // Iterate over POIs
    for (pair<string, POI*> p : poiStorage->getMap()) {
        cout << left << setw(40) << p.first;

        // POI is already selected
        if (find(toVisit.begin(), toVisit.end(), p.second) != toVisit.end())
            cout << "[SELECTED]" << endl;

        else
            cout << "[" << index << "]" << endl;

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

void UserInterface::setAmountOfTime_Interface(){
    clearScreen();

    cout << "================== SET TIME ===================" << endl
         << "Set the amount of time you have to spend in minutes." << endl
         << "Negative numbers will be converted to positive: " << endl;
}

void UserInterface::POIsSelection() {
    vector<POI *> toVisit = {};
    vector<POI> TSP_toVisit = {};
    POI *selected;

    while ((selected = showPOIs(toVisit)) != nullptr) {
        toVisit.push_back(selected);
        TSP_toVisit.push_back(*selected);
    }

    // Case there isn't sufficient POIs to visit, i.e 1 or 2, the program will go back to the MainMenu
    if (toVisit.empty() || toVisit.size() == 1) return;

    res1 = graph->trajectoryOrder(toVisit[0]->getID(), toVisit, maxTime);
    res2 = graph->travelingSalesperson_preProcess(0, TSP_toVisit, maxTime);
}

void UserInterface::showSettings() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Show all? " << (showAll? "YES" : "NO ") <<  "                  [1]" << endl
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::settingsSelection() {
    while (true) {
        showSettings();

        int selected = readOption(0, 1);

        switch (selected) {
            case 1:
                showAll = !showAll;
                break;
            case 0:
                return;
        }
    }
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  showGraph
 *  Description: Function responsible to display the graph and custom settings of it 
 * =====================================================================================
 */
void UserInterface::showMap() {
    clearScreen();

    cout << "Which algorithm do you want to see?" << endl
         << "Greedy                          [1]" << endl
         << "Dynamic                         [2]" << endl;

    int selected;

    selected = readOption(1, 2);

    auto gv = new GraphViewer(900, 900, false);

    #ifdef __unix__
        gv->setBackground("../../data/map.png");
    #else
        gv->setBackground("../data/map.png");
    #endif

    gv->createWindow(900, 900);

    gv->defineEdgeCurved(false);

    if (selected == 1)
        showRoute(gv, res1, "RED");

    else
        showRoute(gv, res2, "BLUE");

    pause();

    // gv->closeWindow();
}

void UserInterface::showRoute(GraphViewer* gv, vector<ulli> res, string color) {
    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    // Add nodes
    for (Vertex* v : graph->getVertexSet()) {
        gv->setVertexSize(v->getID(), 9);
        gv->setVertexColor(v->getID(), "YELLOW");

        if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end())) {
            gv->addNode(
                    v->getID(),
                    (v->lon - min_lon) / (max_lon - min_lon) * 900,
                    (v->lat - min_lat) / (max_lat - min_lat) * 900
            );

            string poi_name;
        }
    }

    int edge_id = 0;

    // Add edges
    for (Vertex* v : graph->getVertexSet())
        for (const Edge &w : v->getAdj()) {
            if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end() && find(res.begin(), res.end(), w.getDest()->getID()) != res.end()))
                gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);

            edge_id++;
        }

    // Customize
    for (ulli id : res) {
        gv->setVertexSize(id, 11);
        gv->setVertexColor(id, color);

        if (!poiStorage->findPOI(id).empty()) {
            gv->setVertexSize(id, 17);
        }

        Sleep(100);

        gv->rearrange();
    }

}

void UserInterface::graphSelection() {
    
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

void pause() {
    cout << "Press any key to continue ...";
    cin.get();
}

