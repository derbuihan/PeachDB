#include <stdio.h>

#include "peachdb.h"

int main() {
  char *query = "select * from users where name = 'peach' and id = 100;";
  Token *tokens = tokenize(query);

  printf("Hello, World!\n");
  return 0;
}
