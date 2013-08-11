#ifndef BIPROBMODEL
#define BIPROBMODEL
//sg

//The probalistic model to determine the probability of a bigram
//P(C) = P(Ci. Ci-1. Ci-2...C1) = P(Ci|Ci-1)*...P(C2|C1)
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <gmp.h>
#include <gmpxx.h>
#include <string>
#include <fstream>

using namespace std;
class BigramProbModel
{

    mpf_class pc[26][26]; //to store pc('j'|'i')
    //for a bigram b1b2, returns the prob of b2 given b1
    double biProb(string bigram);
    public:
    BigramProbModel(string bigramFile);


    //returns the probability of a word occurring by breaking it into bigrams 
    double wordProb(string word);
};
#endif
