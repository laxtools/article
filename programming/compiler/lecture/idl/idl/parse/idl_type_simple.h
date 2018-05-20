#pragma once

#include <cstdlib>
#include "idl_type.h"

class idl_type_simple : public idl_type {
public:
	/**
	* Enumeration of thrift type types
	*/
	enum types {
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_I8,
		TYPE_I16,
		TYPE_I32,
		TYPE_I64,
		TYPE_FLOAT,
		TYPE_DOUBLE
	};

	idl_type_simple(types type)
		: idl_type(), type_(type)
	{
		set_name(type_name(type_));

		is_simple_ = true;
	}

	types get_type() const 
	{ 
		return type_; 
	}

	bool is_string() const 
	{ 
		return type_ == TYPE_STRING; 
	}

	bool is_bool() const 
	{ 
		return type_ == TYPE_BOOL; 
	}

	static std::string type_name(types tbase) 
	{
		switch (tbase) {
		case TYPE_STRING:
			return "string";
			break;
		case TYPE_BOOL:
			return "bool";
			break;
		case TYPE_I8:
			return "i8";
			break;
		case TYPE_I16:
			return "i16";
			break;
		case TYPE_I32:
			return "i32";
			break;
		case TYPE_I64:
			return "i64";
			break;
		case TYPE_FLOAT:
			return "float";
			break;
		case TYPE_DOUBLE:
			return "double";
			break;
		default:
			return "(unknown)";
			break;
		}
	}

	std::string get_typename_in(const std::string& lang) const
	{
		if (lang == "c#")
		{
			return get_typename_in_csharp(type_);
		}
		else if (lang == "c++")
		{
			return get_typename_in_cplus(type_);
		}

		return get_name();
	}

	std::string get_typename_in_csharp(types type) const
	{
		switch (type) {
		case TYPE_STRING:
			return "string";
			break;
		case TYPE_BOOL:
			return "bool";
			break;
		case TYPE_I8:
			return "byte";
			break;
		case TYPE_I16:
			return "short";
			break;
		case TYPE_I32:
			return "int";
			break;
		case TYPE_I64:
			return "long";
			break;
		case TYPE_FLOAT:
			return "float";
			break;
		case TYPE_DOUBLE:
			return "double";
			break;
		default:
			return "(unknown)";
			break;
		}
	}

	std::string get_typename_in_cplus(types type) const
	{
		switch (type) {
		case TYPE_STRING:
			return "string";
			break;
		case TYPE_BOOL:
			return "bool";
			break;
		case TYPE_I8:
			return "int8_t";
			break;
		case TYPE_I16:
			return "int16_t";
			break;
		case TYPE_I32:
			return "int32_t";
			break;
		case TYPE_I64:
			return "int64_t";
			break;
		case TYPE_FLOAT:
			return "float";
			break;
		case TYPE_DOUBLE:
			return "double";
			break;
		default:
			return "(unknown)";
			break;
		}
	}

private:
	types type_;
};
