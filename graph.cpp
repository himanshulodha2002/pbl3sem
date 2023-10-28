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

void Vertex::increment_edge(Vertex * vertex) {
    add_edge(vertex);
    edges[vertex->value]->increment_weight();
}

void Vertex::calculate_probabilities() {
    int sum = 0;
    for (auto const& pair: edges) {
        sum += pair.second->weight;
    }

    for (auto const& pair: edges) {
        double probability = (double) pair.second->weight / sum;
        probabilities[pair.first] = probability;
    }
}