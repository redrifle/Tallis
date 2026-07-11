#ifndef LT_MEM_HPP_019f4d8c_8013_734e_a767_65037d5a5233
#define LT_MEM_HPP_019f4d8c_8013_734e_a767_65037d5a5233
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
namespace libtallis
{
	VmaAllocator vma_init(VkInstance, VkPhysicalDevice, VkDevice);
} /* namespace libtallis */
#endif /* LT_MEM_HPP_019f4d8c_8013_734e_a767_65037d5a5233 */
