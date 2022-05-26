#include "dictionary.h"

Letter *createLetter(char c) {
  Letter *letter = malloc(sizeof(Letter));

  if (letter == NULL) {
    return(NULL);
  }

  letter->c = c;
  letter->numChildren = 0;
  letter->isEnd = 0;
  letter->children = NULL;

  return(letter);
}

void addLetter(Letter *target, Letter *toAdd) {
  target->numChildren++;

  Letter** temp = target->children;

  target->children = realloc(target->children , sizeof(Letter*) * target->numChildren);

  if (target->children == NULL) {
    for (int i = 0; i < target->numChildren-1; i++) {
      freeStruct(temp[i]);
    }
    free(temp);
    return;
  }

  target->children[target->numChildren - 1] = toAdd;
}

void freeStruct(Letter *letter) {
  for (int i = 0; i < letter->numChildren; i++) {
    freeStruct(letter->children[i]);
  }
  free(letter->children);
  free(letter);
}

Letter *contains(Letter *target, char c) {
  for (int i = 0; i < target->numChildren; i++) {
    if (target->children[i]->c == c) {
      return(target->children[i]);
    }
  }
  return(NULL);
}

char generateTree(Letter *current, FILE *file) {
  char c = fgetc(file);

  if (c == EOF) {
    return(EOF);
  }

  if (c != '\n') {
    Letter *next = contains(current, c);
    if (!next) {
      next = createLetter(c);
      addLetter(current, next);
    }
    return(generateTree(next, file));
  } else {
    current->isEnd = 1;
    return('\n');
  }
}

void printLetters(Letter *current, int spaces) {
  for (int i = 0; i < spaces; i++) {
    printf(" ");
  }
  printf("%c\n", current->c);
  for (int i = 0; i < current->numChildren; i++) {
    printLetters(current->children[i], spaces + 1);
  }
}

// The three externally used functions are below

/* Ret 0 if 'guess' is not a real word
 * Ret 1 if 'guess' is 'answer'
 * Ret 2 if 'guess' is above 'answer'
 * Ret 3 if 'guess' is below 'answer'
 */
int checkWord(void *root, char *guess, char *answer) {
  if (strcmp(guess, answer) == 0) {
    return(1);
  }

  int noChild;
  int state = 0;
  Letter *current = (Letter*) root;

  int i;
  for (i = 0; guess[i] != '\0'; i++) {
    noChild = 1;

    if (!state) {
      if (guess[i] > answer[i]) {
        state = 2;
      } else if (guess[i] < answer[i]) {
        state = 3;
      }
    }

    for (int j = 0; j < current->numChildren; j++) {
      if (current->children[j]->c == guess[i]) {
        current = current->children[j];
        noChild = 0;
        break;
      }
    }
    if (noChild) {
      return(0);
    }
  }

  if (!state) {
    if (guess[i] =='\0') {
      state = 3;
    }
  }

  if (current->isEnd) {
    return(state);
  } else {
    return(0);
  }
}

void* createTree() {
  FILE *file;

#ifdef __GNUC__
  file = fopen("./text/dictionary.txt", "r");
#else
  fopen_s(&file, "./text/dictionary.txt", "r");
#endif

  if (!file) {
    printf("Error: File 'dictionary.txt' did not open properly\n");
    return(0);
  }

  Letter* root = createLetter(' ');
  while (generateTree(root, file) != EOF);

  fclose(file);

  return((void*)root);
}

void freeTree(void* rootInt) {
  Letter* root = (Letter*) rootInt;
  freeStruct(root);
}
