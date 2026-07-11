#include <print>
#include <GLFW/glfw3.h>
#include <libtallis/lt_input.hpp>
#include <libtallis/lt_window.hpp>

namespace lt = libtallis;

void key_callback(GLFWwindow* wp, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wp, GLFW_TRUE);
	}

	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
	{
		lt::window* window {(lt::window*)glfwGetWindowUserPointer(wp)};
		lt::toggle_cursor(window);
	}
}

void window_close_callback(GLFWwindow* wp)
{
	std::print("Window close callback triggered\n");
	glfwSetWindowShouldClose(wp, GL_TRUE);
}

void error_callback(int code, const char* description)
{
	std::print("GLFW error #{}: {}\n", code, description);
}
