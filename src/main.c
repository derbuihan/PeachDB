#include "peachdb.h"

int main(int argc, char *argv[]) {
  // "select id, name from users where name = 'peach' and id != 100;";
  Node *node = NULL;

  if (argc > 1) {
    yy_scan_string(argv[1]);
  }

  yyparse(&node);

  printf("Hello, World!\n");
  return 0;
}
