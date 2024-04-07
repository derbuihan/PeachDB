#include "peachdb.h"

void execute_select_stmt(Node *stmt) {
  unsigned long size = get_size(FILENAME);
  User users[size];
  load_storage(FILENAME, users, size);

  for (int i = 0; i < size; i++) {
    printf("%d, %s\n", users[i].id, users[i].name);
  }
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
