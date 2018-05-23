%{
#pragma warning(disable: 4005)
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
using namespace std;
map<string, double> vars;
extern int yylex();
extern void yyerror(char* );
void DivByZeroError();
void UnknownVariableError(const string& s);
%}

%union {
  int   int_val;
  double double_val;
  string* str_val;
}

%token <int_val>      PLUS  MINUS ASTERISK FSLASH EQUALS PRINT  LPAREN RPAREN SEMICOLON QUIT
%token <str_val>      VARIABLE
%token <double_val>   NUMBER

%type <double_val>  expression;
%type <double_val>  inner1;
%type <double_val>  inner2;

%start parsetree

%%

parsetree:    lines;

lines:        lines line | line;

line:         PRINT expression SEMICOLON  { printf("%lf\n", $2); }
		  |	  QUIT SEMICOLON { printf("quit...\n"); exit(0); }
          |   VARIABLE EQUALS expression SEMICOLON { vars[*$1] = $3; delete $1; };

expression:   expression PLUS inner1      { $$ = $1 + $3; }
          |   expression MINUS inner1     { $$ = $1 - $3; }
          |   inner1                      
		  { 
			$$ = $1; 
		   };

inner1:       inner1  ASTERISK  inner2    { $$ = $1 * $3; }
          |   inner1  FSLASH    inner2
              { if ( $3 == 0 ) DivByZeroError(); else $$ = $1 / $3; }
          |   inner2                      { $$ = $1; };

inner2:       VARIABLE
              {
                if (!vars.count(*$1))
                {
                  UnknownVariableError(*$1);
                }
                else
                {
                  $$ = vars[*$1]; delete $1;
                }
              }
          |   NUMBER    { $$ = $1; }
          |   LPAREN expression RPAREN  { $$ = $2; };

%%

void DivByZeroError( void ) { printf (" Error : division by zero \n"); exit (0);}
void UnknownVariableError (const string& s) { printf (" Error : %s does not exist !\n", s. c_str ()); exit (0);}