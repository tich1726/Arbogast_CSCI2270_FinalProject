#include "Dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

//public
Dictionary::Dictionary(const char *dictionaryFile)
{
  if (1 == 0)
  {
    //later adding internet call to get updated dictionary
  }
  else
  {
    //define variables
    std::string word, pos, def;
    std::ifstream dictionaryRaw;
    dictionaryRaw.open(dictionaryFile);

    if (dictionaryRaw.good())
    {
      while (getline(dictionaryRaw, word, 'A'))
      {
        std::cout << word << std::endl;
      }
    }
    else
    {
      std::cout << "Back Up Dictionary Not Found" << std::endl;
    }
  }
  //constructor
}

bool Dictionary::searchDict(std::string word)
{

}

void Dictionary::rndWord()
{

}

Dictionary::~Dictionary()
{
  //destructor
}

//private
int hashFunction(std::string word)
{
  //Upper on word
  if (word[0] > 90)
  {
    word[0] += 32;
  }

  //convert to index in alphabetical order
  word[0] -= 65;

  int index = 1;

  //return integer
  return index;
}

void insertDict(std::string word)
{

}
