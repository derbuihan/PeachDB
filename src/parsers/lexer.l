%{
    #include <stdlib.h>
    #include "node.h"
    #include "parser.tab.h"
%}

%%
"+"                          { return PLUS; }
"-"                          { return MINUS; }
";"                          { return SEMICOLON; }
[0-9]+                       {
                                yylval = new_num_node(atoi(yytext));
                                return NUMBER;
                             }
[ \t\n]                      { /* ignore whitespace */ }
.                            { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}