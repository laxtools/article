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

namespace client {
namespace ast
{

struct rexpr;

struct rexpr_value : x3::variant<
	std::string
	, x3::forward_ast<rexpr>
>
{
	using base_type::base_type;
	using base_type::operator=;
};

typedef std::map<std::string, rexpr_value> rexpr_map;
typedef std::pair<std::string, rexpr_value> rexpr_key_value;

struct rexpr
{
	rexpr_map entries;
};
// rexpr --> entries --> string or rexpr_value --> rexpr (forward_ast : pointer holder) 
// "a" :  { "b" : "c" }
// "d" :  { "e" : { "f" : "g" } }

} // ast 


int const tabsize = 4;

struct rexpr_printer
{
	typedef void result_type;

	rexpr_printer(int indent = 0)
		: indent(indent) {}

	void operator()(ast::rexpr const& ast) const
	{
		tab(indent);
		std::cout << '{' << std::endl;
		for (auto const& entry : ast.entries)
		{
			tab(indent + tabsize);
			std::cout << '"' << entry.first << "\" = ";
			::boost::apply_visitor(rexpr_printer(indent + tabsize), entry.second);
		}
		tab(indent);
		std::cout << '}' << std::endl;
	}

	void operator()(std::string const& text) const
	{
		std::cout << '"' << text << '"' << std::endl;
	}

	void tab(int spaces) const
	{
		for (int i = 0; i < spaces; ++i)
			std::cout << ' ';
	}

	int indent;
};


namespace parser
{
using x3::lit;
using x3::lexeme;

using x3::ascii::char_;
using x3::ascii::string;

x3::rule<class rexpr_value, ast::rexpr_value>
rexpr_value = "rexpr_value";

x3::rule<class rexpr, ast::rexpr>
rexpr = "rexpr";

x3::rule<class rexpr_key_value, ast::rexpr_key_value>
rexpr_key_value = "rexpr_key_value";

auto const quoted_string =
lexeme['"' >> *(char_ - '"') >> '"'];

auto const rexpr_value_def =
quoted_string | rexpr;

auto const rexpr_key_value_def =
quoted_string >> '=' >> rexpr_value;

auto const rexpr_def =
'{' >> *rexpr_key_value >> '}';

// variadic macro. 
BOOST_SPIRIT_DEFINE(rexpr_value, rexpr, rexpr_key_value);

} // parser
} // client

BOOST_FUSION_ADAPT_STRUCT(
	client::ast::rexpr,
	(client::ast::rexpr_map, entries)
)

TEST_CASE("spirit ast")
{
	// 이제 최종 정착지에 가까워졌다. 
	// json과 유사한 형식에 대한 파서를 만든다. 


	SECTION("설명")
	{
		// x3::variant : boost variant을 상속. 상속을 통해 타잎 만들기. 노출

		// x3::forward_ast : type에 대한 포인터 홀더

		//  
	}

	SECTION("parse")
	{
		std::string input = "{"
			"\"color\" = \"blue\""
				"\"size\" = \"29 cm.\""
				"\"position\" = {"
				"\"x\" = \"123\""
				"\"y\" = \"456\""
			"}"
		"}";

		client::ast::rexpr result;

		auto first = input.begin();
		auto last = input.end();

		bool rc = phrase_parse(first, last, client::parser::rexpr, x3::ascii::space, result);

		CHECK(rc);

		client::rexpr_printer(4)(result);
	}

}