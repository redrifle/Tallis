#include <GLFW/glfw3.h>
#include <libtallis/lt_input.hpp>
#include <libtallis/lt_window.hpp>

void key_callback(GLFWwindow* wp, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wp, GLFW_TRUE);
	}

	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
	{
		lt_window* window {(lt_window*)glfwGetWindowUserPointer(wp)};
		lt_toggle_cursor(window);
	}
}
