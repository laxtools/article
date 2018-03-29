  // Bison file

%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern void yyerror(char*);
%}
  // tokens we want to return

%union {
  int int_token;
}

  // list the different tokens of each type
%token <int_token> QUIT HELLO SEMICOLON

  // root node
%start root_node

%%

root_node: hello_node root_node | quit_node;

hello_node: HELLO SEMICOLON
    {printf("parsed a hello node!\nHello, user!\n");}

quit_node: QUIT SEMICOLON
    {printf("parsed a quit node!\nGoodbye, user!\n"); exit(0);}
