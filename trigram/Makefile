edb : FrequencyCountModel.o WordDictionary.o edb.o BigramProbModel.o
	g++ -o edb FrequencyCountModel.o WordDictionary.o edb.o BigramProbModel.o -lgmpxx -lgmp && mv *.o build
WordDictionary.o : WordDictionary.h WordDictionary.cpp
	g++ -c WordDictionary.cpp 
edb.o : edb.cpp edb.h WordDictionary.h WordDictionary.cpp
	g++ -c edb.cpp 
FrequencyCountModel.o  : FrequencyCountModel.h FrequencyCountModel.cpp
	g++ -c FrequencyCountModel.cpp

BigramProbModel.o : BigramProbModel.cpp BigramProbModel.h
	g++ -c BigramProbModel.cpp -lgmpxx -lgmp


clean:
	rm build/*.o
