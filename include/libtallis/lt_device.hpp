#ifndef LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#define LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95
#include <vector>
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
namespace libtallis
{
	struct device_features
	{
		VkPhysicalDeviceFeatures vk_10_features {};
		VkPhysicalDeviceVulkan11Features vk_11_features {};
		VkPhysicalDeviceVulkan12Features vk_12_features {};
		VkPhysicalDeviceVulkan13Features vk_13_features {};
		VkPhysicalDeviceVulkan14Features vk_14_features {};
		VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT dev_local_mem {};
		VkPhysicalDeviceMemoryPriorityFeaturesEXT mem_priority {};
		device_features();
		void enable_features(device_features&);
	};
	struct device
	{
		unsigned int device_index;
		VkPhysicalDevice physdev;
		uint32_t q_family_index;
		VkQueue queue;
		VkDevice vkdev;
		VkPhysicalDeviceProperties2 props;
		VmaAllocator allocator;
		struct device_features features;
		std::vector<const char*> extensions;
		device();
		device(VkInstance, VkPhysicalDevice);
		VkDevice create_logical_device(VkInstance);
		uint32_t select_queue_family(VkInstance);
		VmaAllocator create_allocator(VkInstance);
		void create(VkInstance, VkPhysicalDevice);
	};
	std::vector<VkPhysicalDevice> get_device_list(VkInstance);
	unsigned int get_best_device_index(std::vector<VkPhysicalDevice>&);
} /* namespace libtallis */
#endif /* LT_DEVICE_HPP_019e8124_ddc9_7c7d_a047_cffc6f33fa95 */
