#pragma once

#include "idl_type.h"
#include <sstream>
#include <vector>

class idl_type_full : public idl_type 
{
public:
	idl_type_full()
		: idl_type()
	{
		is_simple_ = false;
	}

	void add_namespace(const std::string& ns)
	{
		ns_.push_back(ns);
	}

	void set_id(const std::string& id)
	{
		EXPECT(!id.empty());

		id_ = id;

		set_name(get_namespace_string("c++") + id_);
	}

	const std::vector<std::string>& get_namespace() const
	{
		return ns_;
	}

	const std::string get_namespace_string(const std::string& lang) const
	{
		std::ostringstream os;

		for (auto& n : ns_)
		{
			if (lang == "c#")
			{
				os << n << ".";
			}
			else
			{
				os << n << "::";
			}
		}

		return os.str();
	}

	const std::string get_name(const std::string& lang) const
	{
		return get_namespace_string(lang) + id_;
	}

private: 
	std::vector<std::string> ns_; 
	std::string id_;
};
