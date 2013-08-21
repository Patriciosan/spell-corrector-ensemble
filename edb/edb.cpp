//sg
#include <sstream>
#include "edb.h"
#include "BigramProbModel.h"
#include "FrequencyCountModel.h"
#include "Ranker.h"
#include <algorithm>
using namespace std;

edb::edb(string pathToDict, string knownCorrectionsMapFile) 
{
	knownCorrectionsMap = new map<string, string>();
	fillKnownCorrections(knownCorrectionsMapFile.c_str());
	dict = new WordDictionary(pathToDict);

}
set<string>* edb::correct(char *w, OPTYPE op) 
{
	char *res;
	set<string> *listOfWords = new set<string>();

	if (checkIfKnown(string(w))) {
		listOfWords->insert(knownCorrectionsMap->find(string(w))->second);
		return listOfWords;
	}

	//if the correction is known, simply return it
	if (op == edb::SUBS) {
		oneDistanceReplacement(w, listOfWords);
	} else if (op == edb::SUBS2) {
		twoDistanceReplacement(w, listOfWords);
	} else if (op == edb::DEL) {
		singleDeletion(w, listOfWords);
	} else if (op == edb::INS) {
		singleInsertion(w, listOfWords);
	} else if (op == edb::TRANS) {
		transpose(w, listOfWords);
	}
	return listOfWords;
}

void edb::fillKnownCorrections(const char *pathToFile) 
{
	ifstream f(pathToFile);
	if (!f) {
		cout << "File cannot be opened!";
		return;
	}
	string mistake, correction;
	while (!f.eof()) {
		f >> mistake >> correction;
		knownCorrectionsMap->insert(make_pair(mistake, correction));
	}
	f.close();
}

//check if the word is a known error
bool edb::checkIfKnown(string w) 
{
	map<string, string>::iterator i = knownCorrectionsMap->find(w);
	if (i == knownCorrectionsMap->end()) {
		return false;
	} else {
		return true;
	}
}

void edb::oneDistanceReplacement(string str, set<string> *listOfWords) {
	char replacement[] = { "abcdefghijklmnopqrstuvwxyz" };
	int l = str.length();
	string strc = str;
	//           strcpy(strc, str);
	char temp;
	for (int i = 0; i < l; i++) { //for each character
		temp = strc[i];
		for (int j = 0; j < 26; j++) { //replace
			strc[i] = replacement[j];
			if (dict->search(strc)) {
				listOfWords->insert(string(strc));
			}
		}
		strc[i] = temp;
	}
}

void edb::twoDistanceReplacement(char *str, set<string> *listOfWords) 
{
	char replacement[] = { "abcdefghijklmnopqrstuvwxyz" };
	int l = strlen(str);
	char *strc = new char[l];
	strcpy(strc, str);
	char temp;
	for (int i = 0; i < l; i++) { //for each character
		temp = strc[i];
		for (int j = 0; j < 26; j++) { //replace
			strc[i] = replacement[j];
			oneDistanceReplacement(strc, listOfWords);
		}
		strc[i] = temp;
	}
}

void edb::transpose(char *str, set<string> *listOfWords) 
{
	int l = strlen(str);
    char temp;
	for (int i = 0; i < l - 1; i++) { //for each character
        temp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = temp;
	    if (dict->search(str)) {
            listOfWords->insert(string(str));
        }
        temp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = temp;
	}
}


//deletes one character at index pos
char* edb::deleteChar(char *str, int pos) 
{
	int l = strlen(str);
	char *strc = new char[l + 1];
	strcpy(strc, str);

	for (int i = pos; i < l; i++) {
		strc[i] = strc[i + 1];
	}
	strc[l - 1] = '\0';
	return strc;
}

void edb::singleDeletion(char *str, set<string> *listOfWords) 
{
	char *res;
	int l = strlen(str);
	for (int i = 0; i < l; i++) { //for each character
		if (dict->search(res = deleteChar(str, i))) {
			listOfWords->insert(string(res));
		}
		delete res;

	}
}

char *edb::insertCharAt(char *str, int pos, char c) 
{
	int l = strlen(str);
	char *mod = new char[l + 2];
	int i = 0;
	for (i = 0; i < pos; i++) {
		mod[i] = str[i];
	}
	mod[i++] = c;
	for (; i <= l; i++) {
		mod[i] = str[i - 1];
	}
	mod[i] = '\0';
	return mod;
}

