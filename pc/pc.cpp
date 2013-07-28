//sg
//The probalistic model to determine the probability of a bigram
//P(C) = P(Ci. Ci-1. Ci-2...C1) = P(Ci|Ci-1)*...P(C2|C1)

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

class BigramProbModel
{

    mpf_class pc[26][26]; //to store pc('j'|'i')
    public:
    BigramProb(string bigramFile)
    {
        mpf_class count, total;
        total = 0;
        char temp[3];
        int i = 0;
        ifstream fi("../data/bicount.txt");
        if(!fi) {
            cout << "Error opening file!";
          
            return;
        }
    
        for(int i = 0; i < 26; i++) {
    
            total = 0; 
            //comments written for i = 0
            for(int j = 0; j < 26; j++) { //calculate the total and store it
                fi >> temp;
                fi >> count;
            pc[i][j] = count;
            total = total + count;
            }
            //now we have total words that start with 'a'
            //we also have in each pc[0][j] the count of words that 
            //start with a and end with jth char
    
            for(int j = 0; j < 26; j++) { 
                pc[i][j] = pc[i][j] / total;
            }
    
        }
    }

    double prob(string bigram)
    {
        return pc[bigram[0] - 97][bigram[1] - 97].get_d();
    }
};

int main()
{
    string temp;
    BigramProb bp("../data/bicount.txt");
    cout << "> ";
    cin >> temp;
    while(temp != "ex") {
        cout << "P (" << temp[1] << " | " << temp[0] <<") = " << bp.prob(temp) << endl;
    cout << "> ";
    cin >> temp;
    }
    return 0;

}
