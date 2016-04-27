#include "Thesaurus.h"
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//public
Thesaurus::Thesaurus()
{
    std::string line, word1, word2, weightStr;
    int weight;
    std::ifstream inFile ("thesaurusRaw.txt");
    if (inFile.good())
    {
        while (getline(inFile,line))
        {
            std::stringstream ss(line);
            getline(ss,word1,',');
            getline(ss,word2,',');
            getline(ss,weightStr);
            weight = atoi(weightStr.c_str());
            addVertex(word1);
            addVertex(word2);
            addEdge(word1,word2,weight);
        }
    }
    //ctor
}

void Thesaurus::searchThesaurus(std::string word, int weight)
{
    int maxVal, val, k;
    bool loopT = true;
    vertex *searchWord = findVertex(word);
    vertex *solved, *s;
    if (searchWord != NULL)
    {
        std::vector<vertex*> solvedV;
        searchWord->visited = true;
        std::cout << "Base:" << searchWord->word << std::endl;
        solvedV.push_back(searchWord);
        while (solvedV.size() != k)
        {
            loopT = false;
            k = solvedV.size();
            maxVal = 101;
            solved = NULL;
            for (int i=0; i<solvedV.size(); i++)
            {
                for (int j=0; j<solvedV[i]->adj.size(); j++)
                {
                    if (!solvedV[i]->adj[j]->v->visited)
                    {
                        val = (solvedV[i]->weight*solvedV[i]->adj[j]->weight)/100;
                        //std::cout << val << std::endl;
                        if (val > maxVal || maxVal == 101)
                        {
                            solved = solvedV[i]->adj[j]->v;
                            maxVal = val;
                            loopT = true;
                        }
                    }
                }
            }
            if (loopT)
            {
                solved->weight = maxVal;
                solved->visited = true;
                if (solved->weight >= weight)
                {
                    std::cout << solved->word << ":" << solved->weight << "%" << std::endl;
                }
                solvedV.push_back(solved);
            }
        }
        for (int i=0; i<thesaurusBase.size(); i++)
        {
            thesaurusBase[i]->visited = false;
        }
    }
    else
    {
        std::cout << "Sorry, I Couldn't Find An Entry For That Word.\nPerhaps You Should Create A New One!" << std::endl;
    }
}

void Thesaurus::addEdge(std::string word1, std::string word2, int weight)
{
    bool repeat = false;
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        if (thesaurusBase[i]->word == word1)
        {
            for (int k=0; k<thesaurusBase[i]->adj.size(); k++)
            {
                if (thesaurusBase[i]->adj[k]->v->word == word2)
                {
                    repeat = true;
                    break;
                }
            }
            for (int j=0; j<thesaurusBase.size(); j++)
            {
                if (thesaurusBase[j]->word == word2 && i != j && !repeat)
                {
                    adjVertex *av = new adjVertex;
                    av->v = thesaurusBase[j];
                    av->weight = weight;
                    thesaurusBase[i]->adj.push_back(av);
                    adjVertex *av2 = new adjVertex;
                    av2->v = thesaurusBase[i];
                    av2->weight = weight;
                    thesaurusBase[j]->adj.push_back(av2);
                }
                else if (thesaurusBase[j]->word == word2 && i != j && repeat)
                {
                    for (int k=0; k<thesaurusBase[i]->adj.size(); k++)
                    {
                        if (thesaurusBase[i]->adj[k]->v->word == word2)
                        {
                            thesaurusBase[i]->adj[k]->weight = weight;
                        }
                    }
                    for (int g=0; g<thesaurusBase[j]->adj.size(); g++)
                    {
                        if (thesaurusBase[j]->adj[g]->v->word == word1)
                        {
                            thesaurusBase[j]->adj[g]->weight = weight;
                        }
                    }
                }
            }
        }
    }
}

