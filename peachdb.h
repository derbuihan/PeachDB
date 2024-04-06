#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tokenizer

typedef enum {
  TK_IDENT,    // identifier (column name, table name, etc)
  TK_KEYWORD,  // keyword (SELECT, FROM, WHERE, etc)
  TK_PUNCT,    // punctuation (*, =, etc)
  TK_NUM,      // number (123, 0x123, etc)
  TK_STR,      // string literal
  TK_EOF,      // end of file
} TokenKind;

typedef struct Token Token;
struct Token {
  Token *next;
  TokenKind kind;
  char *loc;
  unsigned long val;  // if kind is TK_NUM
  char *str;          // if kind is TK_STR
  int len;            // Token length
};

Token *tokenize(char *str);

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
  Token *token;
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

Node *parse(Token *tok);
