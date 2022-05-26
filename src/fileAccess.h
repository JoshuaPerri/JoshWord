#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __GNUC__
	char* getWordAtIndex(int, char*);
#else
	__declspec(dllexport) char* getWordAtIndex(int, char*);
#endif
