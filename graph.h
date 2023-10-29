#ifndef GRAPH_H
#define GRAPH_H


#include <string>
#include <map>
#include <vector>
using namespace std;
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
    string value;
    map<string, Edge *> edges;
    map<string, double> probabilities;

    Vertex(string value);
    void add_edge(Vertex * vertex);
    void increment_edge(Vertex * vertex);
    void calculate_probabilities();
};

class Graph {
public:
    map<string, Vertex *> vertices;

    Vertex * get_vertex(string value);
    void add_edge(string v1, string v2);
    void generate_probability_mappings();
    Vertex * get_next_word(Vertex * word);
};
vector<string> get_words_from_text(string text_path);
vector<string> get_files_from_directory(string directory_path);
Graph make_graph(vector<string> words);
vector<string> compose(Graph g, vector<string> words, int length=50);

#endif