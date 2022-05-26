#include "fileAccess.h"

char* getWordAtIndex(int index, char* filename) {
  FILE* input = NULL;

#ifdef __GNUC__
  input = fopen(filename, "r");
#else
  fopen_s(input, filename, "r");
#endif

  if (!input) {
    printf("Can't open file %s\n", filename);
    return(NULL);
  }

  int i = 0;
  char c;
  if (index != 0) {
    while ((c = fgetc(input)) != EOF) {
      if (c == '\n') {
        i++;
      }
      if (i >= index) {
        break;
      }
    }
  }

  i = 0;
  char buf[50];
  while ((c = fgetc(input)) != EOF) {
    buf[i++] = c;
    if (c == '\n') {
      buf[--i] = '\0';
      break;
    }
  }

  fclose(input);

  int length = i + 1;
  char* word = malloc(sizeof(char) * length);

#ifdef __GNUC__
  strcpy(word, buf);
#else
  strcpy_s(word, length, buf);
#endif

  return(word);
}
