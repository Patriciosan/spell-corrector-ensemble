//sg
#include "edb.h"
using namespace std;
    edb::edb(string pathToDict, string knownCorrectionsMapFile)
        {
            knownCorrectionsMap = new map<string, string>();
            fillKnownCorrections(knownCorrectionsMapFile.c_str());
            dict = new WordDictionary(pathToDict);

        }

    set<string>* edb::correct(char *w)
    {
        char *res;
        set<string> *listOfWords = new set<string>();

        if(checkIfKnown(string(w))) {
            listOfWords -> insert(knownCorrectionsMap -> find(string(w)) -> second);
            return listOfWords;
        }

        //if the correction is known, simply return it

        oneDistanceReplacement(w, listOfWords);
        twoDistanceReplacement(w, listOfWords);
        singleDeletion(w, listOfWords);
        singleInsertion(w, listOfWords);
        return listOfWords;
    }
        
    void edb::fillKnownCorrections(const char *pathToFile)
    {
        ifstream f(pathToFile);
        if(!f) {
            cout << "File cannot be opened!";
            return;
        }
        string mistake, correction;
        while(!f.eof()) {
            f >> mistake >> correction;
            knownCorrectionsMap -> insert(make_pair(mistake, correction));
        }
        f.close();
    }

    //check if the word is a known error
    bool edb::checkIfKnown(string w) 
    {
	map<string, string>::iterator i = knownCorrectionsMap -> find(w);
	if (i == knownCorrectionsMap -> end()) {
		return false;
	} else {
		return true;
	}
    }

    void edb::oneDistanceReplacement(string str, set<string> *listOfWords) 
    {
            char replacement[] = {"abcdefghijklmnopqrstuvwxyz"};
            int l = str.length();
            string strc = str;
 //           strcpy(strc, str);
            char temp;
            for(int i = 0; i < l; i++) {//for each character
                temp = strc[i];
                for(int j = 0; j < 26; j++) { //replace
                    strc[i] = replacement[j];
                    if(dict -> search(strc)) {
                        listOfWords -> insert(string(strc));
                    }
                }
                strc[i] = temp;
            }
        }

        void edb::twoDistanceReplacement(char *str, set<string> *listOfWords) 
        {
            char replacement[] = {"abcdefghijklmnopqrstuvwxyz"};
            int l = strlen(str);
            char *strc = new char[l];
            strcpy(strc, str);
            char temp;
            for(int i = 0; i < l; i++) {//for each character
                temp = strc[i];
                for(int j = 0; j < 26; j++) { //replace
                    strc[i] = replacement[j];
                    oneDistanceReplacement(strc, listOfWords);
                    }
                strc[i] = temp;
            }
        }

        //deletes one character at index pos
        char* edb::deleteChar(char *str, int pos) 
        {
            int l = strlen(str);
            char *strc = new char[l];
            strcpy(strc, str);

            for(int i = pos; i < l; i++) {
                strc[i] = strc[i + 1];
            }
            strc[l - 1] = '\0';
            return strc;
        }

        void edb::singleDeletion(char *str, set<string> *listOfWords) 
        {
            char *res;
            int l = strlen(str);
            for(int i = 0; i < l; i++) {//for each character
                    if(dict -> search(res = deleteChar(str, i))) {
                        listOfWords -> insert(string(res));
                    }
                    delete res;
                
            }
        }
        
        char *edb::insertCharAt(char *str, int pos, char c)
        {
            int l = strlen(str);
            char *mod = new char[l + 2];
            int i = 0;
            for(i = 0; i < pos; i++) {
                mod[i] = str[i];
            }
            mod[i++] = c;
            for(; i <= l; i++) {
                mod[i] = str[i - 1];
            }
            mod[i] = '\0';
            return mod;
        }

        void edb::singleInsertion(char *str, set<string> *listOfWords)
        {
            char alphabet[] = {"abcdefghijklmnopqrstuvwxyz"};
            char *res;
            int l = strlen(str);
            for(int i = 0; i <= l; i++) {
                for(int j = 0; j < 26; j++) {
                    if(dict -> search(res = insertCharAt(str, i, alphabet[j]))) {
                        listOfWords -> insert(string(res));
                    }
                    delete res;
                } 
            }
        }
        edb::~edb()
        {
            delete knownCorrectionsMap;
            delete dict;
        }


       

int main(int argc, char *argv[])
{
    string wordListPath("../data/wordlist.txt");
    string knownCorrectionsFile("../data/knowncorrections.txt");
    edb *nc = new edb(wordListPath, knownCorrectionsFile);
    char input[40];
    set<string> *corrections;
    while(strcmp(input, "bye")) {
        cout << "> ";
        cin >> input;
        corrections = nc -> correct(input);
        if(corrections -> size() == 0) {
            cout << "Sorry I cannot suggest any correction \n";
            continue;
        }
        for(set<string>::iterator it = corrections -> begin(); it != corrections -> end(); it++) {
            cout << *it << "\n";
        }
    }
    cout << "bye\n";
    return 0;

}
