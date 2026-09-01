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
		image();
		image(VkImageCreateInfo const&, VmaAllocator const, float const);
		void create_view(VkDevice const, VkImageViewCreateInfo const&);
	};
	struct buffer
	{
		buffer();
		buffer(VkBufferCreateInfo const&);
	};
}; /* namespace libtallis */
#endif /* LT_RESOURCE_HPP_019f53b9_2c0d_7486_881c_a04fbc6bfd6c */
