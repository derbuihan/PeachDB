
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Bison
find_package(BISON REQUIRED)
set(PARSER_OUT ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)
set(PARSER_HEADER ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
BISON_TARGET(Parser parser.y ${PARSER_OUT} DEFINES_FILE ${PARSER_HEADER})

# Flex
find_package(FLEX REQUIRED)
set(LEXER_OUT ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.c)
set(LEXER_HEADER ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.h)
FLEX_TARGET(Tokenizer lexer.l ${LEXER_OUT} DEFINES_FILE ${LEXER_HEADER})

# copy node.h/node.c to build directory
set(NODE_HEADER ${CMAKE_CURRENT_BINARY_DIR}/node.h)
configure_file(node.h ${NODE_HEADER} COPYONLY)
add_library(node OBJECT node.c)

# create library
add_flex_bison_dependency(Tokenizer Parser)
add_library(parser ${LEXER_OUT} ${PARSER_OUT} node)
