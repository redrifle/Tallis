#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vk_mem_alloc.h>
#include <libtallis/lt_cleanup.hpp>
#include <libtallis/lt_engine.hpp>

namespace lt = libtallis;

void libtallis::cleanup(lt::context& c)
{
	if (c.dev.allocator)
	{
		vmaDestroyAllocator(c.dev.allocator);
	}

	if (c.dev.vkdev)
	{
		vkDestroyDevice(c.dev.vkdev, nullptr);
	}

	if (c.instance)
	{
		vkDestroyInstance(c.instance, nullptr);
	}
}
