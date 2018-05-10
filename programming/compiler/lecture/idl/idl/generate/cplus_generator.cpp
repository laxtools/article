#include "stdafx.h"
#include "cplus_generator.hpp"
#include <idl/idl_symbol_table.hpp>
#include <idl/parse/idl_program.h>
#include <idl/parse/idl_node.h>
#include <idl/parse/idl_node_include.h>
#include <idl/parse/idl_node_enum.h>
#include <idl/parse/idl_node_struct.h>
#include <idl/parse/idl_node_message.h>
#include <idl/parse/idl_node_namespace.h>
#include <util/logger.hpp>
#include <boost/algorithm/string/replace.hpp>

result cplus_generator::generate()
{
	EXPECT(program_);

	// prolog
	{
		auto rc = generate_prolog();
		RETURN_IF(!rc, rc);
	}

	// include
	{
		bool gen = false;
		auto& nodes = program_->get_nodes();

		for (auto& node : nodes)
		{
			if (node->get_type() == idl_node::Include)
			{
				auto rc = generate_include(node);
				RETURN_IF(!rc, rc);

				gen = true;
			}
		}

		if (gen)
		{
			os_ << std::endl;
		}
	}

	// namespace begin
	{
		auto rc = generate_namespace_begin();
		RETURN_IF(!rc, rc);
	}

	auto& nodes = program_->get_nodes();

	for (auto& node : nodes)
	{
		switch (node->get_type())
		{
			case idl_node::Enum:
			{
				auto rc = generate_enum(node);
				RETURN_IF(!rc, rc);
			}
			break; 
			case idl_node::Struct: 
			{
				auto rc = generate_struct(node);
				RETURN_IF(!rc, rc);
			}
			break; 
			case idl_node::Message:
			{
				auto rc = generate_message(node);
				RETURN_IF(!rc, rc);
			}
			break;
			case idl_node::Include:
			{
				// ignore
			}
			break;
			case idl_node::Namespace:
			{
				// ignore
			}
			break;

			default: 
			{
				// not implemented yet.
				return result(false, "Not implemented node type");
			}
			break;
		}
	}

	// namespace end
	{
		auto rc = generate_namespace_end();
		RETURN_IF(!rc, rc);
	}

	// epilog 
	{
		auto rc = generate_epilog();
		RETURN_IF(!rc, rc);
	}

	return result(true, "Success");
}

result cplus_generator::generate_include(const idl_node* node)
{
	auto in = static_cast<const idl_node_include*>(node);

	std::string path = in->get_path_string();

	EXPECT(path.size() > 3);

	auto np = path.substr(0, path.size() - 3);

	np.append(".h");

	// replace trailing .r2 to .h

	os_ << "#include \"" << np << "\"" << std::endl;

	return result(true, "Success");
}

result cplus_generator::generate_enum(const idl_node* node)
{
	auto en = static_cast<const idl_node_enum*>(node);

	os_ << std::endl;
	os_ << "enum " << en->get_name() << std::endl;
	os_ << "{" << std::endl;

	auto vals = en->get_values();

	for (auto& v : vals)
	{
		os_ << "\t" << v->get_name(); 

		auto dv = v->get_expr();

		if (dv)
		{
			os_ << " = "; 

			generate_expression(dv);
		}

		os_ << "," << std::endl;
	}

	os_ << "};" << std::endl;
	os_ << std::endl;


	return result(true, "Success");
}

result cplus_generator::generate_struct(const idl_node* node)
{
	auto sn = static_cast<const idl_node_struct*>(node);

	os_ << std::endl;
	os_ << "struct " << sn->get_name() << std::endl;
	os_ << "{" << std::endl;

	// field 생성 
	auto fields = sn->get_fields();

	for (auto& field : fields)
	{
		auto rc = generate_field(field, false);

		RETURN_IF(!rc, rc);
	}


	// Pack / Unpack function 
	generate_serialize(sn);

	os_ << "};" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}


