#include "peachdb.h"

int main() {
  // char *query = "select id, name from users where name = 'peach' and id !=
  // 100;";
  char *query = "select id, name from users;";
  Token *tokens = tokenize(query);
  Node *node = parse(tokens);

  printf("Hello, World!\n");
  return 0;
}
