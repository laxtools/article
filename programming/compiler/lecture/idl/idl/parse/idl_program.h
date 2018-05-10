#pragma once 

#include "idl_node.h"
#include <memory>
#include <string>
#include <vector>

class idl_program
{
public: 
	using ptr = std::shared_ptr<idl_program>;

public:
	idl_program(const std::string& path)
		: path_(path)
	{}

	~idl_program()
	{
		for (auto& np : nodes_)
		{
			delete np;
		}

		nodes_.clear();
	}

	void add_node(idl_node* node)
	{
		EXPECT(node);

		nodes_.push_back(node);
	}

	const std::string& get_path() const
	{
		return path_;
	}

	const std::vector<idl_node*>& get_nodes() const
	{
		return nodes_;
	}

	const idl_node* get_namespace() const
	{
		for (auto& n : nodes_)
		{
			if (n->get_type() == idl_node::Namespace)
			{
				return n;
			}
		}

		return nullptr;
	}

	const std::string get_fullname(const std::string& name)
	{
		auto ns = get_namespace();

		if (ns)
		{
			return ns->get_name() + "::" + name;
		}
		
		return name;
	}

	void set_verbatim_block(const std::string& text)
	{
		verbatim_ = text;
	}

	const std::string& get_verbatim_block() const
	{
		return verbatim_;
	}

	void clear_verbatim_block()
	{
		verbatim_.clear();
	}

private: 
	std::string path_;
	std::vector<idl_node*> nodes_;
	std::string verbatim_;
};
