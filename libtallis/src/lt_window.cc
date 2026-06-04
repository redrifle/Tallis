#include <stdexcept>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_callback.hpp>

lt_window::lt_window(const char* n, unsigned int w, unsigned int h) :
	name(n),
	width(w),
	height(h),
	win(lt_create_win(name, width, height))
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	glfwSetWindowUserPointer(win, this);
}

bool lt_window::should_close()
{
	return glfwWindowShouldClose(win);
}

GLFWwindow* lt_window::lt_create_win(const char* name,
									 unsigned int width,
									 unsigned int height)
{
	if (glfwInit() != GLFW_TRUE)
	{
		return nullptr;
	}

	win = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (!win)
	{
		throw std::runtime_error("Couldn't create window");
		return nullptr;
	}

	return win;
}

unsigned int lt_window::get_width()
{
	return width;
}

unsigned int lt_window::get_height()
{
	return height;
}

GLFWwindow* lt_window::get_pointer()
{
	return win;
}

lt_window::~lt_window()
{
	glfwDestroyWindow(win);
}
