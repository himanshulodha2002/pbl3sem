#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "graph.h"

std::vector<std::string> get_words_from_text(std::string text_path)
{
    std::ifstream file(text_path);
    std::string word;
    std::vector<std::string> words;
    while (file >> word)
    {
        std::string no_punct_word = "";
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

// std::vector<std::string> remove_punctuation(std::vector<std::string> words)
// {
//     std::vector<std::string> no_punct;
//     for (std::string word : words)
//     {
//         std::string no_punct_word = "";
//         for (char c : word)
//         {
//             if (isalpha(c))
//             {
//                 no_punct_word += tolower(c);
//             }
//         }
//         no_punct.push_back(no_punct_word);
//     }
//     return no_punct;
// }

Graph make_graph(std::vector<std::string> words)
{
    Graph g;
    Vertex *prev_word = nullptr;
    for (std::string word : words)
    {
        Vertex *word_vertex = g.get_vertex(word);
        if (prev_word)
        {
            prev_word->increment_edge(word_vertex);
        }
        prev_word = word_vertex;
    }

    g.generate_probability_mappings();
    return g;
}

std::vector<std::string> compose(Graph g, std::vector<std::string> words, int length = 50)
{
    std::vector<std::string> composition;
    Vertex *word = g.get_vertex(words[rand() % words.size()]);
    for (int i = 0; i < length; i++)
    {
        composition.push_back(word->value);
        word = g.get_next_word(word);
        if (!word)
        {
            word = g.get_vertex(words[rand() % words.size()]);
        }
    }

    return composition;
}

int main()
{
    srand(time(nullptr));
    std::vector<std::string> words = get_words_from_text("hp_sorcerer_stone.txt");
    //std::vector<std::string> words = remove_punctuation(words1);
    
    Graph g = make_graph(words);
    std::vector<std::string> composition = compose(g, words, 100);

    for (std::string word : composition)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
