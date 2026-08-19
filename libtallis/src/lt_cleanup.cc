#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vk_mem_alloc.h>
#include <libtallis/lt_cleanup.hpp>
#include <libtallis/lt_engine.hpp>

namespace lt = libtallis;

void libtallis::cleanup(lt::context& c, lt::window& win)
{
	if (c.swapchain.depth_image.view)
	{
		vkDestroyImageView(c.dev.vkdev, c.swapchain.depth_image.view, nullptr);
	}

	if (c.swapchain.depth_image.vkimage)
	{
		vmaDestroyImage(c.dev.allocator,
						c.swapchain.depth_image.vkimage,
						c.swapchain.depth_image.memory);
	}

	if (c.swapchain.vkswapchain)
	{
		vkDestroySwapchainKHR(c.dev.vkdev, c.swapchain.vkswapchain, nullptr);
	}

	if (win.surface)
	{
		vkDestroySurfaceKHR(c.instance, win.surface, nullptr);
	}

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
