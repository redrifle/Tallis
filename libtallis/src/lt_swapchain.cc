#include <stdexcept>
#include <print>
#include <vulkan/vulkan.h>
#include <libtallis/lt_swapchain.hpp>

namespace lt = libtallis;

lt::swapchain libtallis::create_swapchain(VkPhysicalDevice physdev,
										  VkDevice dev,
										  VkSurfaceKHR surface)
{
	VkSurfaceCapabilities2KHR surface_caps {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR};
	VkPhysicalDeviceSurfaceInfo2KHR surface_info {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR,
		.surface = surface};

	VkResult rv {vkGetPhysicalDeviceSurfaceCapabilities2KHR(physdev,
															&surface_info,
															&surface_caps)};

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't get surface capabilities");
	}

	VkExtent2D swap_extent {surface_caps.surfaceCapabilities.currentExtent};

	if (surface_caps.surfaceCapabilities.currentExtent.width == 0xFFFFFFFF)
	{
		std::print("Wayland detected. Developer, please check swapchain code "
				   "if this does not work :P\n");
		swap_extent = {
			.width = surface_caps.surfaceCapabilities.maxImageExtent.width,
			.height = surface_caps.surfaceCapabilities.maxImageExtent.height};
	}

	const VkFormat image_format {VK_FORMAT_B8G8R8A8_SRGB};
	VkSwapchainCreateInfoKHR swapchain_info {
		.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface,
		.minImageCount = surface_caps.surfaceCapabilities.minImageCount,
		.imageFormat = image_format,
		.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		.imageExtent = {.width = swap_extent.width,
						.height = swap_extent.height},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR};

	lt::swapchain swapchain;
	rv = vkCreateSwapchainKHR(dev,
							  &swapchain_info,
							  nullptr,
							  &swapchain.vkswapchain);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create swapchain");
	}

	uint32_t image_count {0};
	rv = vkGetSwapchainImagesKHR(dev,
								 swapchain.vkswapchain,
								 &image_count,
								 nullptr);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't get swapchain image count");
	}

	swapchain.images.resize(image_count);
	rv = vkGetSwapchainImagesKHR(dev,
								 swapchain.vkswapchain,
								 &image_count,
								 swapchain.images.data());

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't get swapchain images");
	}

	return swapchain;
}
