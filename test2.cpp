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
    map<pair<string, string>, Vertex> vertices;

    void add_edge(const string &v1, const string &v2, const string &v3)
    {
        vertices[make_pair(v1, v2)].edges[v3]++;
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

    const Vertex &get_vertex(const pair<string, string> &words) const
    {
        static Vertex emptyVertex; // Return an empty vertex if not found
        auto it = vertices.find(words);
        return (it != vertices.end()) ? it->second : emptyVertex;
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

    for (size_t i = 0; i < words.size() - 2; ++i)
    {
        g.add_edge(words[i], words[i + 1], words[i + 2]);
    }

    return g;
}

vector<string> compose(const Graph &g, int length = 200)
{
    vector<string> composition;

    if (g.vertices.empty())
    {
        cerr << "Error: Graph is empty." << endl;
        return composition;
    }

    pair<string, string> currentWords = make_pair(g.vertices.begin()->first.first, g.vertices.begin()->first.second);

    for (int i = 0; i < length; ++i)
    {
        composition.push_back(currentWords.first);
        composition.push_back(currentWords.second);

        const Vertex &wordVertex = g.get_vertex(currentWords);
        string nextWord = g.get_next_word(wordVertex);

        if (nextWord.empty())
        {
            break;
        }

        currentWords = make_pair(currentWords.second, nextWord);
    }

    return composition;
}

int main()
{
    srand(time(nullptr));
    //vector<string> words = get_words_from_text("hp_sorcerer_stone.txt");
    vector<string> words = get_words_from_text("songs\\taylor_swift\\1__You-Belong-with-Me.txt");

    Graph g = make_graph(words);

    if (words.empty())
    {
        cerr << "Error: No words in the input text." << endl;
        return 1;
    }

    vector<string> composition = compose(g, 100);

    if (composition.empty())
    {
        cerr << "Error: Unable to generate text." << endl;
        return 1;
    }

    // for (const string &word : composition)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;
    for (int i = 0; i < composition.size(); i += 2)
    {
        std::cout << composition[i] << " ";
    }
    cout << endl;

    return 0;
}
