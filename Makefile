CC=gcc
CFLAGS=-Wall -pedantic

all: bin/removeNames bin/randomizeOrder

bin/testFileAccess: src/fileAccess.c src/testFileAccess.c 
	$(CC) $(CFLAGS) -o bin/testFileAccess src/testFileAccess.c src/fileAccess.c 

bin/testDictionary: src/dictionary.c src/testDictionary.c 
	$(CC) $(CFLAGS) -o bin/testDictionary src/testDictionary.c src/dictionary.c 

bin/removeNames: src/removeNames.c
	$(CC) $(CFLAGS) -o bin/removeNames src/removeNames.c

bin/removeSuffix: src/removeSuffix.c
	$(CC) $(CFLAGS) -o bin/removeSuffix src/removeSuffix.c

bin/randomizeOrder: src/randomizeOrder.c
	$(CC) $(CFLAGS) -o bin/randomizeOrder src/randomizeOrder.c

bin/dictionary.so: bin/dictionary.o
	$(CC) $(CFLAGS) -shared -o bin/dictionary.so bin/dictionary.o

bin/dictionary.o: src/dictionary.c
	$(CC) $(CFLAGS) -c -o bin/dictionary.o src/dictionary.c

bin/fileAccess.so: bin/fileAccess.o
	$(CC) $(CFLAGS) -shared -o bin/fileAccess.so bin/fileAccess.o

bin/fileAccess.o: src/fileAccess.c
	$(CC) $(CFLAGS) -c -o bin/fileAccess.o src/fileAccess.c

clean:
	rm bin/testFileAccess bin/testDictionary bin/removeNames bin/randomizeOrder