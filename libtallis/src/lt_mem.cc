#include <stdexcept>
#include <libtallis/lt_mem.hpp>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

VmaAllocator libtallis::vma_init(VkInstance instance,
								 VkPhysicalDevice physdev,
								 VkDevice dev)
{
	VmaVulkanFunctions vma_vk_funcs {
		.vkGetInstanceProcAddr = vkGetInstanceProcAddr,
		.vkGetDeviceProcAddr = vkGetDeviceProcAddr};

	VmaAllocatorCreateInfo vma_alloc_info {
		.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
		.physicalDevice = physdev,
		.device = dev,
		.pVulkanFunctions = &vma_vk_funcs,
		.instance = instance};

	VmaAllocator allocator {};
	VkResult rv {vmaCreateAllocator(&vma_alloc_info, &allocator)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create VMA allocator");
	}

	return allocator;
}
