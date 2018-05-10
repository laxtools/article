#pragma once

#include <string>

/**
*
*/
class idl_node
{
public: 
	enum Type
	{
		None,
		Enum,
		Struct,
		Message,
		Include,
		Namespace
	};

public:
	idl_node()
	{
	}

	virtual ~idl_node()
	{
	}

	Type get_type() const
	{
		return type_;
	}

	void set_name(const std::string& name) 
	{ 
		name_ = name; 
	}

	const std::string& get_name() const 
	{ 
		return name_;  
	}

protected: 
	Type type_ = Type::None;
	std::string name_;
};
