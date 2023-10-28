#ifndef GRAPH_H
#define GRAPH_H


#include <string>
#include <map>
#include <vector>

class Vertex;

class Edge {
public:
    Vertex * dest;
    int weight;

    Edge(Vertex * dest);
    void increment_weight();
};

class Vertex {
public:
    std::string value;
    std::map<std::string, Edge *> edges;
    std::map<std::string, double> probabilities;

    Vertex(std::string value);
    void add_edge(Vertex * vertex);
    void increment_edge(Vertex * vertex);
    void calculate_probabilities();
};

class Graph {
public:
    std::map<std::string, Vertex *> vertices;

    Vertex * get_vertex(std::string value);
    void add_edge(std::string v1, std::string v2);
    void generate_probability_mappings();
    Vertex * get_next_word(Vertex * word);
};
std::vector<std::string> get_words_from_text(std::string text_path);
std::vector<std::string> get_files_from_directory(std::string directory_path);
Graph make_graph(std::vector<std::string> words);
std::vector<std::string> compose(Graph g, std::vector<std::string> words, int length=50);

#endif