#pragma once 

#include <idl/parse/idl_expression.h>
#include <idl/parse/idl_field.h>
#include <idl/parse/idl_node_struct.h>
#include <util/result.hpp>
#include <iostream>

class idl_program;
class idl_symbol_table;

extern idl_program* g_program;
extern idl_symbol_table* g_symbols;

using result = b2c::result<bool, std::string>;

class generator
{
public: 

public: 
	generator(idl_program* prog, std::ostream& os)
		: program_(prog)
		, os_(os)
	{
		ENSURE(program_);
		ENSURE(os_);
	}

	/// generate source code from prog into ostream
	virtual result generate() = 0;

protected: 
	idl_program* program_ = nullptr;
	std::ostream& os_;
};

