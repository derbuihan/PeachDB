#include "node.h"

static Node *new_node(NodeKind kind) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  return node;
}

Node *new_num_node(int value) {
  Node *node = new_node(ND_NUMBER);
  node->intval = value;
  return node;
}

Node *new_str_node(char *string) {
  Node *node = new_node(ND_STRING);
  node->strval = string;
  return node;
}

Node *new_id_node(char *ident) {
  Node *node = new_node(ND_IDENT);
  node->ident = ident;
  return node;
}

Node *new_op_node(NodeKind kind, Node *left, Node *right) {
  Node *node = new_node(kind);
  node->lhs = left;
  node->rhs = right;
  return node;
}

Node *new_select_node(Node *table_name, Node *column_list, Node *where_clause) {
  Node *node = new_node(ND_SELECT);
  node->table_name = table_name;
  node->columns = column_list;
  node->where_clause = where_clause;
  return node;
}

Node *new_insert_node(Node *table_name, Node *column_list, Node *value_list) {
  Node *node = new_node(ND_INSERT);
  node->table_name = table_name;
  node->columns = column_list;
  node->values = value_list;
  return node;
}

Node *new_column_list_node(Node *column_name, Node *next) {
  Node *node = new_node(ND_COLUMN);
  node->list_value = column_name;
  node->list_next = next;
  return node;
}

Node *new_value_list_node(Node *value, Node *next) {
  Node *node = new_node(ND_VALUE);
  node->list_value = value;
  node->list_next = next;
  return node;
}
