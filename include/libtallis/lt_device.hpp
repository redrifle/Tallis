#ifndef LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#define LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
namespace libtallis
{
	struct device
	{
		VkDevice vkdev;
		uint32_t q_family_index;
		VkQueue queue;
		VmaAllocator allocator;
	};
	VkPhysicalDevice create_physical_device(VkInstance);
	uint32_t get_queue_family(VkInstance, VkPhysicalDevice);
	libtallis::device create_device(VkInstance, VkPhysicalDevice);
} /* namespace libtallis */
#endif /* LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95 */
