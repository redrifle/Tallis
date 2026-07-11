#ifndef LT_SURFACE_HPP_019f4db0_6468_7732_960f_9a957220c0f9
#define LT_SURFACE_HPP_019f4db0_6468_7732_960f_9a957220c0f9
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
namespace libtallis
{
	VkSurfaceKHR create_surface(VkInstance, VkDevice, GLFWwindow*);
} /* namespace libtallis */
#endif /* LT_SURFACE_HPP_019f4db0_6468_7732_960f_9a957220c0f9 */
