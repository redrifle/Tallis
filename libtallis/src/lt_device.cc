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

VkPhysicalDevice libtallis::device::create_physical_device(VkInstance instance)
{
	std::uint32_t dev_count {0};
	int rv {vkEnumeratePhysicalDevices(instance, &dev_count, nullptr)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't enumerate devices");
	}

	if (dev_count == 0)
	{
		throw std::runtime_error("No physical devices found");
	}

	std::vector<VkPhysicalDevice> devs(dev_count);
	rv = vkEnumeratePhysicalDevices(instance, &dev_count, devs.data());

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't obtain device list");
	}

	device::props.sType = {VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
	VkPhysicalDeviceProperties2 props_tmp {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
	std::uint32_t dev_index {0};
	if (dev_count == 1)
	{
		vkGetPhysicalDeviceProperties2(devs[dev_index], &props_tmp);
	}
	else if (dev_count > 1)
	{
		std::vector<double> scores(dev_count);
		for (std::uint32_t i {0}; i < dev_count; ++i)
		{
			vkGetPhysicalDeviceProperties2(devs[i], &props);
			/* NOTE: Don't chain these additions
			lest unsigned integer overflow be your end. */
			scores[i] += props_tmp.properties.limits.maxPushConstantsSize;
			scores[i] += props_tmp.properties.limits.maxMemoryAllocationCount;
			scores[i] += props_tmp.properties.limits.maxImageDimension2D;
			scores[i] += props_tmp.properties.limits.maxSamplerAnisotropy;
		}
		auto scores_it {std::max_element(scores.begin(), scores.end())};
		dev_index = std::distance(scores.begin(), scores_it);
	}
	VkPhysicalDevice physdev {devs[dev_index]};
	vkGetPhysicalDeviceProperties2(physdev, &(device::props));
	std::print("Using device #{} : {}\nVendor ID: 0x{:X}\n",
			   dev_index,
			   device::props.properties.deviceName,
			   props.properties.vendorID);

	return physdev;
}

uint32_t libtallis::get_queue_family(VkInstance instance,
									 VkPhysicalDevice physdev)
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
			std::print("Found queue family with graphics on #{}\n", i);
			return i;
		}
	}

	throw std::runtime_error("No queue family with graphics support");
	return 0;
}

VkDevice libtallis::create_device(VkInstance instance, lt::device& device)
{
	device.q_family_index = get_queue_family(instance, device.physdev);
	int rv = glfwGetPhysicalDevicePresentationSupport(instance,
													  device.physdev,
													  device.q_family_index);

	if (rv != GLFW_TRUE)
	{
		throw std::runtime_error("Device doesn't support presentation");
	}

	const float qp {1.0f};
	VkDeviceQueueCreateInfo queue_info {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = device.q_family_index,
		.queueCount = 1,
		.pQueuePriorities = &qp};

	const std::array dev_extensions {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME,
		VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME};

	lt::device_features supported_features {};
	supported_features.mem_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
	supported_features.vk_12_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	supported_features.vk_13_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	supported_features.vk_13_features.pNext = &supported_features
												   .vk_12_features;

	VkPhysicalDeviceFeatures2 device_features {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = &supported_features.vk_13_features,
		.features = supported_features.vk_10_features};

	vkGetPhysicalDeviceFeatures2(device.physdev, &device_features);
	device.features.enable_features(supported_features);

	VkDeviceCreateInfo device_info {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &device_features,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledExtensionCount = static_cast<uint32_t>(dev_extensions.size()),
		.ppEnabledExtensionNames = dev_extensions.data(),
		.pEnabledFeatures = nullptr};

	VkDevice vkdev {};
	rv = vkCreateDevice(device.physdev, &device_info, nullptr, &vkdev);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create logical device");
	}

	vkGetDeviceQueue(vkdev, device.q_family_index, 0, &device.queue);
	return vkdev;
}

libtallis::device_features::device_features() :
	vk_10_features({}),
	vk_11_features({}),
	vk_12_features({}),
	vk_13_features({}),
	vk_14_features({}),
	mem_features({})
{
	mem_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
	vk_12_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	vk_13_features.sType =
		VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	vk_12_features.pNext = &mem_features;
	vk_13_features.pNext = &vk_12_features;
}

void libtallis::device_features::enable_features(
	lt::device_features& supported_features)
{
	mem_features.pageableDeviceLocalMemory = supported_features.mem_features
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
