#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <map>
#include <vector>

namespace x3 = boost::spirit::x3;

// identifier
namespace
{
x3::rule<class identifier, std::string>
rule_ident = "rule_identifier";

const auto rule_ident_def =
x3::lexeme[x3::ascii::alpha >> *(x3::ascii::alnum | x3::ascii::char_('_'))];

BOOST_SPIRIT_DEFINE(rule_ident);
}

// namespace
namespace 
{
x3::rule<class namespace_, std::vector<std::string>>
rule_namespace = "rule_namespace";

const auto rule_namespace_def =
x3::ascii::lit("namespace")			// don't record "namespace"
>> rule_ident % '.'
>> -x3::lit(';');

BOOST_SPIRIT_DEFINE(rule_namespace);
}

// include parser 
namespace
{
// include "" �Ǵ� include <>
// lexeme���� ���ڿ��� ��°�� �а� ó��
// ��� ���� ������ ó��
// C++ 17 filesystem�̳� �ܺ� ���̺귯�� ����Ͽ� ó��
x3::rule<class include_, std::string>
rule_include = "rule_include";

const auto rule_include_def =
x3::ascii::lit("include")
>> x3::lexeme['"' >> *(x3::ascii::char_ - '"') >> '"'] // idl ���ϵ��� ���� ���� ����
>> -x3::lit(';');

BOOST_SPIRIT_DEFINE(rule_include);
}

// using parser 
namespace
{
// using ns1.ns2.ns3
x3::rule<class using_, std::vector<std::string>>
rule_using = "rule_using";

const auto rule_using_def =
x3::ascii::lit("using")			
>> rule_ident % '.'
>> -x3::lit(';');

BOOST_SPIRIT_DEFINE(rule_using);
}

namespace
{
x3::rule<class comment, std::string>
rule_comment = "rule_comment";

const auto rule_comment_def =
x3::ascii::space | x3::lit("//") >> *(x3::char_ - x3::eol)>> x3::eol; 

BOOST_SPIRIT_DEFINE(rule_comment);
}

// variable parser 
namespace
{

struct attr_assignment
{
	std::string expr;
};

// assignment
x3::rule<class assignment, attr_assignment>
rule_assignment = "rule_assignment";

const auto rule_assignment_def =
x3::lit("=")
>> x3::lexeme[+(x3::ascii::char_ - ';')];

struct attr_array
{
	std::string expr;
};

// array 
x3::rule<class array_, attr_array>
rule_array = "rule_array"; 

const auto rule_array_def =
x3::lit("[")
>> x3::lexeme[+(x3::ascii::char_ - ']')] >> x3::lit("]");

struct attr_var_assign : x3::variant<
	  x3::forward_ast<attr_assignment>,
	  x3::forward_ast<attr_array>
	>
{
	using base_type::base_type;
	using base_type::operator=;
};

// | �� ����� �ٸ� Ÿ�� �Ӽ��� ���� variant�� ���� �� �´�. 
// 

struct attr_variable
{
	std::string id; 
	attr_var_assign va;
};

x3::rule<class variable, attr_variable>
rule_variable = "rule_variable"; 

// assignment / array�� �ƴ� ��� ; ó�� 
const auto rule_variable_def =
rule_ident >> -(rule_assignment | rule_array) >> x3::lit(";");

BOOST_SPIRIT_DEFINE(rule_assignment, rule_array, rule_variable);

}

BOOST_FUSION_ADAPT_STRUCT(
	attr_assignment,
	(std::string, expr)
);

BOOST_FUSION_ADAPT_STRUCT(
	attr_array,
	(std::string, expr)
);

BOOST_FUSION_ADAPT_STRUCT(
	attr_variable,
	(std::string, id)
	(attr_var_assign, va)
);

