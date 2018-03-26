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
// include "" 또는 include <>
// lexeme으로 문자열을 통째로 읽고 처리
// 경로 등은 별도로 처리
// C++ 17 filesystem이나 외부 라이브러리 사용하여 처리
x3::rule<class include_, std::string>
rule_include = "rule_include";

const auto rule_include_def =
x3::ascii::lit("include")
>> x3::lexeme['"' >> *(x3::ascii::char_ - '"') >> '"'] // idl 파일들은 현재 폴더 기준
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

// | 로 연결된 다른 타잎 속성에 대해 variant를 쓰는 건 맞다. 
// 

struct attr_variable
{
	std::string id; 
	attr_var_assign va;
};

x3::rule<class variable, attr_variable>
rule_variable = "rule_variable"; 

// assignment / array가 아닐 경우 ; 처리 
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
		// value expression은 일단 생략하고 문자열로 처리한다. 
		// 의미를 검사하는 건 좀 더 익숙해지면 진행
		// 코드 생성이 어려워짐 
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
		// rule이면 x3::skip으로 전달할 수 있는 것으로 보인다. 
		// 파싱되면 매칭된 만큼 스킵한다. 

		std::string input = "using sample.he // llo ";
		std::vector<std::string> result;

		auto first = input.cbegin();
		auto last = input.cend();

		// rule_comment를 직접 파서로 제공 가능하다. 
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

			// 속성 타잎이 정확하게 일치하면 variant를 포함 잘 동작한다. 
			// transform_attr 함수 관련 오류일 경우
			// 실수하면 찾기가 어려운데 에러의 Source / Dest 타잎을 잘 봐야 한다. 
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

			// variant 값을 사용하기 위한 방법을 applay_visitor외에 찾는다. 
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

			// 문법에서 option 항목이 제일 앞에 올 수는 없다
			// 이럴 경우 *를 사용해야 제대로 동작한다. (정확한 건 좀 더 봐야...) 
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

			// 에러가 최초에 발생. error 핸들러로 원인을 찾아 본다. 
			// - 에러 핸들러를 호출하기 전에 실패 
			// - 무엇이 문제인가? 
			// 규칙을 문자열로 단순화 시켜 체크 
			// - result.var가 [3];로 나온다. 
			// - 이는 앞쪽 type_ident 룰이 더 많은 문자를 소모해서 발생한 문제
			// - rule_ident가 lexeme으로 공백을 허용하면 안 되는 점이 누락되어 발생 
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

			// rule % ','로 정의된 경우에 attribute를 container 타잎으로 검증한다. 
			// - rule에 전달된 타잎 자체가 container여야 한다. 
			// - fusion으로 struct를 adapt 시켜줄 수는 있다. 

			// attr_enum_val::attr_enum_val(attr_enum_val &&)': 인수 1을(를) 'char'에서 'const `anonymous-namespace'::attr_enum_val &'(으)로 변환할 수 없습니다.

			// % 로 리스트 처리가 안정적이지 않다. 
			// - 복잡한 생성식 보다는 간단한 것들로 구축한다. 
			// - 작게 나눠서 처리하는 게 좋다. 
			// - 속성은 std::pair 등을 사용해서 테스트 한 후 struct로 만든다. 
			// - MPL 디버깅은 여전히 어렵다. 컴파일 시간에만 디버깅 가능해서 더욱 그렇다.  
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

		// 속성을 파싱 결과 값이랑 잘 맞추는 연습이 좀 더 필요하다. 
		// - vars만 갖고 파싱하면 잘 됨 
		// 
		// enum을 포함하면 컴파일 에러 발생 
		// - error C2679 : 이항 '=' : 오른쪽 피연산자로 'std::vector<attr_var_decl, std::allocator<_Ty >> ' 형식을 사용하는 연산자가 없거나 허용되는 변환이 없습니다.
		// - variant에서 발생
		// - assignment 가능하게 할 수 있을까? 
		// - rule_var_decls를 추가해서 속성을 별도로 가져오도록 해서 해결 
		// - 이와 같이 복잡한 식을 별도로 나누고 속성을  받아오도록 하면 대체로 해결됨 
		// - 여전히 variant / mpl / fusion으로 연결된 코드들은 복잡함 
		// 
		// TODO: embed 키워드 처리 
		// - 변수 선언만 포함하는 구조체 
		// 
	}

	SECTION("message parser")
	{
		//
		// same as struct parser 
		// code generation is different 
		// can have structs inside 

		// embed 키워드로 처리한다. 
		// 
		// 전체 설계하면 됨 
	}

	// 에러는 ID (Tag)의 on_error() 함수로 처리 

	// 코드 생성시 namespace 문자열 치환 방식 처리 
	// - 파싱 단계에서 다 처리되면 최고이긴 하지만 
	// - 거의 모든 expression이 올 수 있어 생각보다 어려움
}