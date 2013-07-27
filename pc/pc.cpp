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

mpf_class pc[26][26]; //pc('i'|'j')
struct bigramrec
{
    char bi[3];
    mpz_class count;
};

int main()
{
    bigramrec bis[676];
    mpf_class count, total;
    total = 0;
    char temp[3];
    int i = 0;
    ifstream fi("../data/bicount.txt");
    if(!fi) {
        cout << "Error opening file!";
      
        return 0;
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
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            cout << setw(20) << pc[i][j] <<endl;
        }
    }
    cout << "> ";
    cin >> temp;
    while(strcmp(temp, "ex")) {
        cout << "P (" << temp[1] << " | " << temp[0] <<") = " << pc[temp[0] - 97][temp[1] - 97] << endl;
    cout << "> ";
    cin >> temp;
    }
    total = 0;
    for(int i = 0; i < 26; i++) {
        total += pc[1][i];
    }
    cout << total << endl;
    return 0;

}


