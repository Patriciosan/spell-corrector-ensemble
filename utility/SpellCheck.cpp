#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

map<string, int> dictionary;
bool findValue(char* s);
int main() {
	string parseLine;
	ifstream infile("naman.txt");

	while (!infile.eof()) {

		infile >> parseLine;
		dictionary.insert(make_pair(parseLine, 1));

	}

	infile.close();

	if (findValue("zulu")) {
		cout << "Found";
	} else {
		cout << "notfound";
	}


	return 0;

}

bool findValue(char* s) {

	string str(s);
	map<string, int>::iterator i = dictionary.find(str);

	if (i == dictionary.end()) {
		return false;
	} else {
		return true;
	}
}

