#include "dictionary.h"

int main() {
  void* root = createTree();

  if (!root) {
    printf("Error generating dictionary tree\n");
    return(1);
  }

  FILE *dict = fopen("./text/dictionary.txt", "r");

  if (!dict) {
    printf("Error opening dictionary file\n");
    return(1);
  }

  char c;
  int i = 0;
  char buf[50];
  buf[0] = '\0';
  while ((c = fgetc(dict)) != EOF) {
    if (c == '\n' || c == '\r') {
      buf[i] = '\0';
      int ret = checkWord(root, buf, "HORSES");
      if (ret == 0) {
        printf("checkWord('%s') = %d\n", buf, ret);
      }
      i = 0;
    } else {
      buf[i++] = c;
    }
  }

  fclose(dict);
  freeTree(root);

  return(0);
}
