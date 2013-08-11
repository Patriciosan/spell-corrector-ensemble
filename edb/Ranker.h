#ifndef RANKER
#define RANKER
//sg
#include "BigramProbModel.h"
#include "FrequencyCountModel.h"
class Ranker
{ 
    BigramProbModel *bpm;
    FrequencyCountModel *fcm;
    public:
    Ranker(string bigramPath, string freqPath);
    double rank(string type, string str);
};
#endif
