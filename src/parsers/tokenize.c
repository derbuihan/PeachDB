#include "peachdb.h"

static bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

static bool is_ident(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool startswith(char *p, char *prefix) {
  return strncmp(p, prefix, strlen(prefix)) == 0;
}

static Token *new_token(TokenKind kind, char *start, char *end) {
  Token *token = malloc(sizeof(Token));
  token->kind = kind;
  token->loc = start;
  token->len = end - start;
  token->next = NULL;
  return token;
}

static int read_punct(char *p) {
  static char *kw[] = {"!="};
  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
    if (startswith(p, kw[i])) {
      return strlen(kw[i]);
    }
  }
  return ispunct(*p) ? 1 : 0;
}

static Token *read_digit(char *p) {
  char *end;
  int val = strtoul(p, &end, 10);

  Token *token = new_token(TK_NUM, p, end);
  token->val = val;
  return token;
}

static Token *read_string_literal(char *p) {
  char *start = ++p;
  while (*p != '\'') p++;
  int len = p - start;

  Token *token = new_token(TK_STR, start, p);
  token->str = strndup(start, len);
  return token;
}

static Token *read_ident(char *p) {
  char *start = p;
  while (is_ident(*p)) p++;
  return new_token(TK_IDENT, start, p);
}

static bool is_keyword(char *p) {
  static char *kw[] = {"select", "delete", "from", "where", "and"};
  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
    if (startswith(p, kw[i])) return true;
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

Token *tokenize(char *p) {
  Token head = {};
  Token *cur = &head;

  while (*p != '\0') {
    if (is_whitespace(*p)) {
      p++;
      continue;
    }

    if (*p == '\'') {
      cur = cur->next = read_string_literal(p);
      p += cur->len + 2;
      continue;
    }

    int punct_len = read_punct(p);
    if (punct_len > 0) {
      cur = cur->next = new_token(TK_PUNCT, p, p + punct_len);
      p += punct_len;
      continue;
    }

    if (isdigit(*p)) {
      cur = cur->next = read_digit(p);
      p += cur->len;
      continue;
    }

    if (is_ident(*p)) {
      cur = cur->next = read_ident(p);
      p += cur->len;
      continue;
    }
  }
  cur->next = new_token(TK_EOF, p, p);

  convert_keywords(head.next);
  return head.next;
}