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

int UserInterface::showMainMenu() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Choose a tourist route." << endl
         << "2) Show the graph." << endl
         << "3) Adjust the settings." << endl // Like disabling showing all of the edges and showing only those who are part of the route
         << "0) Exit" << endl
         << endl;

    return readOption(0, 2);
}

void UserInterface::mainMenuSelection(int selected) {
    switch (selected) {
        case 1:
            POIs.insert(pair<string, ulli>("Estação", 5118553704));
            POIs.insert(pair<string, ulli>("McDonald's", 3130312339));
            POIs.insert(pair<string, ulli>("Aliados", 7134786669));
            POIs.insert(pair<string, ulli>("Lello", 7134805724));
            POIs.insert(pair<string, ulli>("Bolsa", 2356505225));
            POIs.insert(pair<string, ulli>("Bolhão", 4356494336));

            cout << "Calculating...";

            graph->handleFloydWarshall("PORTO");

            POIsSelection();

            break;
        case 2:
            showGraph(res);
            break;
        case 0:
            return;
    }

    mainMenuSelection(showMainMenu());
}

ulli UserInterface::showPOIs() {
    clearScreen();
    int index = 0;

    for (pair<string, ulli> p : POIs) {
        cout << index << ") " << p.first << " " << p.second << endl;
        index++;
    }

    cout << index << ") " << "None." << endl;

    index = 0;
    int selected = readOption(0, POIs.size());

    for (pair<string, ulli> p : POIs) {
        if (index == selected)
            return p.second;

        index++;
    }

    return -1;
}

void UserInterface::POIsSelection() {
    vector<ulli> toVisit = {};

    ulli selected;

    while ((selected = showPOIs()) != -1)
        toVisit.push_back(selected);

    cout << toVisit[0] << endl;
    cout << toVisit[1] << endl;
    getchar();

    res = graph->getFloydWarshallPath(toVisit[0], toVisit[1]);
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

void UserInterface::showGraph(const vector<ulli>& res) {
    auto gv = new GraphViewer(900, 900, false);
    gv->setBackground("../data/map.png");
    gv->createWindow(900, 900);

    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    gv->defineEdgeCurved(false);

    for (Vertex* v : graph->getVertexSet()) {
        gv->setVertexSize(v->getID(), 6);

        gv->addNode(
                v->getID(),
                (v->lon - min_lon) / (max_lon - min_lon) * 900,
                (v->lat - min_lat) / (max_lat - min_lat) * 900
        );
    }

    int edge_id = 0;

    for (Vertex* v : graph->getVertexSet()) {
        for (const Edge& w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);

            if (find(res.begin(), res.end(), v->getID()) != res.end()
            && find(res.begin(), res.end(), w.getDest()->getID()) != res.end() ) {
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

    gv->closeWindow();
}





