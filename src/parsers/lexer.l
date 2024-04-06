
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

%{
    #include <stdlib.h>
    #include "node.h"
    #include "parser.tab.h"
%}

%%
"select"                    { return SELECT; }
"from"                      { return FROM; }
"where"                     { return WHERE; }
"and"                       { return AND; }
"or"                        { return OR; }
"="                         { return EQ; }
"!="                        { return NE; }
"*"                         { return ASTERISK; }
","                         { return COMMA; }
";"                         { return SEMICOLON; }
"'[^']*'"                   {
                                yylval = new_str_node(strdup(yytext));
                                return STRING;
                            }
[0-9]+                      {
                                yylval = new_num_node(atoi(yytext));
                                return NUMBER;
                            }
[a-zA-Z_][a-zA-Z0-9_]*      {
                                yylval = new_id_node(strdup(yytext));
                                return ID;
                            }
[ \t\n]                      { /* ignore whitespace */ }
.                           { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
