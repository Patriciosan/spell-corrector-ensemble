#ifndef FCOUNT
#define FCOUNT
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class FrequencyCountModel
{
private:
float getTotalFrequency() ;
void countFrequency(string) ;
void populateFrequencyCounterMap(string) ;

public :
float wordProb(string ) ;
FrequencyCountModel(string );
};
#endif
