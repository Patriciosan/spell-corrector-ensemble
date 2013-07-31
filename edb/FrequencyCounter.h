#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>

using namespace std;

struct WordDetails ;

void openFile() ;
void closeFile();

float getTotalFrequency() ;

int findWordFrequency(string searchWord) ;

bool operator<(const WordDetails& left, const WordDetails& right) ;

void countFrequency(set<string> correctedWordSet) ;

void calculate(set<string> correctedWordSet) ;
void getHighestFrequencyCountWord(set<string> correctList,int priority) ;

