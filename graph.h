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