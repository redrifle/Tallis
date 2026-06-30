#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <print>
#include <cstdint>
#include <vulkan/vulkan.h>

VkPhysicalDevice lt_physical_device(VkInstance& instance)
{
	std::uint32_t dev_count {0};
	int rv {vkEnumeratePhysicalDevices(instance, &dev_count, nullptr)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't enumerate devices");
		return nullptr;
	}

	std::vector<VkPhysicalDevice> devs(dev_count);
	rv = vkEnumeratePhysicalDevices(instance, &dev_count, devs.data());

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't obtain device list");
		return nullptr;
	}

	VkPhysicalDeviceProperties2 props {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
	std::uint32_t dev_index;
	if (dev_count == 1)
	{
		dev_index = 0;
		vkGetPhysicalDeviceProperties2(devs[dev_index], &props);
	}
	else if (dev_count > 1)
	{
		std::vector<double> scores(dev_count);
		for (std::uint32_t i {0}; i < dev_count; ++i)
		{
			vkGetPhysicalDeviceProperties2(devs[i], &props);
			scores[i] += (props.properties.limits.maxPushConstantsSize +
						  props.properties.limits.maxMemoryAllocationCount +
						  props.properties.limits.maxImageDimension2D +
						  props.properties.limits.maxSamplerAnisotropy) *
						 0.1;
		}
		auto scores_it {std::max_element(scores.begin(), scores.end())};
		dev_index = std::distance(scores.begin(), scores_it);
	}

	std::print("Using device #{} : {}\n",
			   dev_index,
			   props.properties.deviceName);

	return devs[dev_index];
}
