%{
  #include <stdio.h>
  #include "example01.tab.h"  // bison output
  void yyerror(char*);
  int yyparser(void);
%}

  // on reading this do this
%%
";"             return SEMICOLON;
"hello-world"   {printf("got HELLO token\n"); return HELLO; }
"quit"          {printf("got QUIT token\n"); return QUIT; }
[ \t\n]+        ;   // do nothing on whitespace
%%

void yyerror(char* str) {printf("ERROR: Could not parse!\n");}
int yywrap(void) {}
int main(void) {
  yyparse();
}
