#pragma once

#include <util/result.hpp>
#include <string>
#include <unordered_map>

struct idl_symbol
{
	enum type
	{
		None,
		Enum,
		Struct,
		Message
	};

	type type_;
	std::string full_name_;
	std::string simple_name_;
};


class idl_symbol_table
{
public: 
	using result = b2c::result<bool, idl_symbol>;

public:
	result add(const idl_symbol& sym);

	result lookup(const std::string& full_symbol);

	result lookup(const std::string& ns, const std::string& simple);

private: 
	using symbol_map = std::unordered_map<std::string, idl_symbol>;

	symbol_map symbols_;
};