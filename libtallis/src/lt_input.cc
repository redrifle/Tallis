#include <GLFW/glfw3.h>
#include <libtallis/lt_window.hpp>

void lt_toggle_cursor(lt_window* w)
{
	GLFWwindow* wp = w->get_pointer();
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
	glfwSetCursorPos(wp, w->get_width() / 2.0f, w->get_height() / 2.0f);
}
