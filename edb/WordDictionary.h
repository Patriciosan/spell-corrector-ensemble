//sg
#include <iostream>
#include <map>
#include <string.h>
#include <fstream>
#include <string>
using namespace std;
class WordDictionary
{
    public:
    map<string, int> *dictionary;
    WordDictionary(string pathToDict);
    bool search(string word);
};


