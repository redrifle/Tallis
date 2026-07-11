#include <print>
#include <vulkan/vulkan.h>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_device.hpp>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_instance.hpp>
#include <libtallis/lt_mem.hpp>
#include <libtallis/lt_surface.hpp>
#include <libtallis/lt_swapchain.hpp>

namespace lt = libtallis;

lt::context libtallis::init(lt::window& window)
{
	lt::context context {};
	context.instance = lt::create_instance();
	context.physdev = lt::create_physical_device(context.instance);
	context.dev = lt::create_device(context.instance, context.physdev);
	context.dev.allocator = lt::vma_init(context.instance,
										 context.physdev,
										 context.dev.vkdev);
	window.surface = lt::create_surface(context.instance,
										context.dev.vkdev,
										window.win);
	context.swapchain = lt::create_swapchain(context.physdev,
											 context.dev.vkdev,
											 window.surface);

	std::print("VkDevice: {}\nQueue family index: {}\nQueue: {}\n",
			   (void*)context.dev.vkdev,
			   context.dev.q_family_index,
			   (void*)context.dev.queue);
	std::print("swapchain image count: {}\n", context.swapchain.images.size());

	return context;
}
