//sg
#include "BigramProbModel.h"
#include "FrequencyCountModel.h"
#include "Ranker.h"
Ranker::Ranker(string bigramPath, string freqPath)
        {
            bpm = new BigramProbModel(string("../data/bicount.txt"));
            fcm = new FrequencyCountModel(string("../data/out.txt")); 
        }
        double Ranker::rank(string type, string str)
        {
            if(type == "freq") {
                return fcm -> wordProb(str);
            } else if(type == "bigram"){
                return bpm -> wordProb(str);
            }
        }
    
