#include "Graph.h"
#include "Storage/FloydStorage.h"


/**
 * @file Graph.cpp
 * @brief this file contains the implementation of graph functions and algorithms described in Graph.h
 */
Vertex *Graph::findVertex(const ulli &in) const {
    for (auto v: vertexSet)
        if (v->id == in)
            return v;
    return NULL;
}

bool Graph::addVertex(const ulli &in) {
    if (findVertex(in) != nullptr)
        return false;

    vertexSet.push_back(new Vertex(in));

    return true;
}

bool Graph::addVertex(const ulli &in, const double lon, const double lat) {
    if (findVertex(in) != nullptr)
        return false;

    vertexSet.push_back(new Vertex(in, lon, lat));

    return true;
}


bool Graph::addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->addEdge(v2, w, streetName);

    return true;
}


inline ulli Graph::findVertexIdx(const ulli &in) const {
    int end = vertexSet.size() ;
    int begin = 0 ;
    while (end >= begin) {
        int mid = begin + (end- begin) / 2;
        if (in > vertexSet[mid]->getID()  ) begin = mid +1 ;
        else if (in < vertexSet[mid]->getID() ) end = mid - 1;
        else return mid;
    }

    return -1;
}

template<class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

Graph::~Graph() {
    deleteMatrix(dist, vertexSet.size());
    deleteMatrix(pred, vertexSet.size());
}

void Graph::sortVertexSet() {
    sort(this->vertexSet.begin(), this->vertexSet.end(), [](Vertex* v1, Vertex* v2){
        return v1->getID() < v2->getID();
    });
}

/* 
 * ===  ALGORITHM ======================================================================
 *         Name:  FloydWarshall
 *  Description:  From here on we have the Floyd Warshall algorithm implementation 
 * =====================================================================================
 */
void Graph::handleFloydWarshall(const string& cityName) {
    auto *fs = new FloydStorage(this);

    if (this->dist != nullptr && this->pred != nullptr)
        return;

    if (fs->isToExecuteFloyd(cityName)) {
        floydWarshallShortestPath();
        unsigned int size = vertexSet.size();       //to avoid calculating the size twice
        fs->storePred(size, cityName);
        fs->storeDest(size, cityName);
    }
}

void Graph::floydWarshallShortestPath() {
    int n = vertexSet.size();

    deleteMatrix(dist, n);
    deleteMatrix(pred, n);

    dist = new double *[n];
    pred = new int *[n];

    for (int i = 0; i < n; i++) {
        dist[i] = new double[n];
        pred[i] = new int[n];

        for (unsigned j = 0; j < n; j++) {
            dist[i][j] = i == j ? 0 : INF;
            pred[i][j] = -1;
        }

        for (const auto &e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->id);
            dist[i][j] = e.weight;
            pred[i][j] = i;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (unsigned j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF)
                    continue;               // avoid overflow

                double val = dist[i][k] + dist[k][j];

                if (val < dist[i][j]) {
                    dist[i][j] = val;
                    pred[i][j] = pred[k][j];
                }
            }
}

vector<ulli> Graph::getFloydWarshallPath(const ulli &origin, const ulli &dest) const {
    vector<ulli> res;
    int i = findVertexIdx(origin);
    int j = findVertexIdx(dest);

    if (i == -1 || j == -1 || dist[i][j] == INF) // missing or disconnected
        return res;

    for (; j != -1; j = pred[i][j])
        res.push_back(vertexSet[j]->id);

    reverse(res.begin(), res.end());

    res.push_back(dest);

    return res;
}

/* 
 * ===  ALGORITHM ======================================================================
 *         Name:  GreedyApproach
 *  Description:  From here on is implemented the greedy approach to find out what is 
 				  the next Point of Interest (POI) to visit. Basically is chosen the 
				  next nearest POI. The iteration stops travelling to the next POI 
				  exceeds the maxTime given by the user. 
 * =====================================================================================
 */
