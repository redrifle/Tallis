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

VkPhysicalDevice libtallis::create_physical_device(VkInstance instance)
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

	VkPhysicalDeviceProperties2 props {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
	std::uint32_t dev_index {0};
	if (dev_count == 1)
	{
		vkGetPhysicalDeviceProperties2(devs[dev_index], &props);
	}
	else if (dev_count > 1)
	{
		std::vector<double> scores(dev_count);
		for (std::uint32_t i {0}; i < dev_count; ++i)
		{
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
	VkPhysicalDevice physdev {devs[dev_index]};

	std::print("Using device #{} : {}\n",
			   dev_index,
			   props.properties.deviceName);

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

lt::device libtallis::create_device(VkInstance instance,
									VkPhysicalDevice physdev)
{
	lt::device device {};

	device.q_family_index = get_queue_family(instance, physdev);
	int rv = glfwGetPhysicalDevicePresentationSupport(instance,
													  physdev,
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

	const std::array dev_extensions {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	VkPhysicalDeviceVulkan12Features vk_12_features {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
		.descriptorIndexing = true,
		.shaderSampledImageArrayNonUniformIndexing = true,
		.descriptorBindingVariableDescriptorCount = true,
		.runtimeDescriptorArray = true,
		.bufferDeviceAddress = true};
	VkPhysicalDeviceVulkan13Features vk_13_features {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
		.pNext = &vk_12_features,
		.synchronization2 = true,
		.dynamicRendering = true,
	};
	VkPhysicalDeviceFeatures device_features {.samplerAnisotropy = VK_TRUE};

	VkDeviceCreateInfo device_info {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &vk_13_features,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledExtensionCount = static_cast<uint32_t>(dev_extensions.size()),
		.ppEnabledExtensionNames = dev_extensions.data(),
		.pEnabledFeatures = &device_features};

	rv = vkCreateDevice(physdev, &device_info, nullptr, &device.vkdev);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create logical device");
	}

	vkGetDeviceQueue(device.vkdev, device.q_family_index, 0, &device.queue);
	return device;
}
