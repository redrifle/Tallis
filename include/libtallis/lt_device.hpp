#ifndef LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#define LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#include <vector>
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
namespace libtallis
{
	struct device_features
	{
		VkPhysicalDeviceFeatures vk_10_features;
		VkPhysicalDeviceVulkan11Features vk_11_features;
		VkPhysicalDeviceVulkan12Features vk_12_features;
		VkPhysicalDeviceVulkan13Features vk_13_features;
		VkPhysicalDeviceVulkan14Features vk_14_features;
		VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT mem_features;
		device_features();
		void enable_features(device_features&);
	};
	struct device
	{
		VkPhysicalDevice physdev;
		VkDevice vkdev;
		uint32_t q_family_index;
		VkQueue queue;
		VkPhysicalDeviceProperties2 props;
		VmaAllocator allocator;
		struct device_features features;
		std::vector<const char*> extensions;
		VkPhysicalDevice create_physical_device(VkInstance);
	};
	uint32_t get_queue_family(VkInstance, VkPhysicalDevice);
	VkDevice create_device(VkInstance, device&);
} /* namespace libtallis */
#endif /* LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95 */
