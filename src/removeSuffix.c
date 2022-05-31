#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hasSuffix(char *word, int length) {
  //printf("Word = %s\n", word);

  // check 's'
  //printf(" word[%d] = %c\n", length, word[length]);
  if (word[length] == 'S') {
    return(1);
  }

  // check 'ed'
  if (word[length] == 'D' && word[length-1] == 'E') {
    return(1);
  }

  // check 'ing'
  if (word[length] == 'G' && word[length] == 'N'  && word[length] == 'I') {
    return(1);
  }

  return(0);
}

int main(int argc, char *argv[]) {
  FILE *input;
  FILE *output;

  if (argc != 3) {
    printf("Incorrect number of arguments\nUsage: ./removeSuffix /PATH/TO/WORDLIST /PATH/TO/OUTPUTFILE\n");
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

  char buf[50];
  int i = 0;
  char c;
  while ((c = fgetc(input)) != EOF) {
    if (c == '\n') {
      buf[i] = '\0';
      if (!hasSuffix(buf, i-1)) {
        buf[i] = '\n';
        fwrite(buf, sizeof(char), i+1, output);
      }
      i = 0;
    } else {
      buf[i++] = c;
    }
  }

  fclose(input);
  fclose(output);
  return(0);
}
