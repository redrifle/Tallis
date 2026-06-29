#include <print>
#include <cstdlib>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_engine.hpp>
#include "args.hpp"
#include "version.hpp"

int main(int argc, char** argv)
{
	print_version();
	try
	{
		auto args {tallis_args_parse(argc, argv)};
		lt_window window("Tallis", args.width, args.height);
		lt_run(window);
	}
	catch (std::exception& e)
	{
		std::println(stderr, "{}", e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
