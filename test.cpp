#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

class Vertex
{
public:
    string value;
    map<string, int> edges;
};

class Graph
{
public:
    mutable map<string, Vertex> vertices; // Make the map mutable

    void add_edge(const string &v1, const string &v2)
    {
        vertices[v1].edges[v2]++;
    }

    string get_next_word(const Vertex &word) const
    {
        const auto &probabilities = word.edges;
        int totalWeight = 0;

        for (const auto &pair : probabilities)
        {
            totalWeight += pair.second;
        }

        int randomWeight = rand() % totalWeight;

        for (const auto &pair : probabilities)
        {
            randomWeight -= pair.second;
            if (randomWeight <= 0)
            {
                return pair.first;
            }
        }

        return "";
    }
};

vector<string> get_words_from_text(const string &text_path)
{
    ifstream file(text_path);
    string word;
    vector<string> words;

    while (file >> word)
    {
        string no_punct_word = "";
        for (char c : word)
        {
            if (isalpha(c))
            {
                no_punct_word += tolower(c);
            }
        }
        words.push_back(no_punct_word);
    }
    file.close();

    return words;
}

Graph make_graph(const vector<string> &words)
{
    Graph g;

    for (size_t i = 0; i < words.size() - 1; ++i)
    {
        g.add_edge(words[i], words[i + 1]);
    }

    return g;
}

vector<string> compose(const Graph &g, const vector<string> &words, int length = 50)
{
    vector<string> composition;
    string currentWord = words[rand() % words.size()];

    for (int i = 0; i < length; ++i)
    {
        composition.push_back(currentWord);
        const Vertex &wordVertex = g.vertices[currentWord]; // Access the mutable map
        currentWord = g.get_next_word(wordVertex);
        if (currentWord.empty())
        {
            currentWord = words[rand() % words.size()];
        }
    }

    return composition;
}

int main()
{
    srand(time(nullptr));
    vector<string> words = get_words_from_text("shakespeare.txt");
    Graph g = make_graph(words);
    vector<string> composition = compose(g, words, 100);

    for (const string &word : composition)
    {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}