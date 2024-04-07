#include "peachdb.h"

void execute_select_stmt(Node *stmt) {
  printf("SELECT\n");
  return;
}

void execute(Node *stmt) {
  switch (stmt->kind) {
    case ND_SELECT:
      execute_select_stmt(stmt);
      break;
    default:
      exit(1);
  }
}
