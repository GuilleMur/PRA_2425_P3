bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp
bin/testHashTable: testHashTable.cpp TableEntry.h Dict.h HashTable.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp
clean:
	rm -rf *.o *.gch bin