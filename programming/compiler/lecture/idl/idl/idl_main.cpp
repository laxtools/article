#include "stdafx.h"

#include "idl_main.h"
#include "idl_context.h"
#include "idl_parser.hpp"
#include <idl/generate/csharp_generator.hpp>
#include <idl/generate/cplus_generator.hpp>
#include <util/logger.hpp>
#include <boost/filesystem.hpp>

/**
 * Current file being parsed
 */
std::string g_curpath;

/**
* Global program tree
*/
idl_program* g_program = nullptr; 

idl_symbol_table* g_symbols = nullptr;

/**
 * generator functions
 */
bool generate_program_csharp(idl_program::ptr program);
bool generate_program_cplus(idl_program::ptr program);

/**
* Report an error to the user. This is called yyerror for historical
* reasons (lex and yacc expect the error reporting routine to be called
* this). Call this function to report any errors to the user.
* yyerror takes printf style arguments.
*
* @param fmt C format string followed by additional arguments
*/
void yyerror(const char* fmt, ...) 
{ 
	const int buf_size = 2048;
	char err[buf_size];

	sprintf_s(err, buf_size, "[ERROR:%s:%d] (last token was '%s')\n", g_curpath.c_str(), yylineno, yytext);
	r2c::log()->error(err);
 
	va_list args;
	va_start(args, fmt);
	sprintf_s(err, buf_size, fmt, args);
	va_end(args);

	r2c::log()->error(err);
}

int parse_file(const std::string& path)
{
	FILE* fp = nullptr;

	r2c::log()->info("Start parsing {}", path);

	fopen_s(&fp, path.c_str(), "r");

	yyin = fp;

	if (yyin == nullptr)
	{
		r2c::log()->critical("Cannot open file {}", path);
		return -1;
	}

	auto prog = std::make_shared<idl_program>(path);

	auto rc = parse_program(prog);

	fclose(yyin);

	idl_context::inst().push_program(prog);

	r2c::log()->info("Finished");

	if (rc == 0)
	{
		auto nodes = prog->get_nodes();

		for (auto& n : nodes)
		{
			if (n->get_type() == idl_node::Include)
			{
				auto inode = static_cast<const idl_node_include*>(n);
				idl_context::inst().push_file(inode->get_path_string());
			}
		}
	}

	return rc;
}

int parse_program(idl_program::ptr program)
{
	// singleton
	if (g_symbols == nullptr)
	{
		g_symbols = new idl_symbol_table();
	}

	g_program = program.get(); 

	return yyparse();
}

bool generate_program(idl_program::ptr program)
{
	g_program = program.get();

	if (idl_context::inst().get().generate_cplus)
	{
		auto rc = generate_program_cplus(program);
		RETURN_IF(!rc, false);
	}

	if (idl_context::inst().get().generate_csharp)
	{
		auto rc = generate_program_csharp(program);
		RETURN_IF(!rc, false);
	}

	return true;
}

bool generate_program_csharp(idl_program::ptr program)
{
	namespace fs = boost::filesystem;

	fs::path in(program->get_path());
	 
	in.replace_extension(".cs");

	std::ofstream os(in.c_str());

	r2c::log()->info("Generating {} ...", in.string());

	auto g1 = new csharp_generator(program.get(), os);

	auto rc = g1->generate();

	r2c::log()->info(
		"Finished generation of {} with {}: {}", 
		in.string(), rc.code, rc.value
	);

	return !!rc;
}

bool generate_program_cplus(idl_program::ptr program)
{
	namespace fs = boost::filesystem;

	fs::path in(program->get_path());
	 
	in.replace_extension(".h");

	std::ofstream os(in.c_str());

	r2c::log()->info("Generating {} ...", in.string());

	auto g1 = new cplus_generator(program.get(), os);

	auto rc = g1->generate();

	r2c::log()->info(
		"Finished generation of {} with {}: {}", 
		in.string(), rc.code, rc.value
	);

	return !!rc;
}