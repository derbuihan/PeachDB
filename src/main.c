#include "peachdb.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    yy_scan_string(argv[1]);
  }

  Node *stmt = NULL;
  yyparse(&stmt);
  execute(stmt);

  printf("Hello, World!\n");
  return 0;
}
