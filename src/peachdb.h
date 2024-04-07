#include <stdio.h>

#include "lexer.yy.h"
#include "node.h"
#include "parser.tab.h"

#define FILENAME "data.bin"

void execute(Node *stmt);

typedef struct User User;
struct User {
  int id;
  char name[10];
};

void init_storage(char *filename, User *users, int size);
unsigned long get_size(char *filename);
void load_storage(char *filename, User *users, unsigned long size);
