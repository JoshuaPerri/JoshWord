#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void toUppercase(char *word) {
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') {
      word[i] -= 32;
    }
  }
}

int isValidWord(char *word, FILE *dict) {
  int i = 0;

  printf("Checking %s\n", word);

  char c;
  char buf[50];
  buf[0] = '\0';
  while ((c = fgetc(dict)) != EOF) {
    if (c == '\n' || c == '\r') {
      buf[i] = '\0';
      if (strcmp(word, buf) == 0) {
        rewind(dict);
        return(1);
      }
      i = 0;
    } else {
      buf[i++] = c;
    }
  }
  
  rewind(dict);
  return(0);
}

int main(int argc, char *argv[]) {
  FILE *input;
  FILE *dict;
  FILE *output;

  if (argc != 4) {
    printf("Incorrect number of arguments\nUsage: ./removeNames /PATH/TO/WORDLIST /PATH/TO/DICTIONARY /PATH/TO/OUTPUTFILE\n");
    return(1);
  }

  if (!(input = fopen(argv[1], "r"))) {
    printf("Can't open file %s\n", argv[1]);
    return(1);
  }
  if (!(dict = fopen(argv[2], "r"))) {
    printf("Can't open file %s\n", argv[2]);
    return(1);
  }
  if (!(output = fopen(argv[3], "w"))) {
    printf("Can't open file %s\n", argv[3]);
    return(1);
  }

  char buf[50];
  int i = 0;
  char c;
  while ((c = fgetc(input)) != EOF) {
    // printf("%d - %c\n", i, c);
    if (c != '\n') {
      if (c == '\r') {
        buf[i] = '\0';
        toUppercase(buf);
        // printf("%s\n", buf);
        if (isValidWord(buf, dict)) {
          buf[i] = '\n';
          fwrite(buf, sizeof(char), i+1, output);

          // clear the \n char
          // fgetc(input);
        }
        i = 0;
      } else {
        buf[i++] = c;
      }
    }
  }

  fclose(input);
  fclose(dict);
  fclose(output);
  return(0);
}
