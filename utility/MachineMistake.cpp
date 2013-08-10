//This Programs splits the File into 2 parts based on some delimeter.

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
	ifstream inFile("mistakes.txt");
	ofstream outLeft("mistakes_left.txt");
	ofstream outright("mistakes_right.txt");
	string lines;
	if (!inFile) {
		cout << "akudhahsdl";
	}
	int total = 0;

	getline(inFile, lines);
	int pos = lines.find("->");
	while (pos > -1) {

		//cout<<"Line"<<lines<<"     Position -->"<<pos<<"\n";

		string freq1 = lines.substr(0, pos);
		string freq2 = lines.substr(pos+2, lines.length());

		getline(inFile, lines);
		pos = lines.find("->");

		outLeft<<freq1<<"\n";
		outright<<freq2<<"\n";

	}

	outLeft.close();
	outright.close();
	inFile.close();

	return 0;
}
