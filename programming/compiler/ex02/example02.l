%{
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
#include "example02.tab.hpp"
void yyerror(char*);
int yyparser(void);
%}

%option yylineno

%%
[ \t\n]+                      ; // do nothing
"print"                       return PRINT;
"quit"						  return QUIT; 
[a-zA-Z][a-zA-Z0-9]*          {yylval.str_val = new string(yytext); return VARIABLE; }
[0-9][0-9]*(.[0-9]+)?         {yylval.double_val = atof(yytext); return NUMBER; }
"="                           return EQUALS;
"+"                           return PLUS;
"-"                           return MINUS;
"*"                           return ASTERISK;
"/"                           return FSLASH;
"("                           return LPAREN;
")"                           return RPAREN;
";"                           return SEMICOLON;
%%

void yyerror(char* str) { printf("Parse Error at %d: \n %s with %s\n", yylineno, str, yytext); }

int yywrap(void) {return 0;}

int main(int num_args, char** args)
{
  if ( num_args != 2 ) { printf("usage: ./parser1 filename\n"); exit(-1); }

  FILE* file = NULL; 

  fopen_s(&file, args[1], "r");

  if ( file == NULL ) { printf("Couldn't open %s\n", args[1]); exit(-2); }

  yyin = file;
  yyparse();
  fclose(file);
}
