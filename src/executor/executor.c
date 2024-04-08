#include "peachdb.h"

void execute_select(Node *stmt) {
  unsigned long size = get_size(FILENAME);
  User users[size];
  load_storage(FILENAME, users, size);

  for (int i = 0; i < size; i++) {
    printf("%d, %s\n", users[i].id, users[i].name);
  }
}

void execute_insert(Node *stmt) {
  unsigned long size = get_size(FILENAME);
  User users[size];
  load_storage(FILENAME, users, size);

  int id = stmt->values->list_value->intval;
  char *name = stmt->values->list_next->list_value->strval;
  User user;
  user.id = id;
  strcpy(user.name, name);

  users[size] = user;
  init_storage(FILENAME, users, size + 1);
}

void execute(Node *stmt) {
  switch (stmt->kind) {
    case ND_SELECT:
      execute_select(stmt);
      break;
    case ND_INSERT:
      execute_insert(stmt);
      break;
    default:
      printf("Unknown statement\n");
      exit(1);
  }
}
