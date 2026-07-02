#include <stdexcept>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_callback.hpp>

libtallis::window::window(std::string n, unsigned int w, unsigned int h) :
	name(n),
	width(w),
	height(h)
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("glfwInit() returned GLFW_FALSE");
		return;
	}

	win = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
	if (!win)
	{
		throw std::runtime_error("Couldn't create window");
		return;
	}

	glfwSetKeyCallback(win, key_callback);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	glfwSetWindowUserPointer(win, this);
}

bool libtallis::window::should_close()
{
	return glfwWindowShouldClose(win);
}

GLFWwindow* libtallis::window::create_win(const std::string_view name)
{
	if (glfwInit() != GLFW_TRUE)
	{
		return nullptr;
	}

	win = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
	if (!win)
	{
		throw std::runtime_error("Couldn't create window");
		return nullptr;
	}

	return win;
}

libtallis::window::~window()
{
	glfwDestroyWindow(win);
}
