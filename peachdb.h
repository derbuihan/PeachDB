

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
