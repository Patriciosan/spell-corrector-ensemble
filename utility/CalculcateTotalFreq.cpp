//Calculates the Total Frequency from the file having frequency of individual Words.

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

int main() {
	ifstream inFile("out.txt");

	string lines;
	string freq;
	map<string, int>::iterator iter;
	string strToReturn; //This is no longer on the heap

	int total = 0;

	getline(inFile, lines);
	int pos = lines.find(" ");
	while (pos > -1) {

		string freq = lines.substr(pos, lines.length());

		char * S = new char[freq.length() + 1];
		std::strcpy(S, freq.c_str());

		total = total + atoi(S);

		getline(inFile, lines);
		pos = lines.find(" ");

	}

	cout << total << "\n";

	return 0;
}

