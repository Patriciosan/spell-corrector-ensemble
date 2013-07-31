//sg
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "WordDictionary.h"
#include "FrequencyCounter.h"

using namespace std;
class edb
{
    WordDictionary *dict;
    map<string, string> *knownCorrectionsMap;

    public:
    edb(string pathToDict, string knownCorrectionsMapFile);
    set<string> *correct(char *w,int priority);
    private :
    void fillKnownCorrections(const char *pathToFile);
    //check if the word is a known error
    bool checkIfKnown(string w);
    void oneDistanceReplacement(string str, set<string> *listOfWords);
    void twoDistanceReplacement(char *str, set<string> *listOfWords);
    char* deleteChar(char *str, int pos);
    void singleDeletion(char *str, set<string> *listOfWords);
    char *insertCharAt(char *str, int pos, char c);
    void singleInsertion(char *str, set<string> *listOfWords);
    ~edb();
};

       

