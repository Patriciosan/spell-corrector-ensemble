#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <stdlib.h>

using namespace std;
map<string, int> wordCount;
map<int, string> mwords;

class TrigramSpellCheckerCount {
private:
public:
	void findWord(string);
	void spiltAndCount(string, char);
	string toLowerCase(string str);
	int checkSpelling();
};

void TrigramSpellCheckerCount::findWord(string incorrectWord) {
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

	map<string, int>::iterator iter;
	int max = -1;
	string matchwords = "";

	for (iter = wordCount.begin(); iter != wordCount.end(); iter++) {
		if (iter->first.length() > incorrectWord.length() - 1
				&& iter->first.length() < incorrectWord.length() + 2) {
			if (iter->second > max) {
				mwords.clear();
				mwords.insert(make_pair(iter->second, iter->first));
				matchwords = iter->first;
				max = iter->second;
			} else if (iter->second == max) {
				matchwords = matchwords + "\n" + iter->first;
				mwords.insert(make_pair(iter->second, iter->first));
			}
		}

	}
	cout << "Suggested Words are : \n" << matchwords << "\n";
	wordCount.clear();

}
void TrigramSpellCheckerCount::spiltAndCount(string line, char delimeter) {
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

			if (wordCount.count(word) > 0) {
				wordCount[word]++;

			} else {
				wordCount.insert(make_pair(word, 1));

			}
		}

	}

}

string TrigramSpellCheckerCount::toLowerCase(std::string str) {
	const int length = str.length();
	for (int i = 0; i < length; ++i) {
		str[i] = std::tolower(str[i]);
	}

	return str;
}

int TrigramSpellCheckerCount::checkSpelling() {
	TrigramSpellCheckerCount *t = new TrigramSpellCheckerCount();
	string incorrectWord;
	cout << "\n\n************************Frequency Based Trigram Analysis***********************"<<endl;
	while (1) {
		cout<<endl<<"Enter the Word (Press q for Main Menu) : ";
		cin >> incorrectWord;
		if (incorrectWord != "q" && incorrectWord != "Q") {
			incorrectWord = t->toLowerCase(incorrectWord);
			t->findWord(incorrectWord);
		} else {
			return 0;
		}
	}

	return 0;
}

