#include <GLFW/glfw3.h>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_window.hpp>

int lt_run(lt_window& win)
{
	lt_init();

	while (!win.should_close())
	{
		glfwWaitEvents();
	}
    glfwTerminate();
	return 0;
}