// type decl
namespace
{

struct attr_type_ident
{
	std::vector<std::string> ns; 
	std::string id;
};

x3::rule<class type_ident, attr_type_ident> rule_type_ident =
"rule_type_ident";

const auto rule_type_ident_def =
*(rule_ident >> x3::lit("::") ) >> rule_ident;


struct attr_var_decl
{
	attr_type_ident type; 
	attr_variable var;
};

struct var_decl;

x3::rule<var_decl, attr_var_decl> rule_var_decl =
"rule_var_decl";

const auto rule_var_decl_def =
rule_type_ident >> rule_variable;

BOOST_SPIRIT_DEFINE(rule_type_ident, rule_var_decl);

struct var_decl
{
	template <typename Iterator, typename Exception, typename Context>
	x3::error_handler_result
	on_error(Iterator&, Iterator const& last, Exception const& x, Context const& context)
	{
		std::cout
			<< "Error! Expecting: "
			<< x.which()
			<< " here: \""
			<< std::string(x.where(), last)
			<< "\""
			<< std::endl
			;
		return x3::error_handler_result::fail;
	}
};
} // var_decl

BOOST_FUSION_ADAPT_STRUCT(
	attr_type_ident,
	ns, id
);

BOOST_FUSION_ADAPT_STRUCT(
	attr_var_decl,
	type, var
);


// enum
namespace
{

struct attr_enum_val
{
	std::string id; 
	std::string expr;
};

struct attr_enum_vals
{
	std::vector<attr_enum_val> vals;
};

x3::rule<class enum_assign, std::string> rule_enum_assign =
"rule_enum_assign";

const auto rule_enum_assign_def = 
(x3::lit("=") >> x3::lexeme[+(x3::ascii::char_ - ',' - '}')]);

x3::rule<class enum_ident_expr, attr_enum_val> rule_enum_ident_expr =
"rule_enum_ident_expr";

const auto rule_enum_ident_expr_def =
rule_ident >> -rule_enum_assign;

x3::rule<class enum_vals, std::vector<attr_enum_val>> rule_enum_vals =
"rule_enum_vals";

const auto rule_enum_vals_def =
rule_enum_ident_expr >> *(x3::lit(",") >> rule_enum_ident_expr);

struct attr_enum
{
	std::string id;
	attr_enum_vals vals;
};

x3::rule<class enum_, attr_enum>  rule_enum =
"rule_enum";

const auto rule_enum_def =
x3::lit("enum")
>> rule_ident >> "{"
>> rule_enum_vals
>> "}" >> -x3::lit(";");

BOOST_SPIRIT_DEFINE(rule_enum_ident_expr, rule_enum_assign, rule_enum_vals, rule_enum);

} // enum

BOOST_FUSION_ADAPT_STRUCT(attr_enum_val, 
	id, expr);

BOOST_FUSION_ADAPT_STRUCT(attr_enum_vals,
	vals
);

BOOST_FUSION_ADAPT_STRUCT(attr_enum,
	id, vals	
);

// struct 
namespace
{

struct attr_vars
{
	std::vector<attr_var_decl> vars;
};

struct attr_struct
{
	std::string id;
	attr_enum eval;
	attr_vars vars;
};

//
// struct <- 
//  lit("struct") >> ident >> "{"
//  enum_  >> *var_decl 
//  >> "}" >> -";"
//

x3::rule<class var_decls, attr_vars> rule_var_decls =
"rule_var_decls";

const auto rule_var_decls_def =
*rule_var_decl;


x3::rule<class struct_, attr_struct> rule_struct =
"rule_struct";

const auto rule_struct_def =
x3::lit("struct") >> rule_ident >> x3::lit("{")
>> -rule_enum 
>> rule_var_decls
>> x3::lit("}") >> -x3::lit(";");


//
// embed <- 
//  lit("embed") >> ident >> "{"
//   +var_decl
//  >> "}" >> -";"
//

BOOST_SPIRIT_DEFINE(rule_var_decls, rule_struct);

} // struct

BOOST_FUSION_ADAPT_STRUCT(attr_vars, 
	vars
);

BOOST_FUSION_ADAPT_STRUCT(attr_struct, 
	id, 
	eval, 
	vars	
);



