#include <vulkan/vulkan.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <libtallis/lt_surface.hpp>

VkSurfaceKHR libtallis::create_surface(VkInstance instance,
									   VkDevice dev,
									   GLFWwindow* wp)
{
	VkSurfaceKHR surface {};
	VkResult rv {glfwCreateWindowSurface(instance, wp, nullptr, &surface)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create window surface");
	}
    
	return surface;
}
