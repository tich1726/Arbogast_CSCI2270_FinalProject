#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <vector>

using namespace std;

struct RBTree
{
  string word;
  string def;
  string origin;
  string color;
  RBTree *parent;
  RBTree *left;
  RBTree *right;

  RBTree(){};

  RBTree(string initColor, RBTree *initParent, RBTree *initLeft, RBTree *initRight)
  {
    color = initColor;
    parent = initParent;
    left = initLeft;
    right = initRight;
  }
};

class Dictionary
{
  public:
    Dictionary();
    Dictionary(const char *dictionaryFile);
    virtual ~Dictionary();
    void searchDict(string word);
    void printDict(string section);
    void rndWord();
    void printSim(RBTree *subRoot, string word);
  protected:
  private:
    void leftRotate(RBTree *subRoot, int index);
    void rightRotate(RBTree *subRoot, int index);
    int hashFunction(string word);
    void printDict(RBTree *root);
    RBTree *insertDict(RBTree *newEntry);
    void RBinsertDict(RBTree *newEntry);
    RBTree *hashTable[26];
};

#endif //DICTIONARY_H
