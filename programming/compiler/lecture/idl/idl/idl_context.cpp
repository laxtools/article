#include "stdafx.h"
#include "idl_context.h"
#include "idl_main.h"
#include <util/macros.hpp>
#include <util/logger.hpp>

idl_context& idl_context::inst()
{
	static idl_context inst_;

	return inst_;
}

int idl_context::start(const config& _config)
{
	if (started_)
	{
		b2c::log()->error("Parsing started already.");

		return -1;
	}

	config_ = _config;

	setup_config();

	RETURN_IF(config_.main_file.empty(), -1);

	started_ = true;

	int rc = 0;

	fstack_.push(file_state{ config_.main_file, false });

	// parsing phase 
	rc = parse();

	// generation phase
	rc = generate();

	return  rc;
}

void idl_context::push_program(idl_program::ptr p)
{
	b2c::log()->trace("Push program {}", p->get_path());

	pstack_.push(p);
}

void idl_context::push_file(const std::string& path)
{
	b2c::log()->trace("Push file {}", path);

	auto iter = states_.find(path);

	EXPECT(iter == states_.end());

	if (iter == states_.end())
	{
		states_[path] = file_state{ path, false };

		fstack_.push(states_[path]);
	}
}

int idl_context::parse()
{
	while (!fstack_.empty())
	{
		auto f = fstack_.top();

		fstack_.pop();

		auto iter = states_.find(f.path);

		if (iter == states_.end() || !iter->second.processed)
		{
			auto rc = ::parse_file(f.path);

			if (rc != 0)
			{
				b2c::log()->error("Fail to parse file: {}", f.path);

				return -1;
			}

			f.processed = true;

			states_[f.path] = f;
		}
		else
		{
			b2c::log()->trace("Met a processed file: {}", f.path);
		}
	}

	return 0;
}

int idl_context::generate()
{
	while (!pstack_.empty())
	{
		auto p = pstack_.top();

		pstack_.pop();

		auto rc = ::generate_program(p);

		if (!rc)
		{
			if (!config_.continue_generation_on_error)
			{
				b2c::log()->error(
					"Exit on generation failure on file: {}", 
					p->get_path()
				);

				return -1;
			}
			else
			{
				b2c::log()->error(
					"Continue generation after failure on file: {}", 
					p->get_path()
				);
			}
		}
	}

	return 0;
}

void idl_context::setup_config()
{
	setup_config_log();
}

void idl_context::setup_config_log()
{
	const char* options[] = { "trace", "debug", "info" };

	for (int i = 0; i < 3; ++i)
	{
		if (config_.log_level == options[i])
		{
			b2c::log()->set_level((spdlog::level::level_enum)i);
		}
	}

	if (b2c::log()->level() == spdlog::level::debug ||
		b2c::log()->level() == spdlog::level::trace)
	{
		b2c::log()->info("Enabling parsing debugging output.");

		yydebug = 1;
	}
}
