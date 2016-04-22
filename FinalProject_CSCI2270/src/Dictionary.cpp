#include "Dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//public
Dictionary::Dictionary()
{
    for (int i=0; i<26; i++)
    {
        RBTree *nullNode = new RBTree("black",NULL,NULL,NULL);
        nullNode->word = "nullNode";
        hashTable[i] = nullNode;
    }
    //constructor
}

Dictionary::Dictionary(const char *dictionaryFile)
{
    for (int i=0; i<26; i++)
    {
        RBTree *nullNode = new RBTree("black",NULL,NULL,NULL);
        nullNode->word = "nullNode";
        hashTable[i] = nullNode;
    }
  if (1 == 0)
  {
    //later adding internet call to get updated dictionary
  }
  else
  {
    //define variables
    int count = 0;
    std::string section, word, word2, pos, pos2, def;
    std::ifstream dictionaryRaw;
    dictionaryRaw.open(dictionaryFile);

    if (dictionaryRaw.good())
    {
      while (getline(dictionaryRaw, word))
      {
          ++count;
          if(word[0] != 0 && word[0] != 32 && word[0] != 45 && word[0] != 39 && word[0] != -55
             && word[0] != -93 && word[0] != -116)//space or null
          {
            stringstream ss(word);
            getline(ss,word, ' ');
            /*getline(ss,word2, ' ');
            //http://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char lines 34-40
            char *writable = new char[word.size() + 1];
            std::copy(word.begin(), word.end(), writable);
            writable[str.size()] = '\0';
            strcat(writable,word2.c_str());
            delete[] writable;*/
            getline(ss,pos, ' ');
            getline(ss, def);
            stringstream dd(def);
            getline(dd, pos2, ' ');
            if (pos2[pos2.size()-1] == 46)//.
            {
                int i=0;
                while (def[i] != 0)
                {
                    if (def[i] == -105)//u with asteric
                    {
                    def[i] = 45;
                    }
                    ++i;
                }
                RBTree *nullNode1 = new RBTree("black",NULL,NULL,NULL);
                nullNode1->word = "nullNode";
                RBTree *nullNode2 = new RBTree("black",NULL,NULL,NULL);
                nullNode2->word = "nullNode";
                RBTree *newEntry = new RBTree("red",NULL,nullNode1,nullNode2);
                nullNode1->parent = newEntry;
                nullNode2->parent = newEntry;
                newEntry->def = def;
                newEntry->word = word;
                //std::cout <<int(word[0]) <<std::endl;
                RBinsertDict(newEntry);
                //std::cout << word  <<std::endl;
            }

          }
        if (count == 10080)
        {
            //break;
        }
      }
    }
    else
    {
      std::cout << "Back Up Dictionary Not Found" << std::endl;
    }
  }
  //std::cout << hashTable[0]->word << std::endl;
  //constructor2
}

bool Dictionary::searchDict(std::string word)
{

}

void Dictionary::rndWord()
{

}

void Dictionary::printDict(string section)
{
    int index = hashFunction(section);
    printDict(hashTable[index]);
}

Dictionary::~Dictionary()
{
  //destructor
}

//private
int Dictionary::hashFunction(std::string word)
{
  //Upper on word
  if (word[0] > 90)
  {
    word[0] -= 32;
  }

  //convert to index in alphabetical order
  word[0] -= 65;

  int index = int(word[0]);

  //return integer
  return index;
}

RBTree *Dictionary::insertDict(RBTree *newEntry)
{
    //std::cout << newEntry->word[0]<< std::endl;
    int index = hashFunction(newEntry->word);
    //std::cout << newEntry->word[0]<< std::endl;
    RBTree *tmp = hashTable[index];
    RBTree *parent;
    if (tmp->word != "nullNode")
    {
    while (tmp->word != "nullNode")
    {
        parent = tmp;
        if (newEntry->word < tmp->word)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
    }
    if (newEntry->word < parent->word)
    {
        parent->left = newEntry;
    }
    else
    {
        parent->right = newEntry;
    }
    newEntry->parent = parent;
    }
    else
    {
        hashTable[index] = newEntry;
    }

    return newEntry;
}

void Dictionary::RBinsertDict(RBTree *newEntry)
{
    int index = hashFunction(newEntry->word);
    RBTree *newNode = insertDict(newEntry);
    while (hashTable[index] != newNode && newNode->parent->color == "red")
    {
        if (newNode->parent == newNode->parent->parent->left)
        {
            RBTree *Uncle = newNode->parent->parent->right;
            if (Uncle->color == "red")
            {
                newNode->parent->color = "black";
                Uncle->color = "black";
                newNode->parent->parent->color = "red";
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->right)
                {
                    newNode = newNode->parent;
                    leftRotate(newNode, index);
                    newNode = newNode->left;
                }
                newNode->parent->color = "black";
                newNode->parent->parent->color = "red";
                rightRotate(newNode->parent->parent, index);
            }
        }
        else
        {
            RBTree *Uncle = newNode->parent->parent->left;
            if (Uncle->color == "red")
            {
                newNode->parent->color = "black";
                Uncle->color = "black";
                newNode->parent->parent->color = "red";
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->left)
                {
                    newNode = newNode->parent;
                    rightRotate(newNode, index);
                    newNode = newNode->right;
                }
                newNode->parent->color = "black";
                newNode->parent->parent->color = "red";
                leftRotate(newNode->parent->parent, index);
            }
        }
    }
    hashTable[index]->color = "black";
}

void Dictionary::leftRotate(RBTree *subRoot, int index)
{
    RBTree *y = subRoot->right;
    subRoot->right = y->left;
    if (y->left->word != "nullNode")
    {
        y->left->parent = subRoot;
    }
    y->parent = subRoot->parent;
    if (subRoot->parent == NULL)
    {
        hashTable[index] = y;
    }
    else
    {
        if (subRoot == subRoot->parent->left)
        {
            subRoot->parent->left = y;
        }
        else
        {
            subRoot->parent->right = y;
        }
    }
    y->left = subRoot;
    subRoot->parent = y;
}

void Dictionary::rightRotate(RBTree *subRoot, int index)
{
    RBTree *y = subRoot->left;
    subRoot->left = y->right;
    if (y->right->word != "nullNode")
    {
        y->right->parent = subRoot;
    }
    y->parent = subRoot->parent;
    if (subRoot->parent == NULL)
    {
        hashTable[index] = y;
    }
    else if (subRoot == subRoot->parent->left)
    {
        subRoot->parent->left = y;
    }
    else
    {
        subRoot->parent->right = y;
    }
    y->right = subRoot;
    subRoot->parent = y;
}

void Dictionary::printDict(RBTree *root)
{
    if (root->left != NULL && root->right != NULL)
    {
    if (root->left->word != "nullNode")
    {
        printDict(root->left);
    }
    std::cout << root->word << std::endl;
    std::cout << root->def << std::endl;
    if (root->right->word != "nullNode")
    {
        printDict(root->right);
    }
    }
    else
    {
        std::cout << "*There Are No Entry's This Section*" << std::endl;
    }
}

