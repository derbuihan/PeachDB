#include "node.h"

static Node *new_node() {
  Node *node = calloc(1, sizeof(Node));
  return node;
}

Node *new_num_node(int value) {
  Node *node = new_node();
  node->value = value;
  return node;
}
Node *new_op_node(char op, Node *left, Node *right) {
  Node *node = new_node();
  node->op = op;
  node->left = left;
  node->right = right;
  return node;
}
