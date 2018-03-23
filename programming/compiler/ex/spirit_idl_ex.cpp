#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <map>

namespace x3 = boost::spirit::x3;

// identifier
namespace
{
x3::rule<class identifier, std::string>
rule_ident = "rule_identifier";

const auto rule_ident_def =
x3::ascii::alpha >> *(x3::ascii::alnum | x3::ascii::char_('_'));

BOOST_SPIRIT_DEFINE(rule_ident);
}

// namespace
namespace 
{
x3::rule<class namespace_, std::vector<std::string>>
rule_namespace = "rule_namespace";

const auto rule_namespace_def =
x3::ascii::lit("namespace")			// don't record "namespace"
>> rule_ident % '.';

BOOST_SPIRIT_DEFINE(rule_namespace);
}

// value expression (uint_ only)
namespace
{
	// vexpr   <- operand >> *(operator operand) 
	// operand <- number | identifier 
	// operator <- '+' | '-' | '*' | '/' 

	// number <- uint_
	// 
}

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
		std::string input = "namespace sample.hello";
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
		// calculator example을 먼저 연습하고 온다. 
	}

	SECTION("include parser")
	{
		// include >> 

	}

	SECTION("using namespace parser")
	{
	}

	SECTION("simple variable parser")
	{

	}

	SECTION("array variable parser")
	{

	}

	SECTION("type parser")
	{
		//
		// [ns1.ns2.]types
		// -ns_path  >> types
		// 

		// type <- primitive_type | user_type
		// user_type <- -ns_path >> identifier 
		//
		// primitive_type <- use symbol table w/ attribute
		// 
	}

	SECTION("variable expression parser")
	{

	}

	SECTION("type expression parser")
	{

	}

	SECTION("enum parser")
	{
		// lit("enum") >> lit"{" 
		// >> *(simple_variable_expression) 
		// >> lit("}")
		// >> -lit(";")
	}

	SECTION("struct parser")
	{
		// can have struct or enum 
		// lit("struct") >> lit("{")  
		// >> *(rule_struct | rule_enum | rule_type_expr)
		// >> lit("}") 
		// >> -lit(";")
	}

	SECTION("packet parser")
	{
		//
		// same as struct parser 
		// code generation is different 
		// can have struct inside 
		//
	}

	SECTION("comment skipper")
	{
		// how to write it in x3? 
		// - 아마도 qi와 유사한 개념들이 옮겨와 있을 듯 
		// - x3 문서 찾기가 참 어렵네
	}

	// 에러 처리가 모든 곳에 필요 
	// - 친절한 메세지가 나와야 함 
	// - 입력이 어디서 잘못된 것인지 알 수 있어야 함 

	// 
	// 코드 생성은 별도 연습문제 
	// - 통합된 AST를 생성
	// - AST를 순회하면서 처리 
	// - c# 코드만 생성하고 테스트 
	//   - c#의 엔디언 처리 정확성 
	//   - c++과 리틀 엔디언 호환 
	// 
}