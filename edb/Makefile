edb : build/FrequencyCountModel.o build/Ranker.o build/WordDictionary.o build/edb.o build/BigramProbModel.o
	g++ -g -o edb build/FrequencyCountModel.o build/Ranker.o build/WordDictionary.o build/edb.o build/BigramProbModel.o -lgmpxx -lgmp

build/WordDictionary.o : WordDictionary.h WordDictionary.cpp
	g++ -c WordDictionary.cpp  && mv *.o build

build/edb.o : edb.cpp edb.h WordDictionary.h WordDictionary.cpp
	g++ -c edb.cpp  && mv *.o build

build/FrequencyCountModel.o  : FrequencyCountModel.h FrequencyCountModel.cpp
	g++ -c FrequencyCountModel.cpp && mv *.o build

build/BigramProbModel.o : BigramProbModel.cpp BigramProbModel.h
	g++ -c BigramProbModel.cpp -lgmpxx -lgmp && mv *.o build

build/Ranker.o :Ranker.cpp Ranker.h
	g++ -c Ranker.cpp && mv *.o build

clean:
	rm build/*.o
