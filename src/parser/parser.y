%{
    #include <stdio.h>
    #include "node.h"
    extern void yyerror(Node **root, const char *s);
    extern int yylex();
%}

%param {Node **root}

%define api.value.type {Node *}

%token SELECT FROM WHERE SEMICOLON
%token ASTERISK COMMA
%token EQ NE AND OR
%token PLUS MINUS
%token STRING NUMBER ID

%%
stmt:
    select_stmt SEMICOLON { *root = $1; }

select_stmt:
    SELECT column_list FROM table_name { $$ = new_select_node($2, $4, NULL); }
    | SELECT column_list FROM table_name where_clause { $$ = new_select_node($2, $4, $5); }

column_list:
    column_name { $$ = new_column_list_node($1, NULL); }
    | column_name COMMA column_list { $$ = new_column_list_node($1, $3); }

column_name:
    ASTERISK { $$ = new_str_node("*"); }
    | ID { $$ = $1; }

table_name:
    ID { $$ = $1; }

where_clause:
    WHERE condition { $$ = $2; }

condition:
    comparison { $$ = $1; }
    | condition AND condition { $$ = new_op_node("AND", $1, $3); }
    | condition OR condition { $$ = new_op_node("OR", $1, $3); }

comparison:
    column_name EQ value { $$ = new_op_node("=", $1, $3); }
    | column_name NE value { $$ = new_op_node("!=", $1, $3); }

value:
    expr { $$ = $1; }
    | STRING { $$ = $1; }

expr:
    NUMBER { $$ = $1; }
    | expr PLUS expr { $$ = new_op_node("+", $1, $3); }
    | expr MINUS expr { $$ = new_op_node("+", $1, $3); }
%%

void yyerror(Node **root, const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}