TEST_CASE("spirit message idl exercise")
{
	SECTION("ident parser")
	{
		std::string input = "  abc_3_4 "; 
		std::string result; 

		auto first = input.cbegin(); 
		auto last = input.cend(); 

		bool rc = phrase_parse(first, last, rule_ident, x3::ascii::space, result);

		CHECK(rc);
		CHECK(result == "abc_3_4");
	}

	SECTION("namespace parser")
	{
		std::string input = "namespace sample.hello  ;";
		std::vector<std::string> result;

		auto first = input.cbegin();
		auto last = input.cend();

		bool rc = phrase_parse(first, last, rule_namespace, x3::ascii::space, result);

		CHECK(rc);
		CHECK(result[0] == "sample");
		CHECK(result[1] == "hello");
	}

	SECTION("value expression parser")
	{
		// value expression�� �ϴ� �����ϰ� ���ڿ��� ó���Ѵ�. 
		// �ǹ̸� �˻��ϴ� �� �� �� �ͼ������� ����
		// �ڵ� ������ ������� 
	}

	SECTION("include parser")
	{
		std::string input = " include \"game/sample1.idl\"";

		std::string result;

		auto first = input.cbegin();
		auto last = input.cend();

		bool rc = phrase_parse(first, last, rule_include, x3::ascii::space, result);

		CHECK(rc);
		CHECK(result == "game/sample1.idl");
	}

	SECTION("using namespace parser")
	{
		std::string input = "using sample.hello";
		std::vector<std::string> result;

		auto first = input.cbegin();
		auto last = input.cend();

		bool rc = phrase_parse(first, last, rule_using, x3::ascii::space, result);

		CHECK(rc);
		CHECK(result[0] == "sample");
		CHECK(result[1] == "hello");
	}

	SECTION("comment skipper")
	{
		// rule�̸� x3::skip���� ������ �� �ִ� ������ ���δ�. 
		// �Ľ̵Ǹ� ��Ī�� ��ŭ ��ŵ�Ѵ�. 

		std::string input = "using sample.he // llo ";
		std::vector<std::string> result;

		auto first = input.cbegin();
		auto last = input.cend();

		// rule_comment�� ���� �ļ��� ���� �����ϴ�. 
		// 
		bool rc = phrase_parse(first, last, rule_using, rule_comment, result);
		CHECK(result.size() == 2);
		CHECK(result[1] == "he");
	}

	SECTION("variable parser")
	{
		SECTION("assignment expr")
		{
			std::string input = "= 3*5;";
			attr_assignment result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_assignment, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.expr == "3*5");
		}

		SECTION("array expr")
		{
			std::string input = "[3*5];";
			attr_array result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_array, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.expr == "3*5");
		}

		SECTION("array variable")
		{
			std::string input = "id[3];";
			attr_variable result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_variable, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.id == "id");

			// �Ӽ� Ÿ���� ��Ȯ�ϰ� ��ġ�ϸ� variant�� ���� �� �����Ѵ�. 
			// transform_attr �Լ� ���� ������ ���
			// �Ǽ��ϸ� ã�Ⱑ ���� ������ Source / Dest Ÿ���� �� ���� �Ѵ�. 
		}

		SECTION("variable with a default value")
		{
			std::string input = "id = 3;";
			attr_variable result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_variable, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.id == "id");

			// variant ���� ����ϱ� ���� ����� applay_visitor�ܿ� ã�´�. 
			auto ast_assign = boost::get<x3::forward_ast<attr_assignment>>(result.va);
			CHECK(ast_assign.get().expr == "3");
		}
	}

	SECTION("variable decl parser")
	{
		SECTION("type id")
		{
			std::string input = "a::b::id";
			attr_type_ident result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_type_ident, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.id == "id");

			// �������� option �׸��� ���� �տ� �� ���� ����
			// �̷� ��� *�� ����ؾ� ����� �����Ѵ�. (��Ȯ�� �� �� �� ����...) 
		}

		SECTION("var decl")
		{
			std::string input = "a::b::id v[3];";
			attr_var_decl result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_var_decl, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.var.id == "v");

			// ������ ���ʿ� �߻�. error �ڵ鷯�� ������ ã�� ����. 
			// - ���� �ڵ鷯�� ȣ���ϱ� ���� ���� 
			// - ������ �����ΰ�? 
			// ��Ģ�� ���ڿ��� �ܼ�ȭ ���� üũ 
			// - result.var�� [3];�� ���´�. 
			// - �̴� ���� type_ident ���� �� ���� ���ڸ� �Ҹ��ؼ� �߻��� ����
			// - rule_ident�� lexeme���� ������ ����ϸ� �� �Ǵ� ���� �����Ǿ� �߻� 
		}
	}

	SECTION("enum parser")
	{
		SECTION("enum value")
		{
			std::string input = "a=1, b = 5, c";
			attr_enum_vals result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_enum_vals, x3::ascii::space, result);

			CHECK(rc);
			CHECK(result.vals.size() == 3);

			// rule % ','�� ���ǵ� ��쿡 attribute�� container Ÿ������ �����Ѵ�. 
			// - rule�� ���޵� Ÿ�� ��ü�� container���� �Ѵ�. 
			// - fusion���� struct�� adapt ������ ���� �ִ�. 

			// attr_enum_val::attr_enum_val(attr_enum_val &&)': �μ� 1��(��) 'char'���� 'const `anonymous-namespace'::attr_enum_val &'(��)�� ��ȯ�� �� �����ϴ�.

			// % �� ����Ʈ ó���� ���������� �ʴ�. 
			// - ������ ������ ���ٴ� ������ �͵�� �����Ѵ�. 
			// - �۰� ������ ó���ϴ� �� ����. 
			// - �Ӽ��� std::pair ���� ����ؼ� �׽�Ʈ �� �� struct�� �����. 
			// - MPL ������� ������ ��ƴ�. ������ �ð����� ����� �����ؼ� ���� �׷���.  
			// - 
		}

		SECTION("enum ")
		{
			std::string input = "enum vals { a=1, b = 5, c };`";
			attr_enum result;

			auto first = input.cbegin();
			auto last = input.cend();

			bool rc = phrase_parse(first, last, rule_enum, x3::ascii::space, result);

			CHECK(rc);

			CHECK(result.id == "vals");
			CHECK(result.vals.vals.size() == 3);
			CHECK(result.vals.vals[0].id == "a");
			CHECK(result.vals.vals[0].expr == "1");
		}
	}

	SECTION("struct parser")
	{
		std::string input = "struct test { "
							"enum k { \n vv = 3, v2, v5, v6 };  \n "
							"int a[3];"
							"float v = 3;"
							"ns1::type_1 val; "
							"};";

		attr_struct result;

		auto first = input.cbegin();
		auto last = input.cend();

		bool rc = phrase_parse(first, last, rule_struct, x3::ascii::space, result);

		CHECK(rc);

		// �Ӽ��� �Ľ� ��� ���̶� �� ���ߴ� ������ �� �� �ʿ��ϴ�. 
		// - vars�� ���� �Ľ��ϸ� �� �� 
		// 
		// enum�� �����ϸ� ������ ���� �߻� 
		// - error C2679 : ���� '=' : ������ �ǿ����ڷ� 'std::vector<attr_var_decl, std::allocator<_Ty >> ' ������ ����ϴ� �����ڰ� ���ų� ���Ǵ� ��ȯ�� �����ϴ�.
		// - variant���� �߻�
		// - assignment �����ϰ� �� �� ������? 
		// - rule_var_decls�� �߰��ؼ� �Ӽ��� ������ ���������� �ؼ� �ذ� 
		// - �̿� ���� ������ ���� ������ ������ �Ӽ���  �޾ƿ����� �ϸ� ��ü�� �ذ�� 
		// - ������ variant / mpl / fusion���� ����� �ڵ���� ������ 
		// 
		// TODO: embed Ű���� ó�� 
		// - ���� ���� �����ϴ� ����ü 
		// 
	}

	SECTION("message parser")
	{
		//
		// same as struct parser 
		// code generation is different 
		// can have structs inside 

		// embed Ű����� ó���Ѵ�. 
		// 
		// ��ü �����ϸ� �� 
	}

	// ������ ID (Tag)�� on_error() �Լ��� ó�� 

	// �ڵ� ������ namespace ���ڿ� ġȯ ��� ó�� 
	// - �Ľ� �ܰ迡�� �� ó���Ǹ� �ְ��̱� ������ 
	// - ���� ��� expression�� �� �� �־� �������� �����
}