#pragma once 

#include "idl_node_struct.h"
#include <vector>

class idl_node_message : public idl_node_struct
{
public:
	idl_node_message()
	{
		type_ = Message;
	}

	~idl_node_message()
	{
	}
};

