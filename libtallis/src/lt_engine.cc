#include <GLFW/glfw3.h>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_cleanup.hpp>

int lt_run(lt_window& win)
{
	lt_data data {lt_init()};

	while (!win.should_close())
	{
		glfwWaitEvents();
	}

	lt_cleanup(data);
	glfwTerminate();
	return 0;
}
