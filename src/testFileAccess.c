#include "fileAccess.h"

int main() {
  char *word;
  for (int i = 0; i < 2042; i++) {
    word = getWordAtIndex(i, "./text/words-long-random.txt");
    printf("[%d] %s\n", i, word);
    free(word);
  }
}