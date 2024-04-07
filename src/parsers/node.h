#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

// Parser
typedef enum {
  ND_SELECT,  // SELECT statement
  ND_INSERT,  // INSERT statement
  ND_DELETE,  // DELETE statement
  ND_UPDATE,  // UPDATE statement
  ND_COLUMN,  // Column name
  ND_VALUE,   // Value
  ND_EXPR,    // Expression
  ND_IDENT,   // Identifier
  ND_STRING,  // String literal
  ND_NUMBER,  // Number
  ND_TABLE,   // Table name
  ND_WHERE,   // WHERE clause
  ND_COND,    // Condition
  ND_COMP,    // Comparison
  ND_OP,      // Operator
  ND_AND,     // AND
  ND_OR,      // OR
  ND_EOF,     // End of file
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind;
  Node *next;

  // Statement
  Node *table_name;
  Node *select_list;
  Node *where_clause;

  // Expr
  Node *lhs;
  Node *rhs;

  // number
  int value;

  // String literal
  char *string;

  // Column name
  Node *column_name;

  // Operator
  char *op;
};

Node *new_num_node(int value);
Node *new_op_node(char *op, Node *left, Node *right);
Node *new_str_node(char *string);
Node *new_id_node(char *ident);
Node *new_select_node(Node *table_name, Node *column_list, Node *where_clause);
Node *new_column_list_node(Node *column_name, Node *next);

#endif  // NODE_H_
