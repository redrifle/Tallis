#include <algorithm>
#include <climits>
#include <stdexcept>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_callback.hpp>

libtallis::window::window(std::string n, unsigned int w, unsigned int h) :
	name(n),
	width(w),
	height(h)
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("glfwInit() failed");
	}

	glfw_initialized = true;
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	/* GLFW Takes int values, but asserts width and height must not be
	negative. To avoid this situation entirely, we take unsigned
	and clamp the values to INT_MAX */
	win = glfwCreateWindow(
		std::clamp(width, (unsigned int)0, (unsigned int)INT_MAX),
		std::clamp(height, (unsigned int)0, (unsigned int)INT_MAX),
		name.data(),
		nullptr,
		nullptr);

	if (!win)
	{
		throw std::runtime_error("Couldn't create window");
	}

	glfwSetKeyCallback(win, key_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	glfwSetWindowUserPointer(win, this);

	++num_windows;
}

bool libtallis::window::should_close()
{
	return glfwWindowShouldClose(win);
}

libtallis::window::~window()
{
	glfwDestroyWindow(win);

	if (num_windows == 1 && glfw_initialized)
	{
		glfwTerminate();
	}

	--num_windows;
}