void Thesaurus::addVertex(std::string word)
{
    bool found = false;
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        if (thesaurusBase[i]->word == word)
        {
            found = true;
            //std::cout << thesaurusBase[i].word << " Already Exists" << std::endl;
        }
    }
    if (found == false)
    {
        vertex *newWord = new vertex;
        newWord->word = word;
        newWord->weight = 100;
        newWord->parent = NULL;
        newWord->visited = false;
        thesaurusBase.push_back(newWord);
    }
}

void Thesaurus::deleteEdge(std::string word1, std::string word2)
{
    bool repeat;
    std::cout << "hi" << std::endl;
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        if (thesaurusBase[i]->word == word1)
        {
            for (int k=0; k<thesaurusBase[i]->adj.size(); k++)
            {
                if (thesaurusBase[i]->adj[k]->v->word == word2)
                {
                    repeat = true;
                    break;
                }
            }
            if (repeat)
            {
            for (int j=0; j<thesaurusBase.size(); j++)
            {
                if (thesaurusBase[j]->word == word2 && i != j)
                {
                    for (int k=0; k<thesaurusBase[i]->adj.size(); k++)
                    {
                        if (thesaurusBase[i]->adj[k]->v->word == word2)
                        {
                            for (int h=k; h<thesaurusBase[i]->adj.size()-1; h++)
                            {
                                thesaurusBase[i]->adj[h] = thesaurusBase[i]->adj[h+1];
                            }
                        }
                    }
                    thesaurusBase[i]->adj.pop_back();
                    for (int k=0; k<thesaurusBase[j]->adj.size(); k++)
                    {
                        if (thesaurusBase[j]->adj[k]->v->word == word1)
                        {
                            for (int l=k; l<thesaurusBase[j]->adj.size()-1; l++)
                            {
                                thesaurusBase[j]->adj[l] = thesaurusBase[j]->adj[l+1];
                            }
                        }
                    }
                    thesaurusBase[j]->adj.pop_back();
                }
            }
            }
            else
            {
                std::cout << "There Isn't A Connection Between These Two Words" << std::endl;
            }
        }
    }
}

void Thesaurus::deleteVertex(std::string word)
{
    /*int i;
    bool found = false;
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        if (thesaurusBase[i]->word == word)
        {
            found = true;
            break;
        }
    }
    if (found == true)
    {
        for (int j=0; j<thesaurusBase[i]->adj.size(); j++)
        {
            deleteEdge(thesaurusBase[i]->word, thesaurusBase[i]->adj[j]->v->word);
        }
        std::cout << "hi" << std::endl;
        for (int k=i; k<thesaurusBase.size()-1; k++)
        {
            thesaurusBase[k] = thesaurusBase[k+1];
        }
        thesaurusBase.pop_back();
    }*/
}

void Thesaurus::printThesaurus()
{
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        std::cout << thesaurusBase[i]->word << std::endl;
    }
}

Thesaurus::~Thesaurus()
{
    std::ofstream outFile ("thesaurusRaw.txt");
    if (outFile.is_open())
    {
        for (int i=0; i<thesaurusBase.size(); i++)
        {
            if (!thesaurusBase[i]->adj.empty())
            {
            for (int j=0; j<thesaurusBase[i]->adj.size(); j++)
            {
                outFile << thesaurusBase[i]->word << ",";
                outFile << thesaurusBase[i]->adj[j]->v->word << ",";
                outFile << thesaurusBase[i]->adj[j]->weight;
                outFile << "\n";
            }
            }
            else
            {
                outFile << thesaurusBase[i]->word << ",";
                outFile << "\n";
            }
        }
        outFile.close();
    }
    else
    {
        std::cout << "unable to save thesaurus" << std::endl;
    }
    //dtor
}

vertex *Thesaurus::findVertex(std::string word)
{
    for (int i=0; i<thesaurusBase.size(); i++)
    {
        if (thesaurusBase[i]->word == word)
        {
            return thesaurusBase[i];
        }
    }
    return NULL;
}
