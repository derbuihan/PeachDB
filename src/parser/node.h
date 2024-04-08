#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

typedef enum NodeKind NodeKind;
enum NodeKind {
  ND_SELECT,  // SELECT statement
  ND_INSERT,  // INSERT statement
  ND_DELETE,  // DELETE statement
  ND_UPDATE,  // UPDATE statement
  ND_COLUMN,  // Column name
  ND_VALUE,   // Value
  ND_IDENT,   // Identifier
  ND_STRING,  // String literal
  ND_NUMBER,  // Number
  ND_TABLE,   // Table name
  ND_WHERE,   // WHERE clause
  ND_COND,    // Condition
  ND_COMP,    // Comparison
  ND_ADD,     // +
  ND_SUB,     // -
  ND_EQ,      // =
  ND_NE,      // !=
  ND_AND,     // AND
  ND_OR,      // OR
};

typedef struct Node Node;
struct Node {
  NodeKind kind;

  int intval;    // ND_NUMBER
  char *strval;  // ND_STRING
  char *ident;   // ND_IDENT

  // ND_COLUMN, ND_VALUE
  Node *list_next;
  Node *list_value;

  // ND_TABLE
  Node *table_name;

  // ND_COLUMN
  Node *columns;

  // ND_WHERE
  Node *where_clause;

  // ND_VALUE
  Node *values;

  // ND_ADD, ND_SUB, ND_AND, ND_OR, ND_EQ, ND_NE
  Node *lhs;
  Node *rhs;
};

Node *new_num_node(int value);
Node *new_op_node(NodeKind kind, Node *left, Node *right);
Node *new_str_node(char *string);
Node *new_id_node(char *ident);
Node *new_select_node(Node *table_name, Node *column_list, Node *where_clause);
Node *new_insert_node(Node *table_name, Node *column_list, Node *value_list);
Node *new_column_list_node(Node *column_name, Node *next);
Node *new_value_list_node(Node *value, Node *next);

#endif  // NODE_H_
