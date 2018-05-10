/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "idl/idl_parser.yy"
 

#define YYDEBUG 1			// debug 

//warning C4065: switch statement contains 'default' but no 'case' labels
#pragma warning(disable:4065)
//warning C4702: non-reachable code
#pragma warning(disable:4702)
// C4244: '인수': 'int64_t'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.
#pragma warning(disable:4244)

#include "idl_main.h"
#include <util/logger.hpp>


/* Line 371 of yacc.c  */
#line 84 "idl\\\\idl_parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "idl_parser.hpp".  */
#ifndef YY_YY_IDL_IDL_PARSER_HPP_INCLUDED
# define YY_YY_IDL_IDL_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 26 "idl/idl_parser.yy"

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


/* Line 387 of yacc.c  */
#line 194 "idl\\\\idl_parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_IDL_IDL_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 222 "idl\\\\idl_parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   84

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  94

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    24,     2,     2,     2,     2,     2,
       2,     2,     2,    31,    33,    32,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    13,    15,    21,
      25,    26,    31,    35,    36,    38,    40,    42,    49,    52,
      53,    56,    60,    62,    69,    71,    74,    75,    82,    85,
      86,    91,    98,   102,   109,   112,   114,   115,   118,   122,
     123,   125,   127,   129,   131,   133,   135,   137,   139,   142,
     143,   147,   151,   153,   155,   158,   161,   163,   165,   167,
     168,   170
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    -1,    37,    38,    -1,    -1,    39,
      -1,    41,    -1,    43,    -1,    21,    24,    40,     3,    24,
      -1,    40,     3,    25,    -1,    -1,    16,    42,     3,    62,
      -1,    42,     3,    15,    -1,    -1,    44,    -1,    48,    -1,
      51,    -1,    18,     3,    26,    45,    27,    62,    -1,    45,
      46,    -1,    -1,    47,    61,    -1,     3,    28,    59,    -1,
       3,    -1,    49,     3,    26,    50,    27,    62,    -1,    17,
      -1,    50,    53,    -1,    -1,    20,     3,    26,    52,    27,
      62,    -1,    52,    53,    -1,    -1,    57,     3,    58,    61,
      -1,    57,     3,    29,    59,    30,    61,    -1,    55,     3,
      61,    -1,    55,     3,    29,    59,    30,    61,    -1,    22,
      54,    -1,    23,    -1,    -1,    56,     3,    -1,    56,     3,
      15,    -1,    -1,     8,    -1,     7,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    28,
      59,    -1,    -1,    59,    31,    60,    -1,    59,    32,    60,
      -1,    60,    -1,    55,    -1,    31,     5,    -1,    32,     5,
      -1,     5,    -1,    33,    -1,    34,    -1,    -1,    34,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   124,   129,   134,   139,   144,   150,   159,
     165,   170,   181,   187,   192,   198,   204,   212,   229,   237,
     244,   252,   261,   270,   287,   294,   302,   311,   328,   336,
     343,   354,   365,   374,   385,   392,   402,   407,   416,   422,
     428,   434,   440,   446,   452,   458,   464,   470,   478,   486,
     493,   500,   507,   513,   522,   531,   540,   551,   554,   558,
     562,   565
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tok_identifier", "tok_literal",
  "tok_int_constant", "tok_dub_constant", "tok_bool", "tok_string",
  "tok_i8", "tok_i16", "tok_i32", "tok_i64", "tok_float", "tok_double",
  "tok_namespace_separator", "tok_namespace", "tok_struct", "tok_enum",
  "tok_const", "tok_message", "tok_include", "tok_cplus", "tok_macro_line",
  "'\"'", "'/'", "'{'", "'}'", "'='", "'['", "']'", "'+'", "'-'", "','",
  "';'", "$accept", "Program", "DefinitionList", "Definition", "Include",
  "IncludePath", "Namespace", "NamespaceTail", "TypeDefinition", "Enum",
  "EnumDefList", "EnumDef", "EnumValue", "Struct", "StructHead",
  "StructFieldList", "Message", "MessageFieldList", "Field",
  "CaptureVerbatimBlock", "FullType", "NameAccessor", "SimpleType",
  "FieldValue", "SimpleExpression", "InnerExpression",
  "CommaOrSemicolonOptional", "SemicolonOptional", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    34,    47,   123,   125,    61,    91,
      93,    43,    45,    44,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    39,    40,
      40,    41,    42,    42,    43,    43,    43,    44,    45,    45,
      46,    47,    47,    48,    49,    50,    50,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    54,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    59,    59,    60,    60,    60,    60,    61,    61,    61,
      62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     5,     3,
       0,     4,     3,     0,     1,     1,     1,     6,     2,     0,
       2,     3,     1,     6,     1,     2,     0,     6,     2,     0,
       4,     6,     3,     6,     2,     1,     0,     2,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       3,     3,     1,     1,     2,     2,     1,     1,     1,     0,
       1,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    13,    24,     0,     0,     0,     3,
       5,     6,     7,    14,    15,     0,    16,     0,     0,     0,
      10,     0,    61,    19,    29,     0,    26,    12,    60,    11,
       0,    39,     0,    39,    22,    61,    18,    59,    41,    40,
      42,    43,    44,    45,    46,    47,    36,    35,    61,    28,
       0,     0,     0,     8,     9,    61,    25,    39,    17,    57,
      58,    20,    34,    27,    59,    37,    49,    23,    56,     0,
       0,    53,    21,    52,    39,    32,    38,    39,    39,    59,
      54,    55,    39,    39,     0,    48,     0,    30,    50,    51,
      59,    59,    33,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     9,    10,    25,    11,    17,    12,    13,
      30,    36,    37,    14,    15,    33,    16,    31,    49,    62,
      71,    51,    52,    79,    72,    73,    61,    29
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int8 yypact[] =
{
     -65,    14,    36,   -65,   -65,   -65,    21,    52,    44,   -65,
     -65,   -65,   -65,   -65,   -65,    66,   -65,    67,    45,    46,
     -65,    47,     5,   -65,   -65,    71,   -65,   -65,   -65,   -65,
      -2,    -4,    38,    23,    48,    41,   -65,   -12,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,    41,   -65,
      74,    75,    76,   -65,   -65,    41,   -65,    -3,   -65,   -65,
     -65,   -65,   -65,   -65,   -17,    65,    13,   -65,   -65,    77,
      78,   -65,    33,   -65,    -3,   -65,   -65,    -3,    -3,   -12,
     -65,   -65,    -3,    -3,    17,    33,    29,   -65,   -65,   -65,
     -12,   -12,   -65,   -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,    51,   -65,
     -20,   -65,   -65,   -65,   -34,   -16,   -64,     3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      75,    34,    68,    38,    39,    40,    41,    42,    43,    44,
      45,    50,    74,    50,     3,    87,    59,    60,    46,    47,
      27,    59,    60,    48,    18,    35,    92,    93,    69,    70,
      38,    39,    40,    41,    42,    43,    44,    45,    58,    28,
      84,    77,    78,    85,    86,    46,    47,    90,    82,    83,
      55,    63,     4,     5,     6,    19,     7,     8,    67,    91,
      82,    83,    53,    54,    82,    83,    88,    89,    20,    21,
      22,    23,    24,    26,    32,    28,    57,    64,    65,    66,
      76,     0,    80,    81,    56
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-65)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      64,     3,     5,     7,     8,     9,    10,    11,    12,    13,
      14,    31,    29,    33,     0,    79,    33,    34,    22,    23,
      15,    33,    34,    27,     3,    27,    90,    91,    31,    32,
       7,     8,     9,    10,    11,    12,    13,    14,    35,    34,
      74,    28,    29,    77,    78,    22,    23,    30,    31,    32,
      27,    48,    16,    17,    18,     3,    20,    21,    55,    30,
      31,    32,    24,    25,    31,    32,    82,    83,    24,     3,
       3,    26,    26,    26,     3,    34,    28,     3,     3,     3,
      15,    -1,     5,     5,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,     0,    16,    17,    18,    20,    21,    38,
      39,    41,    43,    44,    48,    49,    51,    42,     3,     3,
      24,     3,     3,    26,    26,    40,    26,    15,    34,    62,
      45,    52,     3,    50,     3,    27,    46,    47,     7,     8,
       9,    10,    11,    12,    13,    14,    22,    23,    27,    53,
      55,    56,    57,    24,    25,    27,    53,    28,    62,    33,
      34,    61,    54,    62,     3,     3,     3,    62,     5,    31,
      32,    55,    59,    60,    29,    61,    15,    28,    29,    58,
       5,     5,    31,    32,    59,    59,    59,    61,    60,    60,
      30,    30,    61,    61
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 118 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Program => DefinitionList");
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 125 "idl/idl_parser.yy"
    {
		b2c::log()->debug("DefinitionList => DefinitionList Definition");
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 129 "idl/idl_parser.yy"
    {
		b2c::log()->debug("DefinitionList => ");
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 135 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Include");
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 140 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Namespace");
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 145 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Definition => TypeDefinition");
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 151 "idl/idl_parser.yy"
    {
		(yyval.tinclude) = (yyvsp[(3) - (5)].tinclude); 
		(yyval.tinclude)->add_path((yyvsp[(4) - (5)].id));

		g_program->add_node((yyval.tinclude));
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 160 "idl/idl_parser.yy"
    {
		(yyval.tinclude) = (yyvsp[(1) - (3)].tinclude); 
		(yyval.tinclude)->add_path((yyvsp[(2) - (3)].id));
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 165 "idl/idl_parser.yy"
    {
		(yyval.tinclude) = new idl_node_include();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 171 "idl/idl_parser.yy"
    {
		b2c::log()->debug("tok_namespace NamespaceTail tok_identifier SemicolonOptional");

		(yyval.tnamespace) = (yyvsp[(2) - (4)].tnamespace);	
		(yyval.tnamespace)->add_namespace((yyvsp[(3) - (4)].id));

		g_program->add_node((yyval.tnamespace));
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 182 "idl/idl_parser.yy"
    {
		(yyval.tnamespace) = (yyvsp[(1) - (3)].tnamespace); 
		(yyval.tnamespace)->add_namespace((yyvsp[(2) - (3)].id));
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 187 "idl/idl_parser.yy"
    {
		(yyval.tnamespace) = new idl_node_namespace();
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 193 "idl/idl_parser.yy"
    {
		b2c::log()->debug("TypeDefinition => Enum");

		g_program->add_node((yyvsp[(1) - (1)].tenum));
    }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 199 "idl/idl_parser.yy"
    {
		b2c::log()->debug("TypeDefinition => Struct");

		g_program->add_node((yyvsp[(1) - (1)].tstruct));
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 205 "idl/idl_parser.yy"
    {
		b2c::log()->debug("TypeDefinition => Message");

		g_program->add_node((yyvsp[(1) - (1)].tmessage));
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 213 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Enum => tok_enum tok_identifier '{' EnumDefList '}' SemicolonOptional");

		(yyval.tenum) = (yyvsp[(4) - (6)].tenum); 
		(yyval.tenum)->set_name((yyvsp[(2) - (6)].id));

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Enum, 
				g_program->get_fullname((yyval.tenum)->get_name()), 
				(yyval.tenum)->get_name()
			} 
		);
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 230 "idl/idl_parser.yy"
    {
		b2c::log()->debug("EnumDefList => EnumDefList EnumDef");

		(yyval.tenum) = (yyvsp[(1) - (2)].tenum);
		(yyval.tenum)->add_value((yyvsp[(2) - (2)].tenumv));
    }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 237 "idl/idl_parser.yy"
    {
		b2c::log()->debug("EnumDefList => ");

		(yyval.tenum) = new idl_node_enum();
    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 245 "idl/idl_parser.yy"
    {
		b2c::log()->debug("EnumDef => EnumValue CommaOrSemicolonOptional");

		(yyval.tenumv) = (yyvsp[(1) - (2)].tenumv);
    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 253 "idl/idl_parser.yy"
    {
		b2c::log()->debug("EnumValue => tok_identifier '=' SimpleExpression");

		(yyval.tenumv) = new idl_enum_value();
		(yyval.tenumv)->set_name((yyvsp[(1) - (3)].id));
		(yyval.tenumv)->set_default_expression((yyvsp[(3) - (3)].texpr));
    }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 262 "idl/idl_parser.yy"
    {
		b2c::log()->debug("EnumValue => tok_identifier");

		(yyval.tenumv) = new idl_enum_value();
		(yyval.tenumv)->set_name((yyvsp[(1) - (1)].id));
    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 271 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Struct => StructHead tok_identifier '{' StructFieldList '}' SemicolonOptional"); 

		(yyval.tstruct) = (yyvsp[(4) - (6)].tstruct);
		(yyval.tstruct)->set_name((yyvsp[(2) - (6)].id));

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Struct, 
				g_program->get_fullname((yyval.tstruct)->get_name()), 
				(yyval.tstruct)->get_name()
			} 
		);
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 288 "idl/idl_parser.yy"
    {
		b2c::log()->debug("StructHead => tok_struct");
    }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 295 "idl/idl_parser.yy"
    {
		b2c::log()->debug("StructFieldList => StructFieldList Field");

		(yyvsp[(1) - (2)].tstruct)->add_field((yyvsp[(2) - (2)].tfield));
		(yyval.tstruct) = (yyvsp[(1) - (2)].tstruct);
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 302 "idl/idl_parser.yy"
    {
		b2c::log()->debug("FieldList => ");

		// epsilon 매칭이 가장 먼저 실행된다. 왜?  

		(yyval.tstruct) = new idl_node_struct();
    }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 312 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Message => tok_message tok_identifier '{' MessageBody '}' SemicolonOptional"); 

		(yyval.tmessage) = (yyvsp[(4) - (6)].tmessage);
		(yyval.tmessage)->set_name((yyvsp[(2) - (6)].id));

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Message, 
				g_program->get_fullname((yyval.tmessage)->get_name()), 
				(yyval.tmessage)->get_name()
			} 
		);
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 329 "idl/idl_parser.yy"
    {
		b2c::log()->debug("MessageFieldList => MessageFieldList Field");

		(yyvsp[(1) - (2)].tmessage)->add_field((yyvsp[(2) - (2)].tfield));
		(yyval.tmessage) = (yyvsp[(1) - (2)].tmessage);
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 336 "idl/idl_parser.yy"
    {
		b2c::log()->debug("MessageFieldList => ");

		(yyval.tmessage) = new idl_node_message();
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 344 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Field => SimpleType tok_identifier FieldValue CommaOrSemicolonOptional");

		// create a field 
		(yyval.tfield) = new idl_field();
		(yyval.tfield)->set_type((yyvsp[(1) - (4)].tsimple));
		(yyval.tfield)->set_variable_name((yyvsp[(2) - (4)].id));
		(yyval.tfield)->set_simple_type();
		(yyval.tfield)->set_field_value((yyvsp[(3) - (4)].tfieldv));
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 355 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Field => SimpleType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional");

		(yyval.tfield) = new idl_field();
		(yyval.tfield)->set_type((yyvsp[(1) - (6)].tsimple));
		(yyval.tfield)->set_variable_name((yyvsp[(2) - (6)].id));
		(yyval.tfield)->set_simple_type();
		(yyval.tfield)->set_array_type();
		(yyval.tfield)->set_array_expression((yyvsp[(4) - (6)].texpr));
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 366 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Field => FullType tok_identifier CommaOrSemicolonOptional");

		(yyval.tfield) = new idl_field();
		(yyval.tfield)->set_type((yyvsp[(1) - (3)].tfull));
		(yyval.tfield)->set_variable_name((yyvsp[(2) - (3)].id));
		(yyval.tfield)->set_full_type();
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 375 "idl/idl_parser.yy"
    {
		b2c::log()->debug("Field => FullType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional");

		(yyval.tfield) = new idl_field();
		(yyval.tfield)->set_type((yyvsp[(1) - (6)].tfull));
		(yyval.tfield)->set_variable_name((yyvsp[(2) - (6)].id));
		(yyval.tfield)->set_full_type();
		(yyval.tfield)->set_array_type();
		(yyval.tfield)->set_array_expression((yyvsp[(4) - (6)].texpr));
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 386 "idl/idl_parser.yy"
    {
		(yyval.tfield) = new idl_field();

		(yyval.tfield)->set_verbatim((yyvsp[(2) - (2)].dtext));
		g_program->clear_verbatim_block();
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 393 "idl/idl_parser.yy"
    {
		b2c::log()->debug("tok_macro_line {}", (yyvsp[(1) - (1)].vline));

		(yyval.tfield) = new idl_field(); 

		(yyval.tfield)->set_macro_line((yyvsp[(1) - (1)].vline));
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 402 "idl/idl_parser.yy"
    {
		(yyval.dtext) = g_program->get_verbatim_block().c_str();
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 408 "idl/idl_parser.yy"
    {
		b2c::log()->debug("FullType => tok_identifier tok_namespace_separator tok_identifier");

		(yyval.tfull) = (yyvsp[(1) - (2)].tfull); 
		(yyval.tfull)->set_id((yyvsp[(2) - (2)].id));
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 417 "idl/idl_parser.yy"
    {
		(yyval.tfull) = (yyvsp[(1) - (3)].tfull);
		(yyval.tfull)->add_namespace((yyvsp[(2) - (3)].id)); 
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 422 "idl/idl_parser.yy"
    {
		(yyval.tfull) = new idl_type_full(); 
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 429 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_string");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_STRING); 
    }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 435 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_bool");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_BOOL); 
    }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 441 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_i8");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_I8); 
    }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 447 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_i16");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_I16); 
    }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 453 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_i32");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_I32); 
    }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 459 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_i64");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_I64); 
    }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 465 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_float");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_FLOAT); 
    }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 471 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleType => tok_double");

		(yyval.tsimple) = new idl_type_simple(idl_type_simple::types::TYPE_DOUBLE); 
    }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 479 "idl/idl_parser.yy"
    {
		b2c::log()->debug("FieldValue => '=' SimpleExpression");

		(yyval.tfieldv) = new idl_field_value(); 
		(yyval.tfieldv)->set_default_expression((yyvsp[(2) - (2)].texpr));
    }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 486 "idl/idl_parser.yy"
    {
		b2c::log()->debug("FieldValue =>"); 

		(yyval.tfieldv) = new idl_field_value();
    }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 494 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleExpression => SimpleExpression '+' InnerExpression");

		(yyval.texpr) = (yyvsp[(1) - (3)].texpr); 
		(yyval.texpr)->add_plus((yyvsp[(3) - (3)].texpr));
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 501 "idl/idl_parser.yy"
    {
		b2c::log()->debug("SimpleExpression => SimpleExpression '-' InnerExpression");

		(yyval.texpr) = (yyvsp[(1) - (3)].texpr); 
		(yyval.texpr)->add_minus((yyvsp[(3) - (3)].texpr));
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 508 "idl/idl_parser.yy"
    {
		(yyval.texpr) = (yyvsp[(1) - (1)].texpr);
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 514 "idl/idl_parser.yy"
    {
		b2c::log()->debug("InnerExpression => FullType '.'  tok_identifier");

		(yyval.texpr) = new idl_expression(); 
		auto fv = new idl_expression_value(); 
		fv->set_full_id((yyvsp[(1) - (1)].tfull));
		(yyval.texpr)->set_value(fv);
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 523 "idl/idl_parser.yy"
    {
		b2c::log()->debug("'+' => tok_int_constant");

		(yyval.texpr) = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value((yyvsp[(2) - (2)].iconst));
		(yyval.texpr)->set_value(cv);
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 532 "idl/idl_parser.yy"
    {
		b2c::log()->debug("'-' => tok_int_constant");

		(yyval.texpr) = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value(0-(yyvsp[(2) - (2)].iconst));
		(yyval.texpr)->set_value(cv);
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 541 "idl/idl_parser.yy"
    {
		b2c::log()->debug("InnerExpression => tok_int_constant");

		(yyval.texpr) = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value((yyvsp[(1) - (1)].iconst));
		(yyval.texpr)->set_value(cv);
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 552 "idl/idl_parser.yy"
    {
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 555 "idl/idl_parser.yy"
    {
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 558 "idl/idl_parser.yy"
    {
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 563 "idl/idl_parser.yy"
    {}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 565 "idl/idl_parser.yy"
    {}
    break;


/* Line 1792 of yacc.c  */
#line 2133 "idl\\\\idl_parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 567 "idl/idl_parser.yy"

