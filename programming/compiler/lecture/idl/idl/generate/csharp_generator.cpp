#include "stdafx.h"
#include "csharp_generator.hpp"
#include <idl/idl_symbol_table.hpp>
#include <idl/parse/idl_program.h>
#include <idl/parse/idl_node.h>
#include <idl/parse/idl_node_enum.h>
#include <idl/parse/idl_node_struct.h>
#include <idl/parse/idl_node_message.h>
#include <idl/parse/idl_node_namespace.h>
#include <util/logger.hpp>

result csharp_generator::generate()
{
	EXPECT(program_);

	// using
	{
		auto rc = generate_using();
		RETURN_IF(!rc, rc);
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
			// Ignore 
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

	return result(true, "Success");
}

result csharp_generator::generate_enum(const idl_node* node)
{
	auto en = static_cast<const idl_node_enum*>(node);

	os_ << std::endl;
	os_ << "public enum " << en->get_name() << std::endl;
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

	os_ << "}" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result csharp_generator::generate_struct(const idl_node* node)
{
	auto sn = static_cast<const idl_node_struct*>(node);

	os_ << std::endl;
	os_ << "public partial class " << sn->get_name() << std::endl;
	os_ << "{" << std::endl;

	// field 생성 
	auto fields = sn->get_fields();

	for (auto& field : fields)
	{
		auto rc = generate_field(field);

		RETURN_IF(!rc, rc);
	}

	// Pack / Unpack function 
	generate_serialize(sn);

	os_ << "}" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result csharp_generator::generate_message(const idl_node* node)
{
	auto sn = static_cast<const idl_node_message*>(node);

	os_ << std::endl;
	os_ << "public partial class " << sn->get_name() << std::endl;
	os_ << "{" << std::endl;

	// field 생성 
	auto fields = sn->get_fields();

	for (auto& field : fields)
	{
		auto rc = generate_field(field);

		RETURN_IF(!rc, rc);
	}

	// Pack / Unpack function 
	generate_serialize(sn);

	os_ << "}" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result csharp_generator::generate_field(const idl_field* field)
{
	// write in one function, then refactor

	// simple vs full
	if (field->is_verbatim())
	{
		return result(true, "Success. Verbatim Block");
	}

	if (field->is_macro_line())
	{
		os_ << field->get_macro_line();
		os_ << std::endl;

		return result(true, "Success");
	}

	os_ << "\tpublic ";

	// TODO: check symbol? 

	os_ << field->get_type_string("c#");

	if (field->is_array_type())
	{
		os_ << "[]";
	}

	os_ << " ";

	// variable
	os_ << field->get_variable_name(); 

	// array expression
	if (field->is_array_type())
	{
		os_ << " = new ";

		os_ << field->get_type_string("c#");

		auto expr = field->get_array_expression();

		os_ << "[";

		auto rc = generate_expression(expr);
		RETURN_IF(!rc, rc);

		os_ << "]";
	}
	else
	{
		// TODO: enum일 경우는 제외. 

		if (field->is_full_type())
		{
			if (!is_enum(field))
			{
				os_ << " = new ";
				os_ << field->get_type_string("c#");
				os_ << "()";
			}
		}
		else
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

result csharp_generator::generate_serialize(const idl_node_struct* sn)
{
	// 각 필드에 대해, 
	// - simple 타잎이면 직접 serialize 
	// - enum 참조이면 정수로 변환해서 serialize 
	// - struct 면 함수 호출 
	// 

	return result(false, "Impementing serialize");
}

result csharp_generator::generate_expression(const idl_expression* expr)
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

result csharp_generator::generate_operator(idl_expression::Op op)
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

result csharp_generator::generate_expression_value(const idl_expression_value* value)
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
		os_ << ft->get_name("c#");
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

result csharp_generator::generate_using()
{
	os_ << "using System;" << std::endl;
	os_ << "using System.IO;" << std::endl;
	os_ << "using System.Text;" << std::endl;
	os_ << std::endl;

	return result(true, "Success");
}

result csharp_generator::generate_namespace_begin()
{
	auto ns = program_->get_namespace();

	if (ns)
	{
		auto ns_node = static_cast<const idl_node_namespace*>(ns);
		auto lst = ns_node->get_namespace();

		os_ << "namespace "; 

		for (size_t i=0; i<lst.size(); ++i)
		{
			if (i > 0)
			{
				os_ << ".";
			}

			os_ << lst[i]; 
		}

		os_ << " { " << std::endl;
	}
	else
	{
		os_ << "namespace r2" << std::endl;
		os_ << "{" << std::endl;
	}

	return result(true, "Success");
}

result csharp_generator::generate_namespace_end()
{
	auto ns = program_->get_namespace();

	if (ns)
	{
		auto ns_node = static_cast<const idl_node_namespace*>(ns);
		auto lst = ns_node->get_namespace();

		os_ << "} // ";

		for (size_t i = 0; i<lst.size(); ++i)
		{
			if (i > 0)
			{
				os_ << ".";
			}

			os_ << lst[i];
		}

		os_ << std::endl;
	}
	else
	{
		os_ << "} // r2" << std::endl;
	}

	return result(true, "Success");
}

bool csharp_generator::is_enum(const idl_field* field) const
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
