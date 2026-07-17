#include <stdexcept>
#include <vulkan/vulkan.h>
#include <libtallis/lt_resource.hpp>
#include <libtallis/lt_swapchain.hpp>
#include <vk_mem_alloc.h>

namespace lt = libtallis;

lt::image libtallis::create_image(VkImageCreateInfo& image_info,
								  VmaAllocator alloc)
{
	lt::image image {};
	VmaAllocationCreateInfo alloc_info {
		VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
		VMA_MEMORY_USAGE_AUTO};

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
