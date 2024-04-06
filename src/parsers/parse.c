#include "peachdb.h"

static void error_tok(Token *tok, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, " at %s\n", tok->loc);

  exit(1);
}

static bool equal(Token *tok, char *str) {
  return strncmp(tok->loc, str, tok->len) == 0 && str[tok->len] == '\0';
}

static Token *skip(Token *tok, char *str) {
  if (!equal(tok, str)) {
    error_tok(tok, "expected '%s'", str);
  }
  return tok->next;
}

static bool consume(Token **rest, Token *tok, char *str) {
  if (strncmp(tok->loc, str, tok->len) == 0) {
    *rest = tok->next;
    return true;
  }
  return false;
}

static Node *new_node(NodeKind kind, Token *tok) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  node->token = tok;
  return node;
}

/*
 * <stmt> ::= <select_stmt> | <insert_stmt> | <delete_stmt> | <update_stmt>
 * <select_stmt> ::= "select" <column_list> "from" <table_name> [<where_clause>]
 * <column_list> ::= "*" | <column_name> ["," <column_list>]
 * <where_clause> ::= "where" <condition>
 * <condition> ::= <comparison> | <condition> "and" <condition>
 *                              | <condition> "or" <condition>
 * <comparison> ::= <column_name> <op> <value>
 * <op> ::= "=" | "!="
 * <value> ::= <number> | <string> | <column_name>
 * <number> ::= [0-9]+
 * <string> ::= "'" [^']* "'"
 * <column_name> ::= [a-zA-Z_][a-zA-Z0-9_]
 * <table_name> ::= [a-zA-Z_][a-zA-Z0-9_]
 */

static Node *value(Token **rest, Token *tok) {
  Node *node = new_node(ND_VALUE, tok);
  return node;
}

static Node *comparison(Token **rest, Token *tok) {
  Node *node = new_node(ND_EXPR, tok);
  return node;
}

static Node *condition(Token **rest, Token *tok) {
  Node *node = new_node(ND_EXPR, tok);
  return node;
}

static Node *select_list(Token **rest, Token *tok) {
  Node head = {};
  Node *cur = &head;

  while (tok->kind == TK_IDENT) {
    Node *node = new_node(ND_COLUMN, tok);
    node->column_name = strndup(tok->loc, tok->len);

    cur = cur->next = node;
    if (!consume(&tok, tok->next, ",")) {
      break;
    }
  }
  *rest = tok->next;
  return head.next;
}

static char *table_name(Token **rest, Token *tok) {
  if (tok->kind != TK_IDENT) error_tok(tok, "expected an identifier");
  *rest = tok->next;
  return strndup(tok->loc, tok->len);
}

static Node *where_clause(Token **rest, Token *tok) {
  if (!consume(&tok, tok, "where")) {
    error_tok(tok, "expected 'where'");
  }
  Node *node = condition(&tok, tok);
  *rest = tok;
  return node;
}

static Node *select_stmt(Token **rest, Token *tok) {
  Node *node = new_node(ND_SELECT, tok);

  if (!consume(&tok, tok, "select")) error_tok(tok, "expected 'select'");
  node->select_list = select_list(&tok, tok);

  if (!consume(&tok, tok, "from")) error_tok(tok, "expected 'from'");
  node->table_name = table_name(&tok, tok);

  if (consume(&tok, tok, "where")) {
    node->where_clause = where_clause(&tok, tok);
  }

  *rest = tok;
  return node;
}

static Node *stmt(Token **rest, Token *tok) {
  if (tok->kind != TK_KEYWORD) error_tok(tok, "expected a keyword");

  Node *node;
  if (equal(tok, "select")) {
    node = select_stmt(&tok, tok);
  } else if (equal(tok, "insert")) {
    // node = insert_stmt(&tok, tok);
  }

  *rest = skip(tok, ";");
  return node;
}

Node *parse(Token *tok) {
  Node *node = stmt(&tok, tok);

  if (tok->kind != TK_EOF) error_tok(tok, "extra token");
  return node;
}