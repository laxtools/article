#include "stdafx.h"
#include <catch.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <list>
#include <map>

namespace x3 = boost::spirit::x3;

namespace client {
namespace ast
{
///////////////////////////////////////////////////////////////////////////
//  The AST
///////////////////////////////////////////////////////////////////////////
struct nil {};
struct signed_;
struct expression;

struct operand : x3::variant<
	nil
	, unsigned int
	, x3::forward_ast<signed_>
	, x3::forward_ast<expression>
>
{
	using base_type::base_type;
	using base_type::operator=;
};

struct signed_
{
	char sign;
	operand operand_;
};

struct operation
{
	char operator_;
	operand operand_;
};

struct expression
{
	operand first;
	std::list<operation> rest;
};

// print function for debugging
inline std::ostream& operator<<(std::ostream& out, nil) { out << "nil"; return out; }
} // ast
} // client

BOOST_FUSION_ADAPT_STRUCT(client::ast::signed_,
	sign, operand_
)

BOOST_FUSION_ADAPT_STRUCT(client::ast::operation,
	operator_, operand_
)

BOOST_FUSION_ADAPT_STRUCT(client::ast::expression,
	first, rest
)

namespace client
{
///////////////////////////////////////////////////////////////////////////
//  The Virtual Machine
///////////////////////////////////////////////////////////////////////////
enum byte_code
{
	op_neg,     //  negate the top stack entry
	op_add,     //  add top two stack entries
	op_sub,     //  subtract top two stack entries
	op_mul,     //  multiply top two stack entries
	op_div,     //  divide top two stack entries
	op_int,     //  push constant integer into the stack
};

class vmachine
{
public:

	vmachine(unsigned stackSize = 4096)
		: stack(stackSize)
		, stack_ptr(stack.begin())
	{
	}

	int top() const { return stack_ptr[-1]; };
	void execute(std::vector<int> const& code);

private:
	std::vector<int> stack;
	std::vector<int>::iterator stack_ptr;
};

void vmachine::execute(std::vector<int> const& code)
{
	std::vector<int>::const_iterator pc = code.begin();
	stack_ptr = stack.begin();

	while (pc != code.end())
	{
		switch (*pc++)
		{
		case op_neg:
			stack_ptr[-1] = -stack_ptr[-1];
			break;

		case op_add:
			--stack_ptr;
			stack_ptr[-1] += stack_ptr[0];
			break;

		case op_sub:
			--stack_ptr;
			stack_ptr[-1] -= stack_ptr[0];
			break;

		case op_mul:
			--stack_ptr;
			stack_ptr[-1] *= stack_ptr[0];
			break;

		case op_div:
			--stack_ptr;
			stack_ptr[-1] /= stack_ptr[0];
			break;

		case op_int:
			*stack_ptr++ = *pc++;
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//  The Compiler
///////////////////////////////////////////////////////////////////////////
struct compiler
{
	typedef void result_type;

	std::vector<int>& code;
	compiler(std::vector<int>& code)
		: code(code) {}

	void operator()(ast::nil) const { BOOST_ASSERT(0); }
	void operator()(unsigned int n) const
	{
		code.push_back(op_int);
		code.push_back(n);
	}

	void operator()(ast::operation const& x) const
	{
		boost::apply_visitor(*this, x.operand_);
		switch (x.operator_)
		{
		case '+': code.push_back(op_add); break;
		case '-': code.push_back(op_sub); break;
		case '*': code.push_back(op_mul); break;
		case '/': code.push_back(op_div); break;
		default: BOOST_ASSERT(0); break;
		}
	}

	void operator()(ast::signed_ const& x) const
	{
		boost::apply_visitor(*this, x.operand_);
		switch (x.sign)
		{
		case '-': code.push_back(op_neg); break;
		case '+': break;
		default: BOOST_ASSERT(0); break;
		}
	}

	void operator()(ast::expression const& x) const
	{
		boost::apply_visitor(*this, x.first);
		for (ast::operation const& oper : x.rest)
		{
			(*this)(oper);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
//  The calculator grammar
///////////////////////////////////////////////////////////////////////////////
namespace calculator_grammar
{
using x3::uint_;
using x3::char_;

struct expression_class;
struct term_class;
struct factor_class;

x3::rule<expression_class, ast::expression> const expression("expression");
x3::rule<term_class, ast::expression> const term("term");
x3::rule<factor_class, ast::operand> const factor("factor");

auto const expression_def =
term
>> *((char_('+') > term)
	| (char_('-') > term)
	)
	;

auto const term_def =
factor
>> *((char_('*') > factor)
	| (char_('/') > factor)
	)
	;

auto const factor_def =
uint_
| '(' > expression > ')'
| (char_('-') > factor)
| (char_('+') > factor)
;

BOOST_SPIRIT_DEFINE(
	expression
	, term
	, factor
);

struct expression_class
{
	//  Our error handler
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

auto calculator = expression;
}

using calculator_grammar::calculator;
}

TEST_CASE("calculator example")
{
	// 
	// learn to parse value expressions 
	// a large example 
	// - variable / expression  
	// - vm to calculate
	// 

	SECTION("run parser")
	{
		typedef std::string::const_iterator iterator_type;
		typedef client::ast::expression ast_expression;
		typedef client::compiler compiler;

		std::string str = "3 * 2 + 1";

		client::vmachine mach;              // Our virtual machine
		std::vector<int> code;              // Our VM code
		auto& calc = client::calculator;    // Our grammar
		ast_expression expression;          // Our program (AST)
		compiler compile(code);             // Compiles the program

		iterator_type iter = str.begin();
		iterator_type const end = str.end();
		boost::spirit::x3::ascii::space_type space;
		bool r = phrase_parse(iter, end, calc, space, expression);

		CHECK(r); 
		CHECK(iter == end);

		compile(expression); // code generation

		mach.execute(code);  // execute
	}
}