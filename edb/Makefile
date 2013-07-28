edb : WordDictionary.o edb.o
	g++ -o edb WordDictionary.o edb.o && mv *.o build
WordDictionary.o : WordDictionary.h WordDictionary.cpp
	g++ -c WordDictionary.cpp 
edb.o : edb.cpp edb.h WordDictionary.h WordDictionary.cpp
	g++ -c edb.cpp 

clean:
	rm build/*.o
