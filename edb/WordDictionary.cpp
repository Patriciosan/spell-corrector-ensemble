//sg
#include "WordDictionary.h"
using namespace std;
    WordDictionary::WordDictionary(string pathToDict) 
    {
        dictionary = new map<string, int>();
        ifstream infile(pathToDict.c_str());
        string word;
        if(infile == NULL) {
            cerr << "Failed to open the dictionary file, program will now exit.";
            return;
        }
        while(!infile.eof()) {
		infile >> word;
		dictionary -> insert(make_pair(word, 1));
        }
    }

    bool WordDictionary::search(string word) {
	map<string, int>::iterator i = dictionary -> find(word);
	if (i == dictionary -> end()) {
		return false;
	} else {
		return true;
	}
    }

