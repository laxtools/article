%{ 

#define YYDEBUG 1			// debug 

//warning C4065: switch statement contains 'default' but no 'case' labels
#pragma warning(disable:4065)
//warning C4702: non-reachable code
#pragma warning(disable:4702)
// C4244: '인수': 'int64_t'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.
#pragma warning(disable:4244)

#include "idl_main.h"
#include <util/logger.hpp>

%}

/** 
 * make verbose error to debug
 */
%error-verbose

/**
 * This structure is used by the parser to hold the data types associated with
 * various parse nodes.
 */
%union {
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
}

/**
 * Strings identifier
 */
%token<id>     tok_identifier
%token<id>     tok_literal

/**
 * Constant values
 */
%token<iconst> tok_int_constant
%token<dconst> tok_dub_constant

/**
 * Base datatype keywords
 */
%token tok_bool
%token tok_string
%token tok_i8
%token tok_i16
%token tok_i32
%token tok_i64
%token tok_float
%token tok_double

/**
 * Syntatic symbols
 */
 %token tok_namespace_separator
 %token tok_namespace

/**
 * Language keywords
 */
%token tok_struct
%token tok_enum
%token tok_const
%token tok_message
%token tok_include
%token tok_cplus
%token<vline> tok_macro_line

/**
 * Grammar nodes
 */
%type<tenum>     	Enum
%type<tenum>     	EnumDefList
%type<tenumv>    	EnumDef
%type<tenumv>    	EnumValue

%type<tstruct>     	Struct
%type<tstruct>     	StructFieldList
%type<tmessage>		Message	
%type<tmessage>		MessageFieldList 
%type<tfield>   	Field 	
%type<tfieldv>   	FieldValue 	

%type<tsimple> 		SimpleType
%type<tfull> 		FullType
%type<tfull> 		NameAccessor
%type<texpr> 		SimpleExpression
%type<texpr> 		InnerExpression	
%type<tnamespace> 	Namespace
%type<tnamespace> 	NamespaceTail
%type<tinclude> 	Include
%type<tinclude> 	IncludePath

%type<dtext>		CaptureVerbatimBlock

%%

Program:
	DefinitionList 
	{
		b2c::log()->debug("Program => DefinitionList");
	}


DefinitionList:
  DefinitionList Definition
    {
		b2c::log()->debug("DefinitionList => DefinitionList Definition");
    }
|
    {
		b2c::log()->debug("DefinitionList => ");
    }

Definition: 
	Include
	{
		b2c::log()->debug("Include");
	}
|
	Namespace 
	{
		b2c::log()->debug("Namespace");
	}
|
	TypeDefinition 
    {
		b2c::log()->debug("Definition => TypeDefinition");
    }

Include: 
	tok_include '\"'  IncludePath tok_identifier '\"'
	{
		$$ = $3; 
		$$->add_path($4);

		g_program->add_node($$);
	}

IncludePath: 
	IncludePath tok_identifier '/' 
	{
		$$ = $1; 
		$$->add_path($2);
	}
|
	{
		$$ = new idl_node_include();
	}

Namespace: 
	tok_namespace NamespaceTail tok_identifier SemicolonOptional
	{
		b2c::log()->debug("tok_namespace NamespaceTail tok_identifier SemicolonOptional");

		$$ = $2;	
		$$->add_namespace($3);

		g_program->add_node($$);
	}

NamespaceTail: 
	NamespaceTail tok_identifier tok_namespace_separator
	{
		$$ = $1; 
		$$->add_namespace($2);
	}
| 
	{
		$$ = new idl_node_namespace();
	}
	
TypeDefinition:
	Enum
    {
		b2c::log()->debug("TypeDefinition => Enum");

		g_program->add_node($1);
    }
|	Struct 
	{
		b2c::log()->debug("TypeDefinition => Struct");

		g_program->add_node($1);
	}
|	Message
	{
		b2c::log()->debug("TypeDefinition => Message");

		g_program->add_node($1);
	}

