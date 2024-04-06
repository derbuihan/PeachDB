#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

// Tokenizer
typedef struct Token Token;
struct Token {
  unsigned int val;
  char *str;
};

// Parser
typedef struct Node Node;
struct Node {
  int value;
  char op;
  Node *left;
  Node *right;
};

Node *new_num_node(int value);
Node *new_op_node(char op, Node *left, Node *right);

#endif  // NODE_H_
