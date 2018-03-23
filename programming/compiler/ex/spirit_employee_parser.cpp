#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

#include <iostream>
#include <map>

using namespace boost::spirit::x3;


namespace client {
namespace ast
{
struct employee
{
	int age;
	std::string surname;
	std::string forename;
	double salary;
};
} // ast

namespace parser 
{
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using ascii::char_;

x3::rule<class employee, ast::employee> const employee = "employee";

auto const quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

auto const employee_def =
lit("employee")
>> '{'
>> int_ >> ';'
>> quoted_string >> ';'
>> quoted_string >> ';'
>> double_
>> '}'
;

BOOST_SPIRIT_DEFINE(employee);
} // parser 
} // client

BOOST_FUSION_ADAPT_STRUCT(
	client::ast::employee,
	(int, age)
	(std::string, surname)
	(std::string, forename)
	(double, salary)
)

TEST_CASE("a employee parser")
{
	SECTION("parse")
	{
		std::string input = "employee \n { 25; \"hello\"; \"park\"; 10 } ";

		// ������� ����. 
		// table { 
		//	int cv; 
		//  char a[10]; 
		// };
		// 

		client::ast::employee result;

		auto first = input.begin(); 
		auto last = input.end();

		bool rc = phrase_parse(first, last, client::parser::employee, space, result);

		CHECK(rc);
		CHECK(result.age == 25);

		//
		// a >> b >> c�� fusion::vector<a, b, c>�� attribute�� �ȴ�. 
		// 

		// 
		// attribute�� ����� ���� ������ attribute collapse, 
		// ȣȯ�Ǵ� attribute�� ����Ⱑ �ִ�. 
		// 
	}
}