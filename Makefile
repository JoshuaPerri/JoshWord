CC=gcc
CFLAGS=-Wall -pedantic

all: bin/removeNames bin/randomizeOrder

bin/testFileAccess: src/fileAccess.c src/testFileAccess.c 
	$(CC) $(CFLAGS) -o bin/testFileAccess src/testFileAccess.c src/fileAccess.c 

bin/testDictionary: src/dictionary.c src/testDictionary.c 
	$(CC) $(CFLAGS) -o bin/testDictionary src/testDictionary.c src/dictionary.c 

bin/removeNames: src/removeNames.c
	$(CC) $(CFLAGS) -o bin/removeNames src/removeNames.c

bin/randomizeOrder: src/randomizeOrder.c
	$(CC) $(CFLAGS) -o bin/randomizeOrder src/randomizeOrder.c

clean:
	rm bin/testFileAccess bin/testDictionary bin/removeNames bin/randomizeOrder