#pragma once 

#include <util/macros.hpp>
#include <string>

class idl_type abstract
{
public:
	idl_type() = default;

	virtual ~idl_type() 
	{
	}

	void set_name(const std::string& name) 
	{ 
		EXPECT(!name.empty());

		name_ = name; 
	}

	const std::string& get_name() const 
	{ 
		return name_; 
	}

	bool is_simple() const
	{
		return is_simple_;
	}

protected:
	std::string name_ = "unknown";
	bool is_simple_ = true;
};