Enum:
  tok_enum tok_identifier '{' EnumDefList '}' SemicolonOptional
    {
		b2c::log()->debug("Enum => tok_enum tok_identifier '{' EnumDefList '}' SemicolonOptional");

		$$ = $4; 
		$$->set_name($2);

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Enum, 
				g_program->get_fullname($$->get_name()), 
				$$->get_name()
			} 
		);
	}

EnumDefList:
  EnumDefList EnumDef
    {
		b2c::log()->debug("EnumDefList => EnumDefList EnumDef");

		$$ = $1;
		$$->add_value($2);
    }
|
    {
		b2c::log()->debug("EnumDefList => ");

		$$ = new idl_node_enum();
    }

EnumDef:
  EnumValue CommaOrSemicolonOptional
    {
		b2c::log()->debug("EnumDef => EnumValue CommaOrSemicolonOptional");

		$$ = $1;
    }

EnumValue:
  tok_identifier '=' SimpleExpression
    {
		b2c::log()->debug("EnumValue => tok_identifier '=' SimpleExpression");

		$$ = new idl_enum_value();
		$$->set_name($1);
		$$->set_default_expression($3);
    }
 |
  tok_identifier
    {
		b2c::log()->debug("EnumValue => tok_identifier");

		$$ = new idl_enum_value();
		$$->set_name($1);
    }

Struct:
  StructHead tok_identifier '{' StructFieldList '}' SemicolonOptional 
    {
		b2c::log()->debug("Struct => StructHead tok_identifier '{' StructFieldList '}' SemicolonOptional"); 

		$$ = $4;
		$$->set_name($2);

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Struct, 
				g_program->get_fullname($$->get_name()), 
				$$->get_name()
			} 
		);
    }

StructHead:
  tok_struct
    {
		b2c::log()->debug("StructHead => tok_struct");
    }


StructFieldList:
  StructFieldList Field
    {
		b2c::log()->debug("StructFieldList => StructFieldList Field");

		$1->add_field($2);
		$$ = $1;
    }
|
    {
		b2c::log()->debug("FieldList => ");

		// epsilon 매칭이 가장 먼저 실행된다. 왜?  

		$$ = new idl_node_struct();
    }

Message:
  tok_message tok_identifier '{' MessageFieldList '}' SemicolonOptional 
    {
		b2c::log()->debug("Message => tok_message tok_identifier '{' MessageBody '}' SemicolonOptional"); 

		$$ = $4;
		$$->set_name($2);

		g_symbols->add( 
			idl_symbol{
				idl_symbol::Message, 
				g_program->get_fullname($$->get_name()), 
				$$->get_name()
			} 
		);
	}

MessageFieldList:
	MessageFieldList Field
    {
		b2c::log()->debug("MessageFieldList => MessageFieldList Field");

		$1->add_field($2);
		$$ = $1;
    }
|
    {
		b2c::log()->debug("MessageFieldList => ");

		$$ = new idl_node_message();
    }

Field:
  SimpleType tok_identifier FieldValue CommaOrSemicolonOptional
    {
		b2c::log()->debug("Field => SimpleType tok_identifier FieldValue CommaOrSemicolonOptional");

		// create a field 
		$$ = new idl_field();
		$$->set_type($1);
		$$->set_variable_name($2);
		$$->set_simple_type();
		$$->set_field_value($3);
    }
| SimpleType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional
	{
		b2c::log()->debug("Field => SimpleType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional");

		$$ = new idl_field();
		$$->set_type($1);
		$$->set_variable_name($2);
		$$->set_simple_type();
		$$->set_array_type();
		$$->set_array_expression($4);
	}
| FullType tok_identifier CommaOrSemicolonOptional
    {
		b2c::log()->debug("Field => FullType tok_identifier CommaOrSemicolonOptional");

		$$ = new idl_field();
		$$->set_type($1);
		$$->set_variable_name($2);
		$$->set_full_type();
    }
