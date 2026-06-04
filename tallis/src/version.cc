#include <print>
#include <config.h>

void print_version()
{
	std::println("You are using {} version {}", PROJECT_NAME, PROJECT_VER);
}
