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
         << " Adjust the settings            [3]"
         << endl    // Like disabling showing all of the edges and showing only those who are part of the route
         << " Set amount of time             [4]" << endl
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::mainMenuSelection() {
    bool calculated = false;
    vector<POI *> toVisit;

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

                    pauseInterface();

                    calculated = true;
                }

                toVisit = POIsSelection();


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

POI *UserInterface::showPOIs(vector<POI *> toVisit) {
    clearScreen();
    int index = 0;

    // Printing the points of interest
    cout << "\t POINTS OF INTEREST \t" << endl;
    cout << "============================================" << endl;

    // Iterate over POIs
    for (pair<string, POI *> p : poiStorage->getMap()) {
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
    POI *result = nullptr;

    do {
        int selected = readOption(0, poiStorage->getMap().size());

        for (pair<string, POI *> p : poiStorage->getMap()) {
            if (index == selected) {
                result = p.second;
                break;
            }

            index++;
        }
    } while (find(toVisit.begin(), toVisit.end(), result) != toVisit.end());

    return result;
}

void UserInterface::setAmountOfTime_Interface() {
    clearScreen();

    cout << "================== SET TIME ===================" << endl
         << "Set the amount of time you have to spend in minutes." << endl
         << "Negative numbers will be converted to positive: " << endl;
}

vector<POI *> UserInterface::POIsSelection() {
    vector<POI *> toVisit = {};
    vector<POI> TSP_toVisit = {};
    POI *selected;

    while ((selected = showPOIs(toVisit)) != nullptr) {
        toVisit.push_back(selected);
        TSP_toVisit.push_back(*selected);
    }

    // Case there isn't sufficient POIs to visit, i.e 1 or 2, the program will go back to the MainMenu
    if (toVisit.empty() || toVisit.size() == 1)
        return toVisit;

    double maxTimeGreedy = maxTime;
    double maxTimeDynamic = maxTime;

    res1 = graph->trajectoryOrder(toVisit[0]->getID(), toVisit, maxTimeGreedy);
    res2 = graph->travelingSalesperson_preProcess(TSP_toVisit, maxTimeDynamic);

    cout << "Greedy " << maxTimeGreedy << endl;
    cout << "Dynamic " << maxTimeDynamic << endl;

    pauseInterface();

    return toVisit;
}

void UserInterface::showSettings() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Show all?                      [1]" << endl
         << "     CURRENT: " << (showAll ? "YES" : "NO ") << endl
         << " Show ID?                       [2]" << endl
         << "     CURRENT: " << (showID ? "YES" : "NO ") << endl
         << " Change animation delay         [3]" << endl
         << "     CURRENT: " << animationDelay << " ms" << endl
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::settingsSelection() {
    while (true) {
        showSettings();

        int selected = readOption(0, 3);

        switch (selected) {
            case 1:
                showAll = !showAll;
                break;
            case 2:
                showID = !showID;
                break;
            case 3:
                cout << "Insert the new value for the delay, in miliseconds:" << endl;
                cin >> animationDelay;
                break;
            case 0:
                return;
        }
    }
}

vector<POI *> UserInterface::getToVisitPOIS(vector<ulli> res) {
    vector<POI *> aux = {};
    POI *poi;

    for (ulli id : res) {
        poi = poiStorage->findPOI(id);

        if (poi != nullptr)
            aux.push_back(poi);
    }

    vector<POI *> result = {};
    vector<ulli> alreadyAdded = {};

    result.push_back(aux[0]);
    alreadyAdded.push_back(aux[0]->getID());

    for (int i = 1; i < aux.size(); i++)
        if (find(alreadyAdded.begin(), alreadyAdded.end(), aux[i]->getID()) == alreadyAdded.end()) {
            result.push_back(aux[i]);
            alreadyAdded.push_back(aux[i]->getID());
        }

    return result;
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  showGraph
 *  Description: Function responsible to display the graph and custom settings of it 
 * =====================================================================================
 */
void UserInterface::showMap() {
    clearScreen();

    if (res1.empty()) {
        cout << "Choose a route first (Option [1] in the menu)" << endl
             << endl;
        pauseInterface();

        return;
    }

    cout << "Which algorithm do you want to see?" << endl
         << endl
         << "Greedy                          [1]" << endl
         << "Dynamic                         [2]" << endl
         << endl;

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
        showRoute(gv, res1, "RED", getToVisitPOIS(res1));

    else
        showRoute(gv, res2, "BLUE", getToVisitPOIS(res2));

    pauseInterface();

    // gv->closeWindow();
}

void UserInterface::showRoute(GraphViewer *gv, vector<ulli> res, string color, vector<POI *> toVisit) {
    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    // Add nodes
    for (Vertex *v : graph->getVertexSet()) {
        gv->setVertexSize(v->getID(), 9);
        gv->setVertexColor(v->getID(), "WHITE");

        if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end())) {
            gv->addNode(
                    v->getID(),
                    (v->lon - min_lon) / (max_lon - min_lon) * 900,
                    (v->lat - min_lat) / (max_lat - min_lat) * 900
            );

            if (showID)
                gv->setVertexLabel(v->getID(), to_string(v->getID()));
        }
    }

    int edge_id = 0;

    // Add edges
    for (Vertex *v : graph->getVertexSet())
        for (const Edge &w : v->getAdj()) {
            if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end() &&
                            find(res.begin(), res.end(), w.getDest()->getID()) != res.end()))
                gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);

            edge_id++;
        }

    gv->rearrange();

    animatePath(gv, res, color, res.front(), res.back());

    int path;

    while (true) {
        path = showPaths(toVisit);

        if (path == 0)
            return;

        animatePath(gv, res, color, toVisit[path - 1]->getID(), toVisit[path]->getID());
    };
}

int UserInterface::showPaths(vector<POI *> toVisit) {
    clearScreen();

    cout << "Which path do you want to see?" << endl
         << endl;

    for (int i = 0; i < toVisit.size() - 1; i++) {
        cout << left << setw(40) << (toVisit[i]->getName() + " -> " + toVisit[i + 1]->getName());
        cout << "[" << i + 1 << "]" << endl;
    }

    cout << "Go back                                 [0]" << endl
         << endl;

    int selected = readOption(0, toVisit.size() - 1);

    return selected;
}

void UserInterface::animatePath(GraphViewer *gv, vector<ulli> res, string color, ulli begin, ulli end) {
    vector<ulli> POI_route;
    bool begun = false;

    for (ulli id : res) {
        if (begun) {
            gv->setVertexSize(id, 11);
            gv->setVertexColor(id, color);

            POI_route.push_back(id);

#ifdef __unix__
            usleep(animationDelay);
#else
            Sleep(animationDelay);
#endif

            gv->rearrange();
        }

        // Reached a POI
        if (poiStorage->findPOI(id) != nullptr) {
            gv->setVertexSize(id, 17);

            for (ulli id : POI_route) {
                gv->setVertexColor(id, "YELLOW");
                POI_route.clear();
            }

            if (id == begin) {
                begun = true;
                gv->setVertexColor(id, color);
                POI_route.push_back(id);
            }

            if (id == end)
                break;
        }
    }
}

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

void pauseInterface() {
    cout << "Press any key to continue ...";
    cin.get();
}

