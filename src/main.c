#include "peachdb.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    yy_scan_string(argv[1]);
  }

  User users[] = {
      {1, "Alice"},
      {2, "Bob"},
      {3, "Charlie"},
  };
  init_storage(FILENAME, users, sizeof(users) / sizeof(User));

  Node *node = NULL;
  yyparse(&node);
  execute(node);

  printf("Hello, World!\n");
  return 0;
}