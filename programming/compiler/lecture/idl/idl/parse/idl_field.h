#pragma once 

#include "idl_type.h"
#include "idl_expression.h"
#include "idl_field_value.h"
#include <util/macros.hpp>
#include <sstream>

/**
 * struct / message field  
 */
class idl_field
{
public:
	idl_field() = default;

	~idl_field()
	{
		delete type_;
		delete value_;
		delete array_expr_;
	}

	void set_type(idl_type* type) 
	{ 
		EXPECT(type);
		EXPECT(!type_);

		type_ = type;  
	}

	void set_variable_name(const std::string& var_name) 
	{ 
		EXPECT(!var_name.empty());
		EXPECT(var_name_.empty());

		var_name_ = var_name;  
	}

	void set_simple_type() 
	{ 
		is_simple_type_ = true;  
	}

	void set_full_type() 
	{ 
		is_simple_type_ = false;  
	}

	void set_array_type() 
	{ 
		is_array_type_ = true;  
	}

	void set_field_value(idl_field_value* fv) 
	{ 
		EXPECT(fv);
		EXPECT(!value_);

		value_ = fv;  
	}

	void set_array_expression(idl_expression* expr) 
	{ 
		EXPECT(expr);
		EXPECT(!value_);
		EXPECT(!array_expr_);

		array_expr_ = expr;  
	}

	const idl_type* get_type() const
	{
		return type_;
	}

	const std::string& get_variable_name() const
	{
		return var_name_;
	}

	bool is_simple_type() const
	{
		return is_simple_type_;
	}

	bool is_full_type() const
	{
		return !is_simple_type();
	}

	bool is_array_type() const
	{
		return is_array_type_;
	}

	const idl_field_value* get_field_value() const
	{
		return value_;
	}

	const idl_expression* get_array_expression() const
	{
		return array_expr_;
	}

	const std::string get_type_string(const std::string& lang) const
	{
		// 언어가 바뀌므로 캐싱할 수 없다. 

		std::ostringstream os;

		if (is_simple_type())
		{
			auto st = static_cast<const idl_type_simple*>(get_type());

			os << st->get_typename_in(lang);
		}
		else
		{
			auto ft = static_cast<const idl_type_full*>(get_type());

			os << ft->get_name(lang);
		}

		return os.str();
	}

	const char* get_namespace_separator(const std::string& lang) const
	{
		if (lang == "c#")
		{
			return ".";
		}

		return "::";
	}

	void set_verbatim(const std::string& text)
	{
		verbatim_ = text;
		is_verbatim_ = true;
	}

	const std::string& get_verbatim() const
	{
		EXPECT(is_verbatim());
		return verbatim_;
	}

	bool is_verbatim() const
	{
		return is_verbatim_;
	}

	void set_macro_line(const std::string& line)
	{
		EXPECT(!line.empty());
		macro_line_ = line;
		is_macro_line_ = true;
	}

	const std::string& get_macro_line() const
	{
		EXPECT(is_macro_line());
		return macro_line_;
	}

	bool is_macro_line() const
	{
		return is_macro_line_;
	}

private: 
	idl_type* type_ = nullptr;
	std::string var_name_;
	bool is_simple_type_ = true; 
	bool is_array_type_ = false;
	bool is_verbatim_ = false;
	bool is_macro_line_ = false;
	idl_field_value* value_ = nullptr;
	idl_expression* array_expr_ = nullptr;
	std::string verbatim_;
	std::string macro_line_;
};