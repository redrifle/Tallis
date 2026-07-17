#ifndef LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#define LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#include <vulkan/vulkan.h>
#include <libtallis/lt_device.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_swapchain.hpp>
namespace libtallis
{
	struct context
	{
		VkInstance instance;
		libtallis::device dev;
		libtallis::swapchain swapchain;
	};
	void run(libtallis::window&);
} /* namespace libtallis */
#endif /* LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde */
