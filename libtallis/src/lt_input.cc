#include <GLFW/glfw3.h>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_input.hpp>

void libtallis::toggle_cursor(libtallis::window* w)
{
	GLFWwindow* wp {w->win};
	int mode {glfwGetInputMode(wp, GLFW_CURSOR)};

	if (mode == GLFW_CURSOR_DISABLED)
	{
		mode = GLFW_CURSOR_NORMAL;
	}
	else if (mode == GLFW_CURSOR_NORMAL)
	{
		mode = GLFW_CURSOR_DISABLED;
	}

	glfwSetInputMode(wp, GLFW_CURSOR, mode);
	glfwSetCursorPos(wp, w->width / 2.0f, w->height / 2.0f);
}
