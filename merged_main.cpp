#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

class Vertex;

class Edge {
public:
    Vertex * dest;
    int weight;

    Edge(Vertex * dest) {
        this->dest = dest;
        weight = 1;
    }

    void increment_weight() {
        weight++;
    }
};

class Vertex {
public:
    string value;
    map<string, Edge *> edges;
    map<string, double> probabilities;

    Vertex(string value) {
        this->value = value;
    }

    void add_edge(Vertex * vertex) {
        if (edges.find(vertex->value) == edges.end()) {
            edges[vertex->value] = new Edge(vertex);
        }
    }

    void increment_edge(Vertex * vertex) {
        add_edge(vertex);
        edges[vertex->value]->increment_weight();
    }

    void calculate_probabilities() {
        int sum = 0;
        for (auto const& pair: edges) {
            sum += pair.second->weight;
        }

        for (auto const& pair: edges) {
            double probability = (double) pair.second->weight / sum;
            probabilities[pair.first] = probability;
        }
    }
};

class Graph {
public:
    map<string, Vertex *> vertices;

    Vertex * get_vertex(string value) {
        if (vertices.find(value) == vertices.end()) {
            vertices[value] = new Vertex(value);
        }
        return vertices[value];
    }

    void add_edge(string v1, string v2) {
        Vertex * vertex1 = get_vertex(v1);
        Vertex * vertex2 = get_vertex(v2);
        vertex1->increment_edge(vertex2);
    }

    void generate_probability_mappings() {
        for (auto const& pair: vertices) {
            pair.second->calculate_probabilities();
        }
    }

    Vertex * get_next_word(Vertex * word) {
        map<string, double> probabilities = word->probabilities;

        double probability = (double) rand() / RAND_MAX;

        double cumulative_probability = 0.0;
        for (auto const& pair: probabilities) {
            cumulative_probability += pair.second;
            if (cumulative_probability >= probability) {
                return vertices[pair.first];
            }
        }
        return nullptr;
    }
};

vector<string> get_words_from_text(string text_path) {
    ifstream file(text_path);
    string word;
    vector<string> words;
    while (file >> word) {
        string no_punct_word = "";
        for (char c : word) {
            if (isalpha(c)) {
                no_punct_word += tolower(c);
            }
        }
        words.push_back(no_punct_word);
    }
    file.close();
    return words;
}

// vector<string> remove_punctuation(vector<string> words) {
//     vector<string> no_punct;
//     for (string word : words) {
//         string no_punct_word = "";
//         for (char c : word) {
//             if (isalpha(c)) {
//                 no_punct_word += tolower(c);
//             }
//         }
//         no_punct.push_back(no_punct_word);
//     }
    
//     return no_punct;
// } 

Graph make_graph(vector<string> words) {
    Graph g;
    Vertex * prev_word = nullptr;
    // for each word
    for (string word : words) {
        // check that word is in graph, and if not then add it
        Vertex * word_vertex = g.get_vertex(word);

        // if there was a previous word, then add an edge if does not exist
        // if exists, increment weight by 1
        if (prev_word) {
            // check if edge exists from previous word to current word
            prev_word->increment_edge(word_vertex);
        }

        prev_word = word_vertex;
    }

    g.generate_probability_mappings();

    return g;
}

vector<string> compose(Graph g, vector<string> words, int length=50) {
    vector<string> composition;
    Vertex * word = g.get_vertex(words[rand() % words.size()]);
    for (int i = 0; i < length; i++) {
        composition.push_back(word->value);
        word = g.get_next_word(word);
        if (!word) {
            word = g.get_vertex(words[rand() % words.size()]);
        }
    }

    return composition;
}

int main() {
    srand(time(nullptr));
    vector<string> words = get_words_from_text("hp_sorcerer_stone.txt");
    //vector<string> words = remove_punctuation(words1);

    Graph g = make_graph(words);
    vector<string> composition = compose(g, words, 100);
    
    for (string word : composition) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}