vector<ulli> Graph::trajectoryOrder(ulli origin, vector<POI*> &poi, double maxTime) {
    vector<ulli> order = {};
    vector<bool> visited(vertexSet.size());
    visited[findVertexIdx(origin)] = true;
    double  initialTime = maxTime - poi[0]->getTime();
    ulli idNext;

    //the poi vector must contain the INDEX of the POIS in the vertexSet => to accelerate the process
    origin = findVertexIdx(origin);
    for (int i = 0; i < poi.size(); i++){
        poi[i]->setIndex(findVertexIdx(poi[i]->getID()));
    }


    for (int i = 1; i < poi.size(); i++) {
        idNext = nextPoi(origin, poi, visited, initialTime);                //get the id of the next poi to be visited
        if (idNext == 0) return order;                                          // no sufficient time to visit all pois
        vector<ulli> floydPath = this->getFloydWarshallPath(vertexSet[origin]->getID(), vertexSet[idNext]->getID());    //path between these two points

        order.insert(order.end(), floydPath.begin(), floydPath.end());          //join the actual path two the vector
        visited[idNext] = true;
        origin = idNext;                                                        //the new vertex now is the origin
    }

    return order;
}


ulli Graph::nextPoi(const ulli &origin, vector<POI *> &poi, vector<bool> visited, double& maxTime) {
    int actualIndex = origin;
    double minWeight = INF;
    ulli selectedPoiIndex = -1;

    for (int i = 0; i < poi.size(); i++) {
        ulli nextVertex = poi[i]->getIndex();

        //the poi[i]->getTime() is the time that the user will spend at the place
        if (dist[actualIndex][nextVertex]+poi[i]->getTime() < minWeight && visited[nextVertex] == false) {
            minWeight = dist[actualIndex][nextVertex] + poi[i]->getTime();
            selectedPoiIndex = nextVertex;
        }

    }
    //update the time the person has to spend
    maxTime -= minWeight;
    if (maxTime == 0) maxTime = -1;                 //cannot be 0
    if (maxTime < 0) return 0;


    return selectedPoiIndex;
}

vector<Vertex *> Graph::getVertexSet() {
    return vertexSet;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  DynamicApproach
 *  Description:  From here on is implemented the algorithm for solving the Traveling
				  Salesperson problem (TSP) by using a dynamic programing approach.
 * =====================================================================================
 */

//TODO: apagar origin
vector<ulli> Graph::travelingSalesperson_preProcess(const ulli &origin, vector<POI> poi, double time) {
    for (int i = 0 ; i < poi.size(); i++){
        poi[i].setVisited(false);
        poi[i].setIndex(findVertexIdx(poi[i].getID()));
    }
    double minDistance = 0;
    int nodes = 1;
    vector<ulli> resposta = travelingSalesperson( 0, poi, poi.size(), minDistance, time - poi[0].getTime(), nodes );
    return resposta;
}

vector<ulli> Graph::travelingSalesperson(lli actualPoint, vector<POI> poi, lli available,
                                         double &minDistance, double time, int& nodes) {

    vector<ulli> answer;
    poi[actualPoint].setVisited(true);

    /*<Case there is no time to visit this poi*/
    if (time < 0) {
        minDistance = INF;
        return {};
    }

    nodes ++;
    /*<Case all the vertices from poi has been visited*/
    if (available == 1) {
        minDistance = poi[actualPoint].getTime();
        return {};
    }

    lli nextPOI = -1;


    for (int i = 0 ; i < poi.size(); i++){
        if (!poi[i].getVisited()){
            double actualDistance = 0;
            int auxNodes = nodes;

            /*<Value to be parsed to the next poi = actualTime - distance between next and actual*/
            double auxTime = time - dist[poi[actualPoint].getIndex()][poi[i].getIndex()] - poi[i].getTime();
            vector<ulli> tempVector = travelingSalesperson(i, poi, available-1, actualDistance, auxTime, auxNodes);

            /*<Update the actual distance*/
            lli source = poi[actualPoint].getIndex();
            lli dest = poi[i].getIndex();
            actualDistance += dist[source][dest];

            /*<Update the min distance*/
            /*<The auxNodes guarantee that we have the max number of pois visited and the distance guarantees the min time*/
            if ((minDistance > actualDistance && auxNodes > nodes) || auxNodes > nodes){
                answer = tempVector;
                minDistance = actualDistance;
                nodes = auxNodes;
                nextPOI = i;
            }
        }
    }
    if (nextPOI != -1) {
        vector<ulli> floydPath = getFloydWarshallPath(poi[actualPoint].getID(), poi[nextPOI].getID());
        floydPath.insert(floydPath.end(), answer.begin(), answer.end());
        return floydPath;
    }
    else{
        return {};
    }


}


