#include "graph.h"
#include <iostream>
#include <fstream>
#include <random>

Edge::Edge(Vertex * dest) {
    this->dest = dest;
    this->weight = 1;
}

void Edge::increment_weight() {
    weight++;
}

Vertex::Vertex(std::string value) {
    this->value = value;
}

void Vertex::add_edge(Vertex * vertex) {
    if (edges.find(vertex->value) == edges.end()) {
        edges[vertex->value] = new Edge(vertex);
    }
}
