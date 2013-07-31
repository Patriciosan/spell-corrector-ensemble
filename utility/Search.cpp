#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
	string search, line;
	ifstream inFile("out.txt");

	cout << "Enter the word";
	cin >> search;
	int flag = 0;
	while (inFile.good()) {
		getline(inFile, line); // get line from file
		int pos = line.find(search); // search

		if (pos > -1
				&& (search.length() == line.substr(0, line.find(" ")).length())) // string::npos is returned if string is not found
				{
			flag = 1;
			break;
		}
	}

	if (flag == 1) {
		cout << std::endl << "Found \n";
		string freq=line.substr(line.find(" "), line.length());
		char * S = new char[freq.length() + 1];
		std::strcpy(S,freq.c_str());
		;
		cout << "Frequency  " <<atoi(S)  << "\n\n";

	} else {
		cout << std::endl << "Not Found";
	}

	return 0;
}
