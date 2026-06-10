#include <string>
#include <format>
#include <print>
#include <exception>
#include <CLI11/CLI11.hpp>
#include <config.h>
#include "args.hpp"

int tallis_args_parse(int argc, char** argv, tallis_args& args)
{
	try
	{
		std::string desc {std::format("{} {}", PROJECT_NAME, PROJECT_VER)};
		CLI::App app {desc};
		argv = app.ensure_utf8(argv);

		app.add_option("-x, --width", args.width, "Set width in pixels");
		app.add_option("-y, --height", args.height, "Set height in pixels");

		try
		{
			app.parse(argc, argv);
		}
		catch (const CLI::ParseError& e)
		{
			exit(app.exit(e));
		}
	}
	catch (std::exception& e)
	{
		std::println(stderr, "{}", e.what());
		return 1;
	}

	return 0;
}
