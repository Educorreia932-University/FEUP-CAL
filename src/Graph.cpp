#include "Graph.h"

#define INF std::numeric_limits<double>::max()

int Graph::getNumVertex() const {
    return vertexSet.size();
}

tabHVertex Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(const ulli &in) const {
    auto *v = new Vertex(in);
    Capsule cv(v);
    auto iterator = vertexSet.find(cv);
    if (iterator == vertexSet.end())
        return nullptr;
    return iterator->getVertex();
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const Capsule &in) {
    if (vertexSet.find(in) != vertexSet.end())
        return false;

    vertexSet.insert(in);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->addEdge(v2, w, streetName);

    return true;
}

int Graph::findVertexIdx(const int &in) const {
    int i = 0;
    for (auto iter : vertexSet) {
        if (iter.getVertex()->id == in)
            return i;
        i++;
    }
    return -1;
}

int Graph::getElement(int pos) const {
    auto iter = vertexSet.begin();
    for (int i = 0; i < pos; ++i)
        iter++;
    return iter->getVertex()->id;
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
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}

void Graph::floydWarshallShortestPath() {
    int n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double *[n];
    P = new int *[n];
    int i = 0;
    for (auto iter : vertexSet) {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j ? 0 : INF;
            P[i][j] = -1;
        }
        for (const auto &e : iter.getVertex()->adj) {
            int j = findVertexIdx(e.dest->id);
            W[i][j] = e.weight;
            P[i][j] = i;
        }
        i++;
    }
    for (int k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (unsigned j = 0; j < n; j++) {
                if (W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                double val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }
}

vector<int> Graph::getFloydWarshallPath(const ulli &origin, const ulli &dest) const {
    vector<int> res;
    int i = findVertexIdx(origin);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for (; j != -1; j = P[i][j])
        res.push_back(getElement(j));
    reverse(res.begin(), res.end());
    return res;
}
