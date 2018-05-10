#pragma once 

#include "generator.hpp"

class cplus_generator : public generator
{
public: 
	cplus_generator(idl_program* prog, std::ostream& os)
		: generator(prog, os)
	{
	}

	result generate() override;

private: 
	result generate_include(const idl_node* node);

	result generate_enum(const idl_node* node); 

	result generate_struct(const idl_node* node);

	result generate_message(const idl_node* node);

	result generate_field(const idl_field* field, bool add_prefix = true);

	result generate_field_functions(const idl_field* field);

	result generate_serialize(const idl_node_struct* sn);

	result generate_expression(const idl_expression* expr);

	result generate_operator(idl_expression::Op op);

	result generate_expression_value(const idl_expression_value* value);

	result generate_prolog();

	result generate_namespace_begin();

	result generate_namespace_end();

	result generate_epilog();

	bool is_enum(const idl_field* field) const;

};