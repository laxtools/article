#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

#include <iostream>
#include <map>

using namespace boost::spirit::x3;

namespace
{

struct hundreds_ : symbols<unsigned>
{
	hundreds_()
	{
		// DSEL w/ operator ()
		add
			("C", 100)
			("CC", 200)
			("CCC", 300)
			("CD", 400)
			("D", 500)
			("DC", 600)
			("DCC", 700)
			("DCCC", 800)
			("CM", 900)
			;
	}

} hundreds;

struct tens_ : symbols<unsigned>
{
	tens_()
	{
		add
		("X", 10)
			("XX", 20)
			("XXX", 30)
			("XL", 40)
			("L", 50)
			("LX", 60)
			("LXX", 70)
			("LXXX", 80)
			("XC", 90)
			;
	}

} tens;

struct ones_ : symbols<unsigned>
{
	ones_()
	{
		add
		("I", 1)
			("II", 2)
			("III", 3)
			("IV", 4)
			("V", 5)
			("VI", 6)
			("VII", 7)
			("VIII", 8)
			("IX", 9)
			;
	}

} ones;

}

namespace roman_parser
{

auto set_zero = [&](auto& ctx) { _val(ctx) = 0; };
auto add1000 = [&](auto& ctx) { _val(ctx) += 1000; };
auto add = [&](auto& ctx) { _val(ctx) += _attr(ctx); };

rule<class roman, unsigned> const roman = "roman";

auto const roman_def =
eps[set_zero]		// eps is epsilon (empty) parser
>>
(
	-(+lit('M')[add1000])
	>> -hundreds[add]
	>> -tens[add]
	>> -ones[add]
	)
	;

BOOST_SPIRIT_DEFINE(roman);
} // parser


TEST_CASE("a roman parser")
{
	SECTION("parse")
	{
		std::string input = "XI";

		unsigned result = 0;

		auto first = input.begin(); 
		auto last = input.end();

		bool rc = phrase_parse(first, last, roman_parser::roman, space, result);

		CHECK(rc);
		CHECK(result == 11);
	}
}