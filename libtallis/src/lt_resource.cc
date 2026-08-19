#include <stdexcept>
#include <vulkan/vulkan.h>
#include <libtallis/lt_resource.hpp>
#include <libtallis/lt_swapchain.hpp>
#include <vk_mem_alloc.h>

namespace lt = libtallis;

lt::image libtallis::create_image(VkImageCreateInfo& image_info,
								  VmaAllocator alloc,
								  float priority)
{
	lt::image image {.format = image_info.format};
	VmaAllocationCreateInfo alloc_info {
		.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
		.usage = VMA_MEMORY_USAGE_AUTO,
		.priority = priority};

	VkResult rv {vmaCreateImage(alloc,
								&image_info,
								&alloc_info,
								&image.vkimage,
								&image.memory,
								nullptr)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create image");
	}

	return image;
}

VkBuffer libtallis::create_buffer()
{
	return nullptr;
}
