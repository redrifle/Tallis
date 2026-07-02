#include <GLFW/glfw3.h>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_cleanup.hpp>

namespace lt = libtallis;

int libtallis::run(lt::window& win)
{
	lt::context context {lt::init()};

	while (!win.should_close())
	{
		glfwWaitEvents();
	}

	lt::cleanup(context);
	glfwTerminate();
	return 0;
}
