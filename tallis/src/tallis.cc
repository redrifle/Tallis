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
		tallis_args_struct tallis_args {};
		tallis_args_parse(argc, argv, tallis_args);
		lt_window window("Tallis", tallis_args.width, tallis_args.height);
		lt_run(window);
	}
	catch (std::exception& e)
	{
		std::println(stderr, "{}", e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
