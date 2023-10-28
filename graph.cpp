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

Vertex * Graph::get_vertex(std::string value) {
    if (vertices.find(value) == vertices.end()) {
        vertices[value] = new Vertex(value);
    }
    return vertices[value];
}

void Graph::add_edge(std::string v1, std::string v2) {
    Vertex * vertex1 = get_vertex(v1);
    Vertex * vertex2 = get_vertex(v2);
    vertex1->increment_edge(vertex2);
}

void Graph::generate_probability_mappings() {
    for (auto const& pair: vertices) {
        pair.second->calculate_probabilities();
    }
}