void edb::singleInsertion(char *str, set<string> *listOfWords) 
{
	char alphabet[] = { "abcdefghijklmnopqrstuvwxyz" };
	char *res;
	int l = strlen(str);
	for (int i = 0; i <= l; i++) {
		for (int j = 0; j < 26; j++) {
			if (dict->search(res = insertCharAt(str, i, alphabet[j]))) {
				listOfWords->insert(string(res));
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

void printCorrections(set<string> *correction, int op) {

}

string correction(string ip, Ranker *r, string type, edb *nc)
{
    char input[90];
    strcpy(input, ip.c_str());
	int flag=0;

	set<string> *ins = NULL;
	set<string> *dels = NULL;
	set<string> *trans;
	set<string> *subs;
	set<string> *subs2;

		    ins = nc->correct(input, edb::INS);
			dels = nc->correct(input, edb::DEL);
			subs = nc->correct(input, edb::SUBS);
			trans = nc->correct(input, edb::TRANS);
			//subs2 = nc->correct(input, edb::SUBS2);
            std::map<double, string> *scoreString = new std::map<double, string>();
            int wc = 0;
            double score;
            for(set<string>::iterator it = ins -> begin(); it != ins -> end(); it++) {
                score = r -> rank(type, *it) + edb::ISCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }
            for(set<string>::iterator it = dels -> begin(); it != dels -> end(); it++) {
                score = r -> rank(type, *it) + edb::DSCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            for(set<string>::iterator it = trans -> begin(); it != trans -> end(); it++) {
                score = r -> rank(type, *it) + edb::TRANS;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            for(set<string>::iterator it = subs -> begin(); it != subs -> end(); it++) {
                score = r -> rank(type, *it) + edb::SSCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            /*
           for(set<string>::iterator it = subs2 -> begin(); it != subs2 -> end(); it++) {
                score = r -> rank(type, *it) + edb::S2SCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }
            */

          std::map<double, string>::reverse_iterator it = scoreString -> rbegin();
          if(scoreString -> empty()) {
              return "";
          }
           return (--scoreString->end()) -> second;
           delete ins, trans, subs, dels, scoreString;
	}

float percent(Ranker*, edb*);

int main(int argc, char *argv[]) {

	string wordListPath("../data/wordlist.txt");
	string knownCorrectionsFile("../data/knowncorrections.txt");
	edb *nc = new edb(wordListPath, knownCorrectionsFile);
	int flag=0;
    Ranker *r = new Ranker(string("../data/bicount.txt"), string("../data/out.txt")); 
    if(r == NULL || nc == NULL) {
        cout << "NPE\n!";
        return 0;
    }
    cout <<"\n\n% of words correctly corrected : "<<  percent(r, nc) << "%\n";
    
    return 0;

if(argc != 2) {
        cout << "Usage : ./edb [freq|bigram|help]\n";
        return 0;
    }
    if(!strcmp(argv[1], "help")) {
        cout << "Start the program by typing $./edb [freq|bigram]\n\n1. freq : The possible corrections are rated by considering which word has appeared most in the dictionary.\n\n2. bigram :Candidates are broken down into bigrams, the individual probabilities are then mulitiplied to get the frequency of the word\n";
        return 0;
    }
	char input[40];
    	set<string> *ins =new set<string>();
	set<string> *dels =new set<string>();
	set<string> *trans =new set<string>();
	set<string> *subs =new set<string>();
	set<string> *subs2 =new set<string>();

    while(1)
    {
		cout << "Enter the Word (q for Exit): ";
		cin >> input;
        cout << correction(input, r, "freq", nc) << endl;
       continue; 
		if(strcmp(input,"q") && strcmp(input,"Q")) {
            /*FILL ALL THE SETS*/
			ins = nc->correct(input, edb::INS);
			dels = nc->correct(input, edb::DEL);
			subs = nc->correct(input, edb::SUBS);
			trans = nc->correct(input, edb::TRANS);
			subs2 = nc->correct(input, edb::SUBS2);
            int wc = 0;
            std::map<double, string> *scoreString = new std::map<double, string>();
            double score;
            for(set<string>::iterator it = ins -> begin(); it != ins -> end(); it++) {
                score = r -> rank(argv[1], *it) + edb::ISCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            for(set<string>::iterator it = dels -> begin(); it != dels -> end(); it++) {
                score = r -> rank(argv[1], *it) + edb::DSCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            for(set<string>::iterator it = trans -> begin(); it != trans -> end(); it++) {
                score = r -> rank(argv[1], *it) + edb::TRANS;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

            for(set<string>::iterator it = subs -> begin(); it != subs -> end(); it++) {
                score = r -> rank(argv[1], *it) + edb::SSCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }

           for(set<string>::iterator it = subs2 -> begin(); it != subs2 -> end(); it++) {
                score = r -> rank(argv[1], *it) + edb::S2SCORE;
                if(scoreString -> find(score) == scoreString -> end()) { //not found
                    scoreString->insert(std::make_pair(score, *it));
                } else {
                    string temp = scoreString -> find(score) -> second;
                    scoreString->insert(std::make_pair(score, *it + temp));
                }
            }
            
           for(std::map<double, string>::reverse_iterator it = scoreString -> rbegin(); it != scoreString -> rend(); it++) {
               cout << it -> first << " " << it -> second << endl;
           }

           //now iterate through the dict and show the probables
       } else {
			return 0;
	   }
    }
	return 0;

}
/*Tester for edit distance based approach
 * MASSIVE TODO : Split it to other file
 */
float percent(Ranker *r, edb *e) // functions that calculate & return the required percentage
{
	  ifstream InputFile("data/knowncorrections.txt") ;
      if(!InputFile) { 
          return -1.0f;
      }

	  int total = -1, match = 0;
	  string inc_word,c_word,temp;
      int prev = 0, curr;
      string strLine;
      // Get every line
          int i = 0;
		while (!InputFile.eof() && getline (InputFile, strLine))
		{   
          total++;
          std::stringstream ssWordsBuf(strLine);
          ssWordsBuf >> inc_word;
		  ssWordsBuf >> c_word;
          std::transform(inc_word.begin(), inc_word.end(), inc_word.begin(), ::tolower);
          std::transform(c_word.begin(), c_word.end(), c_word.begin(), ::tolower);
		  temp = correction(inc_word, r, "freq", e);
		  //cout << inc_word << " " << c_word << " Got : " << temp << "\n";
          if(c_word == temp) {
			  match++;
          }
          curr = (float(total) / 4479) * 100;
          if(curr - prev > 10) {
             cout <<"Completed : "<< curr << "%| Score = "<< (float(match) / total) * 100<< "%\n";
             prev = curr;
		  }
        }

		float per = ((float)match/ total) * 100;
		InputFile.close ();
		return per;
}
