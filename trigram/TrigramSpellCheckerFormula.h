#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <stdlib.h>
#include <iomanip>


using namespace std;
map<string, int> wordCounts;
map<float, string> temp;

class TrigramSpellCheckerFormula {
private:
public:
	void findWord(string);
	void spiltAndCount(string, char);
	string toLowerCase(string str);
	void computeRank(string);
	int checkSpelling();

};

void TrigramSpellCheckerFormula::findWord(string incorrectWord) {
	ifstream infile;

	int length = incorrectWord.length();
	string trigram;
	for (int i = 0; i < length - 2; i++) {
		trigram = incorrectWord.substr(i, 3);
		infile.open("../data/Trigrams.txt");
		while (infile.good()) {
			string line = "";
			getline(infile, line);
			if (line.substr(0, 3) == trigram && line.length() > 4) {
				string test = line.substr(4, line.length() - 1);
				spiltAndCount(test, ',');
			}
		}
		infile.close();
	}
}
void TrigramSpellCheckerFormula::spiltAndCount(string line, char delimeter) {
	int posBeg = 0;
	int posEnd = 0;
	int flag = 0;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] != delimeter && line[i] != '\0') {
			posEnd++;
		} else {

			string word = line.substr(posBeg, posEnd);
			posBeg = i + 1;
			posEnd = 0;

			if (wordCounts.count(word) > 0) {
				wordCounts[word]++;

			} else {
				wordCounts.insert(make_pair(word, 1));

			}
		}

	}

}

string TrigramSpellCheckerFormula::toLowerCase(std::string str) {
	const int length = str.length();
	for (int i = 0; i < length; ++i) {
		str[i] = std::tolower(str[i]);
	}

	return str;
}

void TrigramSpellCheckerFormula::computeRank(string incorrectWord) {
	map<string, int>::iterator iter;
	for (iter = wordCounts.begin(); iter != wordCounts.end(); iter++) {

		if(iter->first=="therr")
		{
		cout<<" Count == " <<iter->second;
		}		
		float abc = ((float) (2 * iter->second)
				/ (incorrectWord.length() - 2 + (iter->first).length() - 2));

		string word = temp[abc];
		word = word + "," + iter->first;
		temp[abc] = word;

	}

}

int TrigramSpellCheckerFormula::checkSpelling() {
	TrigramSpellCheckerFormula *t = new TrigramSpellCheckerFormula();
	string incorrectWord;
	system("clear");
	cout << "\n\n************Spell Correction Using Trigram Similarity Analysis*************";
	
	while (1) {
		cout <<endl<< "\n\nEnter the Word (Press q for Main Menu) : ";
		cin >> incorrectWord;
		cout<<endl;
		if (incorrectWord != "q" && incorrectWord != "Q") {
			incorrectWord = t->toLowerCase(incorrectWord);
			t->findWord(incorrectWord);
			t->computeRank(incorrectWord);
			wordCounts.clear();
			map<float, string>::reverse_iterator iter;
			int flag = 1;
			if(!temp.empty())
			{
				cout <<"Rank   |       Score       |          Suggested Words"<<endl;
				cout <<"----------------------------------------------------------------";
			}
			else
			{
			  cout<<"No Solution";	
			}	
			for (iter = temp.rbegin(); iter != temp.rend(); iter++) {
				cout.precision(8);
				if (flag < 3) {
					cout << endl<<flag++ << "      |     "<<right<<setw(10)<<iter->first << "    |       "<< iter->second.substr(1, iter->second.length());
							
				} else {
					temp.clear();
					break;
				}
			}
		} else {
			temp.clear();
			return 0;
		}
	}
	
	return 0;
}

