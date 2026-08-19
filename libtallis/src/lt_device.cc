#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <print>
#include <ranges>
#include <cstdint>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <libtallis/lt_device.hpp>

namespace lt = libtallis;

libtallis::device::device() :
	device_index(0),
	physdev(nullptr),
	vkdev(nullptr),
	q_family_index(0),
	queue(nullptr),
	props({}),
	allocator(nullptr),
	features({}),
	extensions({})
{
}

libtallis::device::device(VkInstance instance, VkPhysicalDevice dev) : device()
{
	physdev = dev;
	props.sType = {VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
	vkGetPhysicalDeviceProperties2(physdev, &props);
	q_family_index = select_queue_family(instance);
	vkdev = create_logical_device(instance);
	allocator = create_allocator(instance);

	std::print("Using device : {}\nVendor ID : 0x{:X}\n",
			   props.properties.deviceName,
			   props.properties.vendorID);
}

uint32_t libtallis::device::select_queue_family(VkInstance instance)
{
	uint32_t queue_fam_count {0};
	vkGetPhysicalDeviceQueueFamilyProperties(physdev,
											 &queue_fam_count,
											 nullptr);

	if (queue_fam_count == 0)
	{
		throw std::runtime_error("Could not enumerate queue families");
	}

	std::vector<VkQueueFamilyProperties> queue_fams(queue_fam_count);
	vkGetPhysicalDeviceQueueFamilyProperties(physdev,
											 &queue_fam_count,
											 queue_fams.data());

	if (queue_fams.empty())
	{
		throw std::runtime_error("Could not get list of queue families");
	}

	for (const auto [i, queue_fam] : std::views::enumerate(queue_fams))
	{
		if (queue_fam.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			return i;
		}
	}

	throw std::runtime_error("No queue family with graphics support");
	return 0;
}

VkDevice lt::device::create_logical_device(VkInstance instance)
{
	int rv = glfwGetPhysicalDevicePresentationSupport(instance,
													  physdev,
													  q_family_index);

	if (rv != GLFW_TRUE)
	{
		throw std::runtime_error("Device doesn't support presentation");
	}

	const float qp {1.0f};
	VkDeviceQueueCreateInfo queue_info {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = q_family_index,
		.queueCount = 1,
		.pQueuePriorities = &qp};

	const std::array dev_extensions {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME,
		VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME};

	/* We do not want to indiscriminately enable every feature on the device,
	for performance reasons. Therefore, we get the supported features first
	using a local struct, then set the features we want explicitly in our
	actual device struct */
	lt::device_features supported_features {};
	VkPhysicalDeviceFeatures2 supported_features_2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = &supported_features.vk_14_features,
		.features = supported_features.vk_10_features};

	vkGetPhysicalDeviceFeatures2(physdev, &supported_features_2);
	features.enable_features(supported_features);
	supported_features_2.pNext = &features.vk_14_features;
	supported_features_2.features = features.vk_10_features;

	VkDeviceCreateInfo device_info {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &supported_features_2,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledExtensionCount = static_cast<uint32_t>(dev_extensions.size()),
		.ppEnabledExtensionNames = dev_extensions.data(),
		.pEnabledFeatures = nullptr};

	VkDevice vkdev {};
	rv = vkCreateDevice(physdev, &device_info, nullptr, &vkdev);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create logical device");
	}

	vkGetDeviceQueue(vkdev, q_family_index, 0, &queue);
	return vkdev;
}

libtallis::device_features::device_features() :
	vk_10_features({}),
	vk_11_features({}),
	vk_12_features({}),
	vk_13_features({}),
	vk_14_features({}),
	dev_local_mem({})
{
	dev_local_mem.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
	mem_priority.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
	vk_12_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	vk_13_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	vk_14_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
	dev_local_mem.pNext = &mem_priority;
	vk_12_features.pNext = &dev_local_mem;
	vk_13_features.pNext = &vk_12_features;
	vk_14_features.pNext = &vk_13_features;
}

void libtallis::device_features::enable_features(
	lt::device_features& supported_features)
{
	dev_local_mem.pageableDeviceLocalMemory = supported_features.dev_local_mem
												  .pageableDeviceLocalMemory;
	vk_10_features.samplerAnisotropy = supported_features.vk_10_features
										   .samplerAnisotropy;
	vk_12_features.descriptorIndexing = supported_features.vk_12_features
											.descriptorIndexing;
	vk_12_features.shaderSampledImageArrayNonUniformIndexing =
		supported_features.vk_12_features
			.shaderSampledImageArrayNonUniformIndexing;
	vk_12_features.descriptorBindingVariableDescriptorCount =
		supported_features.vk_12_features
			.descriptorBindingVariableDescriptorCount;
	vk_12_features.runtimeDescriptorArray = supported_features.vk_12_features
												.runtimeDescriptorArray;
	vk_12_features.bufferDeviceAddress = supported_features.vk_12_features
											 .bufferDeviceAddress;
	vk_13_features.synchronization2 = supported_features.vk_13_features
										  .synchronization2;
	vk_13_features.dynamicRendering = supported_features.vk_13_features
										  .dynamicRendering;
}

std::vector<VkPhysicalDevice> lt::get_device_list(VkInstance inst)
{
	std::uint32_t dev_count {0};
	int rv {vkEnumeratePhysicalDevices(inst, &dev_count, nullptr)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't enumerate devices");
	}

	if (dev_count == 0)
	{
		throw std::runtime_error("No physical devices found");
	}

	std::vector<VkPhysicalDevice> devs(dev_count);
	rv = vkEnumeratePhysicalDevices(inst, &dev_count, devs.data());

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't obtain device list");
	}

	return devs;
}

unsigned int libtallis::get_best_device_index(
	std::vector<VkPhysicalDevice>& devs)
{
	VkPhysicalDeviceProperties2 props {
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};

	std::uint32_t dev_index {0};
	if (devs.size() == 1)
	{
		vkGetPhysicalDeviceProperties2(devs[dev_index], &props);
	}
	else if (devs.size() > 1)
	{
		std::vector<double> scores(devs.size());
		for (std::uint32_t i {0}; i < devs.size(); ++i)
		{
			props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
			vkGetPhysicalDeviceProperties2(devs[i], &props);
			/* NOTE: Don't chain these additions
			lest unsigned integer overflow be your end. */
			scores[i] += props.properties.limits.maxPushConstantsSize;
			scores[i] += props.properties.limits.maxMemoryAllocationCount;
			scores[i] += props.properties.limits.maxImageDimension2D;
			scores[i] += props.properties.limits.maxSamplerAnisotropy;
		}
		auto scores_it {std::max_element(scores.begin(), scores.end())};
		dev_index = std::distance(scores.begin(), scores_it);
	}
	return dev_index;
}

VmaAllocator lt::device::create_allocator(VkInstance instance)
{
	VmaVulkanFunctions vma_vk_funcs {
		.vkGetInstanceProcAddr = vkGetInstanceProcAddr,
		.vkGetDeviceProcAddr = vkGetDeviceProcAddr};

	VmaAllocatorCreateInfo vma_alloc_info {
		.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT |
				 VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT,
		.physicalDevice = physdev,
		.device = vkdev,
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
