#include "peachdb.h"

int main() {
  // "select id, name from users where name = 'peach' and id != 100;";

  yyparse();

  printf("Hello, World!\n");
  return 0;
}
