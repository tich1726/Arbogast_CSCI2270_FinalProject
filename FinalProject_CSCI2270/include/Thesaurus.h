#ifndef THESAURUS_H
#define THESAURUS_H
#include <vector>
#include <iostream>

struct vertex;

struct adjVertex
    {
    vertex *v;
    int weight;
    };

    struct vertex
    {
    vertex *parent;
    std::string word;
    int weight;
    bool visited;
    std::vector<adjVertex*> adj;
    };

class Thesaurus
{
    public:
        Thesaurus();
        ~Thesaurus();
        void searchThesaurus(std::string word, int weight);
        void addEdge(std::string word1, std::string word2, int weight);
        void addVertex(std::string word);
        void deleteEdge(std::string word1, std::string word2);
        void deleteVertex(std::string word);
        vertex *findVertex(std::string word);
    protected:
    private:
        std::vector<vertex*> thesaurusBase;
};

#endif // THESAURUS_H
