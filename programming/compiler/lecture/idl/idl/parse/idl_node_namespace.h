#pragma once 

#include "idl_node.h"
#include <vector>

class idl_node_namespace : public idl_node
{
public:
	idl_node_namespace()
		: idl_node()
	{
		type_ = Namespace;
	}

	~idl_node_namespace()
	{
	}

	void add_namespace(const std::string& ns)
	{
		ns_.push_back(ns);
	}

	const std::vector<std::string>& get_namespace() const
	{
		return ns_;
	}

private:
	std::vector<std::string> ns_;
};

