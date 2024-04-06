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

/*
 * select id, name from users;
 * select id, name from users where id = 1 + 2 and name != 'foo';
 */

%{
    #include <stdio.h>
    #include "node.h"
    extern void yyerror(Node **root, const char *s);
    extern int yylex();
%}

%param {Node **root}

%define api.value.type {Node *}

%token PLUS MINUS SEMICOLON
%token SELECT FROM WHERE
%token AND OR EQ NE ASTERISK COMMA STRING NUMBER ID

%%
stmt: select_stmt SEMICOLON {
    *root = $1;
}
select_stmt: SELECT column_list FROM table_name {
    $$ = new_select_node($2, $4, NULL);
}
column_list: column_name { $$ = new_column_list_node($1, NULL); }
    | column_name COMMA column_list { $$ = new_column_list_node($1, $3); }
column_name: ID { $$ = $1; }
table_name: ID { $$ = $1; }

expr: NUMBER { $$ = $1; }
    | expr PLUS expr { $$ = new_op_node("+", $1, $3); }
    | expr MINUS expr { $$ = new_op_node("-", $1, $3); }
%%

void yyerror(Node **root, const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
