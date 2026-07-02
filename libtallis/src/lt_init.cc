#include <print>
#include <vulkan/vulkan.h>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_device.hpp>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_instance.hpp>

namespace lt = libtallis;

lt::context libtallis::init()
{
	lt::context context {
		.instance = lt::create_instance(),
		.physdev = lt::create_physical_device(context.instance),
		.dev = lt::create_device(context.instance, context.physdev)};

	std::print("VkDevice: {}\nQueue family index: {}\nQueue: {}\n",
			   (void*)context.dev.vkdev,
			   context.dev.q_family_index,
			   (void*)context.dev.queue);

	return context;
}
