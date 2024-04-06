%{
    #include <stdio.h>
    #include "node.h"
    extern void yyerror(Node **root, const char *s);
    extern int yylex();
%}

%param {Node **root}

%define api.value.type {Node *}

%token NUMBER
%token PLUS MINUS SEMICOLON

%%
stmt: expr SEMICOLON { *root = $1; }
expr: NUMBER { $$ = $1; }
    | expr PLUS expr { $$ = new_op_node('+', $1, $3); }
    | expr MINUS expr { $$ = new_op_node('-', $1, $3); }
%%

void yyerror(Node **root, const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}