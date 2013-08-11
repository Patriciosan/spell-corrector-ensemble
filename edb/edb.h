//sg
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "WordDictionary.h"
#include "FrequencyCountModel.h"

using namespace std;
class edb
{
    WordDictionary *dict;
    map<string, string> *knownCorrectionsMap;

    public:
    static int MAX_CORRECTIONS;
    enum OPTYPE  {INS = 1, DEL, SUBS, TRANS, SUBS2};
    static double ISCORE, DSCORE, SSCORE, TSCORE, S2SCORE;
    edb(string pathToDict, string knownCorrectionsMapFile);
    set<string> *correct(char *w, OPTYPE);
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
    void transpose(char *, set<string> *listOfWords);
    ~edb();
};

int edb::MAX_CORRECTIONS = 100;
double edb::ISCORE = 1;
double edb::DSCORE = 1;
double edb::TSCORE = 0.5;
double edb::SSCORE = 0.5;
double edb::S2SCORE = 0.25;

