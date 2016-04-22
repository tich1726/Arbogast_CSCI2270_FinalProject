#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Dictionary.h"

using namespace std;

//define variables
int userChoice;
string userChoiceStr;

//displays menu as well as loads the Thesaurus and Dictionary
int main(int argc, char *argv[])
{
  Dictionary baseDictionary(argv[1]);

  cout << "         __WORD OF THE DAY__" << endl;
  cout << endl;

  userChoice = -1;
  while (userChoice != 0)
  {
    cout << "======AwfulWafful's Dictionary======" << endl;
    cout << "1. Search Dictionary" << endl;
    cout << "2. How Accurate Are My Tweets?" << endl;
    cout << "3. My Thesaurus" << endl;
    cout << "4. Exit" << endl;

    getline(cin,userChoiceStr);
    userChoice = atoi(userChoiceStr.c_str());

    switch (userChoice)
    {
      case 1:
        break;
      case 2:
        while (userChoice != -1)
        {
          cout << "******Login******" << endl;
          cout << "1. Facebook" << endl;
          cout << "2. Twitter" << endl;
          cout << "3. Go Back" << endl;

          getline(cin, userChoiceStr);
          userChoice = atoi(userChoiceStr.c_str());

          switch (userChoice)
          {
            case 1:
              break;
            case 2:
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
              break;
            case 2:
              break;
            case 3:
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
