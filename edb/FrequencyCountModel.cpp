#include "FrequencyCountModel.h"

using namespace std;

static map<string,int> frequencyCounterMap;


FrequencyCountModel::FrequencyCountModel(string pathToFile)
{ 
	populateFrequencyCounterMap(pathToFile);
}
	
float FrequencyCountModel::getTotalFrequency() {
	return 18302813.0f;
}

void FrequencyCountModel::populateFrequencyCounterMap(string pathToFile) {
	int flag = 0;
	string parseLine;
	ifstream inFile;
	inFile.open(pathToFile.c_str());
    if(!inFile) {
        cerr << "File missing!\n";
        return;
    }

	while (inFile.good()) {
		getline(inFile, parseLine);
		int pos=parseLine.find(" ");
		if(pos > -1)
		{	
			string word = parseLine.substr(0,pos);			
			string freq = parseLine.substr(pos, parseLine.length());
			char * S = new char[freq.length() + 1];
			std::strcpy(S, freq.c_str());
			int frequency= atoi(S);
			frequencyCounterMap.insert(make_pair(word,frequency));
		}
		
	
	}
	inFile.close();
}


float FrequencyCountModel::wordProb(string word) {
	if(frequencyCounterMap.count(word) >0)
	{
		int frq= frequencyCounterMap[word];
		float probability = (float)frq/getTotalFrequency();
		return probability;
	}
	
	return 0.0f;
}





