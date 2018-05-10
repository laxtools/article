%{

#pragma warning(disable: 4005) // INT_*에 대한 중복 정의 
#include "idl_main.h"
#include "idl_parser.hpp"
#include <util/logger.hpp>

void integer_overflow(char* text) {
  yyerror("This integer is too big: \"%s\"\n", text);
  exit(1);
}

%}
/**
 * Provides the yylineno global, useful for debugging output
 */
%option lex-compat

/**
 * Our inputs are all single files, so no need for yywrap
 */
%option noyywrap

/**
 * We don't use it, and it fires up warnings at -Wall
 */
%option nounput

/**
 * Helper definitions, comments, constants, and whatnot
 */

intconstant   ([0-9]+)
hexconstant   ("0x"[0-9A-Fa-f]+)
dubconstant   ([0-9]*(\.[0-9]+)?([eE][+-]?[0-9]+)?)
identifier    ([a-zA-Z_](\.[a-zA-Z_0-9]|[a-zA-Z_0-9])*)
whitespace    ([ \t\r\n]*)
comment       ("//"[^\n]*)
symbol        ([/\":;\.\,\{\}\(\)\=<>\[\]])
multicm_begin ("/*")
verbatim_begin ("$")
macro_line ("#"[^\n]*)


%% 

{whitespace}        { /* do nothing */					}
{comment}			{ /* do nothing */					}

"::"				{ return tok_namespace_separator;	/* should come before symbol */ }
{symbol}            { return yytext[0];					}


"i8"                { return tok_i8;					}
"i16"               { return tok_i16;					}
"i32"               { return tok_i32;					}
"i64"               { return tok_i64;					}
"float"             { return tok_float;					}
"double"            { return tok_double;				}
"string"            { return tok_string;				}
"enum"              { return tok_enum;					}
"struct"            { return tok_struct;				}
"message"           { return tok_message;				}
[+]					{ return yytext[0];					}
[-]					{ return yytext[0];					}
"namespace"			{ return tok_namespace;				}
"include"			{ return tok_include;				}				


{multicm_begin}  { /* parsed, but thrown away */
  std::string parsed("/*");
  int state = 0;  // 0 = normal, 1 = "*" seen, "*/" seen
  while(state < 2)
  {
    int ch = yyinput();
    parsed.push_back(ch);
    switch (ch) {
      case EOF:
        yyerror("Unexpected end of file in multiline comment at %d\n", yylineno);
        exit(1);
      case '*':
        state = 1;
        break;
      case '/':
        state = (state == 1) ? 2 : 0;
        break;
      default:
        state = 0;
        break;
    }
  }

  r2c::log()->debug("multi_comm = {}", parsed);
}

"cplus"	{
  std::string parsed;
  int state = 0;  // 0 = normal, 1 = "{" seen, "}" end
  while(state < 2)
  {
    int ch = yyinput();
    switch (ch) {
      case EOF:
        yyerror("Unexpected end of file in verbatim block at %d\n", yylineno);
        exit(1);
      case '{':
		state = 1;
        break;
      case '}':
		state = 2;
        break;
      default:
		parsed.push_back(ch);
        break;
    }
  }

  g_program->set_verbatim_block(parsed);

  r2c::log()->debug("cplus verbatim = {}", parsed);

  return tok_cplus;									
}

{intconstant} {
  errno = 0;
  yylval.iconst = strtoll(yytext, NULL, 10);
  if (errno == ERANGE) {
    integer_overflow(yytext);
  }
  return tok_int_constant;
}

{hexconstant} {
  errno = 0;
  char sign = yytext[0];
  int shift = sign == '0' ? 2 : 3;
  yylval.iconst = strtoll(yytext+shift, NULL, 16);
  if (sign == '-') {
    yylval.iconst = -yylval.iconst;
  }
  if (errno == ERANGE) {
    integer_overflow(yytext);
  }
  return tok_int_constant;
}

{identifier} {
  yylval.id = _strdup(yytext);
  return tok_identifier;
}

{macro_line} {
  yylval.vline = _strdup(yytext);
  r2c::log()->debug("verbatim line {}", yylval.vline);
  return tok_macro_line;
}

{dubconstant} {
 /* Deliberately placed after identifier, since "e10" is NOT a double literal (THRIFT-3477) */
  yylval.dconst = atof(yytext);
  return tok_dub_constant;
}

. {
  r2c::log()->error("Unexpected token: {}", yytext);
}

%%