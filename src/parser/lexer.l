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
"+"                         { return PLUS; }
"-"                         { return MINUS; }
[0-9]+                      {
                                yylval = new_num_node(atoi(yytext));
                                return NUMBER;
                            }
'[^\']*'                    {
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
[ \t\n]                     { /* ignore whitespace */ }
.                           { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
