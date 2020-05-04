#include "Edge.h"

Edge::Edge(Vertex* d, double w): dest(d), weight(w) {}

Edge::Edge(Vertex* d, double w, const std::string& sn): dest(d), weight(w), streetName(sn) {}
