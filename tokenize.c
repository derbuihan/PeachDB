#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "peachdb.h"

static bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

static bool is_ident(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int read_punct(char *str) {
  static char *kw[] = {};
  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
    int len = strlen(kw[i]);
    if (strncmp(str, kw[i], len) == 0) {
      return len;
    }
  }

  return ispunct(*str) ? 1 : 0;
}

static int read_digit(char *str) {
  char *end;
  strtoul(str, &end, 10);
  int len = end - str;
  return len;
}

static Token *new_token(TokenKind kind, char *start, char *end) {
  Token *token = malloc(sizeof(Token));
  token->kind = kind;
  token->loc = start;
  token->len = end - start;
  token->next = NULL;
  return token;
}

static bool startswith(char *str, char *prefix) {
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

static bool is_keyword(char *str) {
  static char *kw[] = {"select", "from", "where", "and"};
  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
    if (startswith(str, kw[i])) return true;
  }
  return false;
}

static void convert_keywords(Token *token) {
  for (Token *tok = token; tok->kind != TK_EOF; tok = tok->next) {
    if (tok->kind == TK_IDENT && is_keyword(tok->loc)) {
      tok->kind = TK_KEYWORD;
    }
  }
}

Token *tokenize(char *str) {
  Token head = {};
  Token *cur = &head;

  while (*str != '\0') {
    if (is_whitespace(*str)) {
      str++;
      continue;
    }

    if (*str == '\'') {
      char *start = ++str;
      while (*str != '\'') str++;
      Token *token = new_token(TK_STR, start, str++);
      char *str = malloc(token->len);
      strncpy(str, token->loc, token->len);
      token->str = str;
      cur = cur->next = token;
      continue;
    }

    int punct_len = read_punct(str);
    if (punct_len > 0) {
      cur = cur->next = new_token(TK_PUNCT, str, str + punct_len);
      str += punct_len;
      continue;
    }

    int num_len = read_digit(str);
    if (num_len > 0) {
      Token *token = new_token(TK_NUM, str, str + num_len);
      token->val = strtoul(str, NULL, 10);
      cur = cur->next = token;
      str += num_len;
      continue;
    }

    if (is_ident(*str)) {
      char *start = str;
      while (is_ident(*str)) str++;
      cur = cur->next = new_token(TK_IDENT, start, str);
      continue;
    }
  }
  cur->next = new_token(TK_EOF, str, str);

  convert_keywords(head.next);
  return head.next;
}