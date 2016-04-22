#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>

using namespace std;

struct RBTree
{
  string word;
  string pos;
  string def;
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
    Dictionary(const char *dictionaryFile);
    virtual ~Dictionary();
    bool searchDict(string word);
    void rndWord();
  protected:
  private:
    int hashFunction(string word);
    void insertDict(string word);
    RBTree *hashTable[26];
};

#endif //DICTIONARY_H
