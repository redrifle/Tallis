#ifndef LT_RESOURCE_HPP_019f53b9_2c0d_7486_881c_a04fbc6bfd6c
#define LT_RESOURCE_HPP_019f53b9_2c0d_7486_881c_a04fbc6bfd6c
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
namespace libtallis
{
	struct image
	{
		VkImage vkimage;
		VmaAllocation memory;
		VkFormat format;
		VkImageView view;
		void create_view(VkDevice, VkImageViewCreateInfo&);
	};
	libtallis::image create_image(VkImageCreateInfo&, VmaAllocator, float);
	VkBuffer create_buffer();
}; /* namespace libtallis */
#endif /* LT_RESOURCE_HPP_019f53b9_2c0d_7486_881c_a04fbc6bfd6c */