| FullType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional
	{
		b2c::log()->debug("Field => FullType tok_identifier '[' SimpleExpression ']' CommaOrSemicolonOptional");

		$$ = new idl_field();
		$$->set_type($1);
		$$->set_variable_name($2);
		$$->set_full_type();
		$$->set_array_type();
		$$->set_array_expression($4);
	}
| tok_cplus CaptureVerbatimBlock 
	{
		$$ = new idl_field();

		$$->set_verbatim($2);
		g_program->clear_verbatim_block();
	}
| tok_macro_line 
	{
		b2c::log()->debug("tok_macro_line {}", $1);

		$$ = new idl_field(); 

		$$->set_macro_line($1);
	}

CaptureVerbatimBlock: 
	{
		$$ = g_program->get_verbatim_block().c_str();
	}

FullType: 
  NameAccessor tok_identifier 
	{
		b2c::log()->debug("FullType => tok_identifier tok_namespace_separator tok_identifier");

		$$ = $1; 
		$$->set_id($2);
	}

NameAccessor: 
  NameAccessor tok_identifier tok_namespace_separator 
	{
		$$ = $1;
		$$->add_namespace($2); 
	}
| 
	{
		$$ = new idl_type_full(); 
	} 


SimpleType:
  tok_string
    {
		b2c::log()->debug("SimpleType => tok_string");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_STRING); 
    }
| tok_bool
    {
		b2c::log()->debug("SimpleType => tok_bool");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_BOOL); 
    }
| tok_i8
    {
		b2c::log()->debug("SimpleType => tok_i8");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_I8); 
    }
| tok_i16
    {
		b2c::log()->debug("SimpleType => tok_i16");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_I16); 
    }
| tok_i32
    {
		b2c::log()->debug("SimpleType => tok_i32");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_I32); 
    }
| tok_i64
    {
		b2c::log()->debug("SimpleType => tok_i64");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_I64); 
    }
| tok_float
    {
		b2c::log()->debug("SimpleType => tok_float");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_FLOAT); 
    }
| tok_double
    {
		b2c::log()->debug("SimpleType => tok_double");

		$$ = new idl_type_simple(idl_type_simple::types::TYPE_DOUBLE); 
    }

FieldValue:
  '=' SimpleExpression
    {
		b2c::log()->debug("FieldValue => '=' SimpleExpression");

		$$ = new idl_field_value(); 
		$$->set_default_expression($2);
    }
|
    {
		b2c::log()->debug("FieldValue =>"); 

		$$ = new idl_field_value();
    }

SimpleExpression: 
   SimpleExpression '+' InnerExpression
	{
		b2c::log()->debug("SimpleExpression => SimpleExpression '+' InnerExpression");

		$$ = $1; 
		$$->add_plus($3);
	}
| SimpleExpression '-' InnerExpression
	{
		b2c::log()->debug("SimpleExpression => SimpleExpression '-' InnerExpression");

		$$ = $1; 
		$$->add_minus($3);
	}
| InnerExpression
	{
		$$ = $1;
	}

InnerExpression:
  FullType 
	{
		b2c::log()->debug("InnerExpression => FullType '.'  tok_identifier");

		$$ = new idl_expression(); 
		auto fv = new idl_expression_value(); 
		fv->set_full_id($1);
		$$->set_value(fv);
	}
| '+' tok_int_constant 
	{
		b2c::log()->debug("'+' => tok_int_constant");

		$$ = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value($2);
		$$->set_value(cv);
	}
| '-' tok_int_constant 
	{
		b2c::log()->debug("'-' => tok_int_constant");

		$$ = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value(0-$2);
		$$->set_value(cv);
	}
| tok_int_constant 
	{
		b2c::log()->debug("InnerExpression => tok_int_constant");

		$$ = new idl_expression(); 
		auto cv = new idl_expression_value(); 
		cv->set_const_value($1);
		$$->set_value(cv);
	}

CommaOrSemicolonOptional:
  ','
    {
	}
| ';'
    {
	}
|
    {
	}
	
SemicolonOptional:
 ';'
    {}
|
    {}

%%
