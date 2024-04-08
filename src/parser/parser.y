%{
    #include <stdio.h>
    #include "node.h"
    extern void yyerror(Node **root, const char *s);
    extern int yylex();
%}

%param {Node **root}

%define api.value.type {Node *}

%token SELECT FROM WHERE
%token INSERT INTO VALUES LPAREN RPAREN
%token ASTERISK COMMA
%token EQ NE AND OR
%token PLUS MINUS
%token STRING NUMBER ID
%token SEMICOLON

%%
stmt:
    select_stmt SEMICOLON { *root = $1; }
    | insert_stmt SEMICOLON { *root = $1; }

select_stmt:
    SELECT column_list FROM table_name { $$ = new_select_node($2, $4, NULL); }
    | SELECT column_list FROM table_name where_clause { $$ = new_select_node($2, $4, $5); }

insert_stmt:
    INSERT INTO table_name VALUES LPAREN value_list RPAREN { $$ = new_insert_node($3, NULL, $6); }
    | INSERT INTO table_name LPAREN column_list RPAREN VALUES LPAREN value_list RPAREN { $$ = new_insert_node($3, $5, $9); }

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

value_list:
    value { $$ = new_value_list_node($1, NULL); }
    | value COMMA value_list { $$ = new_value_list_node($1, $3); }

condition:
    comparison { $$ = $1; }
    | condition AND condition { $$ = new_op_node(ND_AND, $1, $3); }
    | condition OR condition { $$ = new_op_node(ND_OR, $1, $3); }

comparison:
    column_name EQ value { $$ = new_op_node(ND_EQ, $1, $3); }
    | column_name NE value { $$ = new_op_node(ND_NE, $1, $3); }

value:
    expr { $$ = $1; }
    | STRING { $$ = $1; }

expr:
    NUMBER { $$ = $1; }
    | expr PLUS expr { $$ = new_op_node(ND_ADD, $1, $3); }
    | expr MINUS expr { $$ = new_op_node(ND_SUB, $1, $3); }
%%

void yyerror(Node **root, const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
