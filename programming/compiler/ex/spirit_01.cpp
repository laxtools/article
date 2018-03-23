#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

#include <iostream>
#include <map>

using namespace boost::spirit::x3;

TEST_CASE("a small parser and generator")
{
	// syntax:
	//
	// packet identifier { 
	//    type identifier[=default]; 
	//    type identifier[enum | integer literal];
	// };
	// 
	// type은 int32, int16, uint32, uint16, float, double 
	// 
	// 하나씩 처리한다. 

	SECTION("type parser 1")
	{
		const std::string input = "int32 Hp;";
	}

	SECTION("type parser 2")
	{
		const std::string input = "float Hp = 3.01;";
	}

	SECTION("array type parser")
	{
		const std::string input1 = "float Hp[3]";
		const std::string input2 = "float Hp[3*2+1]";

		// expression validation 
		// - arithematic 
		// - enum reference
	}

	SECTION("packet parser")
	{

	}

	SECTION("code generation")
	{

	}
}

TEST_CASE("spirit")
{
	SECTION("a simple parser")
	{
		std::string input("876 1234.56");
		bool rc = parse(input.cbegin(), input.cend(), int_ >> space >> double_);

		CHECK(rc);
	}

	SECTION("attributes")
	{
		SECTION("example1")
		{
			std::string input("1234");
			int result;
			parse(
				input.begin(), input.end(),
				int_,
				result
			);

			CHECK(result == 1234);
		}

		SECTION("example 2")
		{
			std::string input("pizza");
			auto iter = input.begin();
			auto end_iter = input.end();
			std::string result;
			parse(iter, end_iter,
				*char_,
				result);

			CHECK(result == "pizza");
		}

		SECTION("compatible attributes")
		{
			std::string input(
				"foo : bar ,"
				"gorp : smart ,"
				"falcou : \"crazy frenchman\" "
			);

			auto iter = input.begin();
			auto iter_end = input.end();

			auto name = rule<class name, std::string>()
				= alpha >> *alnum;

			auto quote
				= rule<class quote, std::string>()
				= '"'
				>> lexeme[*(~char_('"'))]
				>> '"';

			auto item = rule<class item, std::pair<std::string, std::string>>()
				= name >> ':' >> (quote | name);

			std::map< std::string, std::string > key_value_map;

			// include fusion std_pair adaptor

			phrase_parse(
				iter, iter_end,
				item % ',',
				space,
				key_value_map
			);
		}
	}

	SECTION("another tutorial")
	{
		// https://ciere.com/cppnow15/x3_docs/spirit/tutorials/

		SECTION("semantic actions")
		{
			std::string  in = "{345, 123, 456}";
			
			auto f = [](auto& ctx) { std::cout << _attr(ctx) << std::endl; };
			phrase_parse(in.begin(), in.end(), '{' >> int_[f] % ',' >> '}', space);

			// 
			// parser[function]으로 지정 
			// 
		}

		SECTION("a complex parser")
		{
			std::string input = "(123.4, 5.4)";

			double rN = 0.0;
			double iN = 0.0;
			auto fr = [&rN, &iN](auto& ctx) { rN = _attr(ctx); };
			auto fi = [&rN, &iN](auto& ctx) { iN = _attr(ctx); };
			auto first = input.begin(); 
			auto last = input.end();

			bool r = phrase_parse(first, last,

				//  Begin grammar
				(
					'(' >> double_[fr] >> -(',' >> double_[fi]) >> ')'
					| double_[fr]
					),
				//  End grammar

				space);

			CHECK(r); 
			CHECK(first == last);

			CHECK(rN == 123.4);
			CHECK(iN == 5.4);
		}

		SECTION("adding numbers")
		{
			std::string input = "1, 2, 3, 4.0, 5";

			double n = 0;
			auto assign = [&n](auto& ctx) { n = _attr(ctx); };
			auto add = [&n](auto& ctx) { n += _attr(ctx); };

			auto first = input.begin(); 
			auto last = input.end();

			bool r = phrase_parse(first, last,

				//  Begin grammar
				(
					double_[assign] >> *(',' >> double_[add])
					)
				,
				//  End grammar
				space);

			CHECK(r); 
			CHECK(n == 15);
		}

		SECTION("getting numbers")
		{
			std::string input = "1, 2, 3, 4, 5.1";

			std::vector<double> v;

			auto push_back = [&v](auto& ctx) { v.push_back(_attr(ctx)); };

			auto first = input.begin(); 
			auto last = input.end(); 

			bool r = phrase_parse(first, last,

				//  Begin grammar
				(
					double_[push_back]
					>> *(',' >> double_[push_back])
					)
				,
				//  End grammar

				space);

			CHECK(r);
			CHECK(v.size() == 5); 
			CHECK(v[4] == 5.1);
		}

		SECTION("list operator")
		{
			std::string input = "1, 2, 3, 4, 5.1";

			std::vector<double> v;

			auto push_back = [&v](auto& ctx) { v.push_back(_attr(ctx)); };

			auto first = input.begin();
			auto last = input.end();

			bool r = phrase_parse(first, last,

				//  Begin grammar
				(
					double_[push_back] % ','
				)
				,
				//  End grammar

				space);

			CHECK(r);
			CHECK(v.size() == 5);
			CHECK(v[4] == 5.1);
		}

		SECTION("list parser attribute")
		{
			std::string input = "1, 2, 3, 4, 5.1";

			auto first = input.begin();
			auto last = input.end();

			std::vector<double> v;

			bool r = phrase_parse(first, last,

				//  Begin grammar
				(
					double_ % ','
				)
				,
				//  End grammar

				space, 
				v);

			CHECK(r);
			CHECK(v.size() == 5);
			CHECK(v[4] == 5.1);
		}

		SECTION("symbol table and non-terminal")
		{
			// symbol table. symbols available during parsing. 
			// spirit is a dynamic parser. 
			// - 파싱 중에 파서의 행동을 변경할 수 있다. 

			// Rules 
			// 

		}
	}
}