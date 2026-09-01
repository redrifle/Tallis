#include <stdexcept>
#include <vulkan/vulkan.h>
#include <libtallis/lt_resource.hpp>
#include <libtallis/lt_swapchain.hpp>
#include <vk_mem_alloc.h>

namespace lt = libtallis;

libtallis::image::image() :
	vkimage(nullptr),
	memory(nullptr),
	format(),
	view(nullptr)
{
}

libtallis::image::image(VkImageCreateInfo const& image_info,
						VmaAllocator const alloc,
						float const priority)
{
	format = image_info.format;
	VmaAllocationCreateInfo alloc_info {
		.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
		.usage = VMA_MEMORY_USAGE_AUTO,
		.priority = priority};

	VkResult rv {vmaCreateImage(alloc,
								&image_info,
								&alloc_info,
								&vkimage,
								&memory,
								nullptr)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create image");
	}
}

void lt::image::create_view(VkDevice const dev,
							VkImageViewCreateInfo const& create_info)
{
	VkResult rv {vkCreateImageView(dev, &create_info, nullptr, &view)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create image view");
	}
}

libtallis::buffer::buffer()
{
}

libtallis::buffer::buffer(VkBufferCreateInfo const& buffer_info)
{
}
