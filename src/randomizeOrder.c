#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNumWords(FILE *file) {
  int i = 0;
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      i++;
    }
  }
  rewind(file);
  return(i);
}

void getWordAtIndex(int index, int flags[], FILE *input, FILE *output) {
  int unusedWordCount = 0;
  int wordCount = 0;
  char c;
  if (index != 0) {
    while ((c = fgetc(input)) != EOF) {
      // printf("Target: %d - %d - %d\n", index, wordCount, unusedWordCount);
      if (c == '\n') {
        if (flags[wordCount++] == 0) {
          unusedWordCount++;
        }
      }
      if (unusedWordCount >= index) {
        break;
      } 
    }

    flags[wordCount-1] = 1;
    char buf[50];
    int i = 0;
    while ((c = fgetc(input)) != EOF) {
      buf[i++] = c;
      if (c == '\n') {
        break;
      }
    }
    rewind(input);
    fwrite(buf, sizeof(char), i, output);
  }
}


int main(int argc, char *argv[]) {
  FILE *input;
  FILE *output;

  if (argc != 3) {
    printf("Incorrect number of arguments\nUsage: ./randomizeOrder /PATH/TO/WORDLIST /PATH/TO/OUTPUTFILE\n");
    return(1);
  }

  if (!(input = fopen(argv[1], "r"))) {
    printf("Can't open file %s\n", argv[1]);
    return(1);
  }
  if (!(output = fopen(argv[2], "w"))) {
    printf("Can't open file %s\n", argv[2]);
    return(1);
  }

  int length = getNumWords(input);

  int flags[length];
  for (int i = 0; i < length; i++) {
    flags[i] = 0;
  }

  printf("Checkpoint\n");
  int r;
  srand(11100);
  for (int i = length - 1; i > 0; i--) {
    r = (int) (((double)rand() / RAND_MAX) * (i - 2) + 1);
    // printf("%d\n", r);
    getWordAtIndex(r, flags, input, output);
  }

  fclose(input);
  fclose(output);
  return(0);
}
