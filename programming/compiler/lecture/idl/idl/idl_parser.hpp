/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_IDL_IDL_PARSER_HPP_INCLUDED
# define YY_YY_IDL_IDL_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tok_identifier = 258,
    tok_literal = 259,
    tok_int_constant = 260,
    tok_dub_constant = 261,
    tok_bool = 262,
    tok_string = 263,
    tok_i8 = 264,
    tok_i16 = 265,
    tok_i32 = 266,
    tok_i64 = 267,
    tok_float = 268,
    tok_double = 269,
    tok_namespace_separator = 270,
    tok_namespace = 271,
    tok_struct = 272,
    tok_enum = 273,
    tok_const = 274,
    tok_message = 275,
    tok_include = 276,
    tok_cplus = 277,
    tok_macro_line = 278
  };
#endif
/* Tokens.  */
#define tok_identifier 258
#define tok_literal 259
#define tok_int_constant 260
#define tok_dub_constant 261
#define tok_bool 262
#define tok_string 263
#define tok_i8 264
#define tok_i16 265
#define tok_i32 266
#define tok_i64 267
#define tok_float 268
#define tok_double 269
#define tok_namespace_separator 270
#define tok_namespace 271
#define tok_struct 272
#define tok_enum 273
#define tok_const 274
#define tok_message 275
#define tok_include 276
#define tok_cplus 277
#define tok_macro_line 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "idl/idl_parser.yy" /* yacc.c:1909  */

  char*						id;
  const char*				dtext;
  const char*				vline;
  int64_t					iconst;
  double					dconst;
  bool						tbool;
  idl_enum_value*			tenumv;
  idl_field*				tfield;
  idl_field_value*			tfieldv;
  idl_expression* 			texpr;
  idl_type_simple*			tsimple;
  idl_type_full*			tfull;
  idl_node_enum*			tenum;
  idl_node_struct*			tstruct;
  idl_node_message*			tmessage;
  idl_node_namespace*		tnamespace;
  idl_node_include*			tinclude;

#line 120 "idl\\\\idl_parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IDL_IDL_PARSER_HPP_INCLUDED  */
