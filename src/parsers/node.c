#include "node.h"

static Node *new_node(NodeKind kind) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  return node;
}

Node *new_num_node(int value) {
  Node *node = new_node(ND_NUMBER);
  node->value = value;
  return node;
}

Node *new_str_node(char *string) {
  Node *node = new_node(ND_STRING);
  node->string = string;
  return node;
}

Node *new_id_node(char *ident) {
  Node *node = new_node(ND_IDENT);
  node->string = ident;
  return node;
}

Node *new_op_node(char *op, Node *left, Node *right) {
  Node *node = new_node(ND_OP);
  node->op = op;
  node->lhs = left;
  node->rhs = right;
  return node;
}

Node *new_select_node(Node *table_name, Node *column_list, Node *where_clause) {
  Node *node = new_node(ND_SELECT);
  node->table_name = table_name;
  node->select_list = column_list;
  node->where_clause = where_clause;
  return node;
}

Node *new_column_list_node(Node *column_name, Node *next) {
  Node *node = new_node(ND_COLUMN);
  node->column_name = column_name;
  node->next = next;
  return node;
}
