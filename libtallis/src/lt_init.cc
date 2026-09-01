#include <print>
#include <vulkan/vulkan.h>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_device.hpp>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_instance.hpp>
#include <libtallis/lt_surface.hpp>
#include <libtallis/lt_swapchain.hpp>
#include <config.h>

namespace lt = libtallis;

auto lt::init(lt::window& window) -> context
{
	lt::context context;
	context.instance = lt::create_instance();
	std::vector<VkPhysicalDevice> devices {get_device_list(context.instance)};
	const unsigned int device_index {get_best_device_index(devices)};
	context.dev.create(context.instance, devices[device_index]);
	window.create_surface(context.instance);
	context.swapchain.create_swapchain(context.dev, window.surface);
	context.load_models(ASSET_PATH);

	std::print("VkDevice : {}\nQueue family index : {}\nQueue : {}\nswapchain "
			   "image count : {}\n",
			   (void*)context.dev.vkdev,
			   context.dev.q_family_index,
			   (void*)context.dev.queue,
			   context.swapchain.images.size());

	return context;
}