result cplus_generator::generate_message(const idl_node* node)
{
	auto sn = static_cast<const idl_node_message*>(node);

	os_ << std::endl;
	os_ << "class " << sn->get_name() << std::endl;
	os_ << "{" << std::endl;

	os_ << "public:" << std::endl;
	os_ << "// field functions" << std::endl;

	// field 생성 
	auto fields = sn->get_fields();

	for (auto& field : fields)
	{
		auto rc = generate_field_functions(field);

		RETURN_IF(!rc, rc);
	}

	os_ << std::endl;

	os_ << "private:" << std::endl;
	os_ << "// field variables " << std::endl;

	for (auto& field : fields)
	{
		auto rc = generate_field(field);

		RETURN_IF(!rc, rc);
	}


	// Pack / Unpack function 
	generate_serialize(sn);

	os_ << "};" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result cplus_generator::generate_field(const idl_field* field, bool add_prefix)
{
	// write in one function, then refactor

	// simple vs full

	if ( field->is_verbatim() )
	{ 
		auto& ss = field->get_verbatim();

		if (!ss.empty())
		{
			os_ << field->get_verbatim();
		}

		return result(true, "Success");
	}
	
	if (field->is_macro_line())
	{
		os_ << field->get_macro_line();
		os_ << std::endl;

		return result(true, "Success");
	}

	// else : normal type field

	os_ << "\t";
	os_ << field->get_type_string("c++");
	os_ << "\t";

	// variable
	if (add_prefix)
	{
		os_ << "__m";
	}

	os_ << field->get_variable_name();

	// array expression
	if (field->is_array_type())
	{
		auto expr = field->get_array_expression();

		os_ << "[";

		auto rc = generate_expression(expr);
		RETURN_IF(!rc, rc);

		os_ << "]";
	}
	else
	{
		// TODO: enum일 경우는 제외. 

		if (field->is_simple_type())
		{
			// field_value 수직이 있으면 처리 

			auto fv = field->get_field_value();

			if (fv && fv->get_default_expression())
			{
				os_ << " = "; 
				
				auto rc = generate_expression(fv->get_default_expression());
				RETURN_IF(!rc, rc);
			}
		}
	}

	os_ << ";" << std::endl;

	return result(true, "Success");
}

result cplus_generator::generate_field_functions(const idl_field* field)
{
	if (field->is_verbatim())
	{
		return result(true, "Success. Verbatim");
	}

	os_ << "\t";

	os_ << "const " << field->get_type_string("c++");

	if (field->is_array_type())
	{
		os_ << "*";
	}
	else if (!field->is_simple_type())
	{
		os_ << "&";
	}

	os_ << " " << "Get" << field->get_variable_name();


	os_ << "() const;";
	os_ << std::endl;

	return result(true, "Success");
}

result cplus_generator::generate_serialize(const idl_node_struct* sn)
{
	// 각 필드에 대해, 
	// - simple 타잎이면 직접 serialize 
	// - enum 참조이면 정수로 변환해서 serialize 
	// - struct 면 함수 호출 
	// 

	return result(false, "Impementing serialize");
}

result cplus_generator::generate_expression(const idl_expression* expr)
{
	// value op value op value ...

	auto ev = expr->get_value();

	generate_expression_value(ev);

	auto exprs = expr->get_exprs();

	// 파싱이 동작하도록 한 후에 작업 진행

	for (auto& ex : exprs)
	{
		auto op = ex->get_operator();

		// operator
		{
			auto rc = generate_operator(op);
			RETURN_IF(!rc, rc);
		}

		// next value
		{
			auto rc = generate_expression(ex);
			RETURN_IF(!rc, rc);
		}
	}

	return result(true, "Success");
}

result cplus_generator::generate_operator(idl_expression::Op op)
{
	switch (op)
	{
	case idl_expression::Op::Plus:
	{
		os_ << " + ";
	}
	break;
	case idl_expression::Op::Minus:
	{
		os_ << " - ";
	}
	break;
	default:
	{
		return result(false, "Invalid expression operator");
	}
	}

	return result(true, "Success");
}

result cplus_generator::generate_expression_value(const idl_expression_value* value)
{
	switch (value->get_type())
	{
	case idl_expression_value::Type::Const:
	{
		os_ << value->get_value();
	}
	break; 
	case idl_expression_value::Type::Simple:
	{
		os_ << value->get_id(); 
	}
	break; 
	case idl_expression_value::Type::Full: 
	{
		auto ft = value->get_full_type();
		os_ << ft->get_name("c++");
	}
	break;
	default: 
	{
		return result(false, "Invalid value type");
	}
	break;
	}

	return result(true, "Success");
}

result cplus_generator::generate_prolog()
{
	os_ << "#pragma once" << std::endl;
	os_ << "#include <stdint.h>" << std::endl;
	os_ << std::endl;
	os_ << "#pragma pack(push, 1)" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result cplus_generator::generate_namespace_begin()
{
	auto ns = program_->get_namespace();

	if (ns)
	{
		auto ns_node = static_cast<const idl_node_namespace*>(ns);
		auto lst = ns_node->get_namespace();

		for (size_t i = 0; i < lst.size(); ++i)
		{
			os_ << "namespace " << lst[i] << " {" << std::endl;
		}
	}
	else
	{
		os_ << "namespace r2" << std::endl;
		os_ << "{" << std::endl;
	}

	return result(true, "Success");
}

result cplus_generator::generate_namespace_end()
{
	auto ns = program_->get_namespace();

	if (ns)
	{
		auto ns_node = static_cast<const idl_node_namespace*>(ns);
		auto lst = ns_node->get_namespace();

		for (size_t i = 0; i < lst.size(); ++i)
		{
			os_ << "} // "  << lst[i] << std::endl;
		}
	}
	else
	{
		os_ << "} // r2" << std::endl;
	}

	return result(true, "Success");
}

result cplus_generator::generate_epilog()
{
	os_ << std::endl;
	os_ << "#pragma pack(pop)" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

bool cplus_generator::is_enum(const idl_field* field) const
{
	auto& fn = field->get_type_string("c++");

	// try with field type name. ex, hello::type1
	{
		auto rc = g_symbols->lookup(fn);

		if (rc && rc.value.type_ == idl_symbol::Enum)
		{
			return true;
		}
	}

	auto ffn = g_program->get_fullname(fn);

	// try with namespace attached. ex, program::hello::type1
	{
		auto rc = g_symbols->lookup(ffn);

		if (rc && rc.value.type_ == idl_symbol::Enum)
		{
			return true;
		}
	}

	return false;
}
