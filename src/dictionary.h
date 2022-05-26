
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char c;
  int numChildren;
  int isEnd;
  struct Node **children;
} Letter;


#ifdef __GNUC__

	Letter *createLetter(char);
  void addLetter(Letter*, Letter*);
  void freeStruct(Letter*);
  Letter *contains(Letter*, char);
  char generateTree(Letter*, FILE*);
  void printLetters(Letter*, int);
  int isWord(Letter*, char*);
  int checkWord(void*, char*, char*);
  void* createTree();
  void freeTree(void*);

#else

  #ifdef __cplusplus  
  extern "C" {
  #endif

  Letter *createLetter(char);
  void addLetter(Letter*, Letter*);
  void freeStruct(Letter*);
  Letter *contains(Letter*, char);
  char generateTree(Letter*, FILE*);
  void printLetters(Letter*, int);
  int isWord(Letter*, char*);
	__declspec(dllexport) int checkWord(void*, char*, char*);
  __declspec(dllexport) void* createTree();
  __declspec(dllexport) void freeTree(void*);

  #ifdef __cplusplus  
  }
  #endif

#endif
