#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Dictionary.h"
#include "Thesaurus.h"
#include <sstream>

using namespace std;

//define variables
int userChoice, percent;
string userChoiceStr, filePath, thesaurusEntry, word1, word2, wordD, percentStr;

//displays menu as well as loads the Thesaurus and Dictionary
int main(int argc, char *argv[])
{
  Dictionary baseDictionary(argv[1]);
  Thesaurus baseThesaurus;

  cout << "         __WORD OF THE DAY__" << endl;
  cout << endl;
  baseDictionary.rndWord();
  cout << endl;

  userChoice = -1;
  while (userChoice != 0)
  {
    cout << "======AwfulWafful's Dictionary======" << endl;
    cout << "1. Search Dictionary" << endl;
    cout << "2. How Accurate Is My Paper?" << endl;
    cout << "3. My Thesaurus" << endl;
    cout << "4. Exit" << endl;

    getline(cin,userChoiceStr);
    userChoice = atoi(userChoiceStr.c_str());

    switch (userChoice)
    {
      case 1:
          while (userChoice != -1)
          {
              cout << "1. Print A Section" << endl;
              cout << "2. Find a Word" << endl;
              cout << "3. Go Back" << endl;

            getline(cin,userChoiceStr);
            userChoice = atoi(userChoiceStr.c_str());
              switch (userChoice)
              {
              case 1:
                  cout << "Enter The Section You Wish To Print (Eg. 'A' ):" << endl;
                  getline(cin,userChoiceStr);
                  while (userChoiceStr.size() > 1 || userChoiceStr[0] < 65 || userChoiceStr[0] > 122)
                  {
                      cout << "Please Enter A Single Letter (A-Z) In Order To Indicate the Section\nYou Wish To Print:" << endl;

                      getline(cin,userChoiceStr);
                  }
                  baseDictionary.printDict(userChoiceStr);
                break;
              case 2:
                  cout << "Please Enter The Word You Wish To Find:" << endl;
                  getline(cin,wordD);
                  baseDictionary.searchDict(wordD);
                break;
              case 3:
                  userChoice = -1;
                break;
              default:
                  cout << endl;
                  cout << "Please Choose An Option From The Menu" << endl;
                  cout << endl;
              }
          }
        break;
      case 2:
          cout << "Please Enter The Full Path Of The .txt File\nYou Wish To Check:" << endl;

          getline(cin, filePath);

        while (userChoice != -1)
        {
          cout << "******Paper Editor******" << endl;
          cout << "1. Spell Check" << endl;
          cout << "2. Top Ten Histogram" << endl;
          cout << "3. Words Only Used Once" << endl;
          cout << "4. Word Accuracy" << endl;
          cout << "5. Go Back" << endl;

          getline(cin, userChoiceStr);
          userChoice = atoi(userChoiceStr.c_str());

          switch (userChoice)
          {
            case 1:
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;
            case 5:
              userChoice = -1;
              break;
            default:
              cout << endl;
              cout << "Please Choose An Option From The Menu" << endl;
              cout << endl;
          }
        }
        break;
      case 3:
        while (userChoice != -1)
        {
          cout << "******My Thesaurus******" << endl;
          cout << "1. Add Thesaurus Entry" << endl;
          cout << "2. Delete Thesaurus Entry" << endl;
          cout << "3. Search Thesaurus" << endl;
          cout << "4. Go Back" << endl;

          getline(cin,userChoiceStr);
          userChoice = atoi(userChoiceStr.c_str());

          switch (userChoice)
          {
            case 1:
                cout << "Please Enter Word Pairs Followed By A Percent Value Of Their Relatability:\nEG. 'Mountain,Hill,70 Gym,School,30'" << endl;
                getline(cin,thesaurusEntry);
                if (userChoice == 1)
                {
                    stringstream ss(thesaurusEntry);
                    while (getline(ss,thesaurusEntry, ' '))
                    {
                        stringstream dd(thesaurusEntry);
                        getline(dd,word1,',');
                        baseThesaurus.addVertex(word1);
                        getline(dd,word2,',');
                        baseThesaurus.addVertex(word2);
                        getline(dd,percentStr);
                        percent = atoi(percentStr.c_str());
                        baseThesaurus.addEdge(word1,word2,percent);
                    }
                }
              break;
            case 2:
                cout << "Please Enter The Connection(s) You Wish To Terminate, Separated By A Space:\nEG. 'Mountain,Hill School,Gym'" << endl;
                cout << "Or Delete An Entire Entry by Typing In The Word You Wish To Delete In Brackets:\nEG. '[Mountain]'" << endl;
                getline(cin,thesaurusEntry);
                if (userChoice == 2)
                {
                    if (thesaurusEntry[0] == 91 && thesaurusEntry[thesaurusEntry.size()-1] == 93)
                    {
                        stringstream ss(thesaurusEntry);
                        getline(ss,word1,'[');
                        getline(ss,word1,']');
                        baseThesaurus.deleteVertex(word1);
                    }
                    else
                    {
                        stringstream ss(thesaurusEntry);
                        while (getline(ss,thesaurusEntry, ' '))
                        {
                            stringstream dd(thesaurusEntry);
                            getline(dd,word1,',');
                            getline(dd,word2);
                            baseThesaurus.deleteEdge(word1,word2);
                        }
                    }
                }
              break;
            case 3:
                cout << "Please Enter The Word You Wish To Search And The Minimum Percent Relatability\nTo This Word You Require Eg. 'Mountain,70':" << endl;
                getline(cin,word1,',');
                getline(cin,percentStr);
                percent = atoi(percentStr.c_str());
                baseThesaurus.searchThesaurus(word1, percent);
              break;
            case 4:
              userChoice = -1;
              break;
            default:
              cout << endl;
              cout << "Please Choose An Option From The Menu" << endl;
              cout << endl;
          }
        }
          break;
        case 4:
          cout << "Goodbye!" << endl;
          cout << "...or is it?" << endl;
          userChoice = 0;
          break;
        default:
          cout << endl;
          cout << "Please Choose An Option From The Menu" << endl;
          cout << endl;
          userChoice = -1;
      }
    }
  return 0;
}

