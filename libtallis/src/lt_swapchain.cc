#include <stdexcept>
#include <print>
#include <array>
#include <algorithm>
#include <vulkan/vulkan.h>
#include <libtallis/lt_swapchain.hpp>
#include <libtallis/lt_resource.hpp>
#include <libtallis/lt_device.hpp>

namespace lt = libtallis;

lt::swapchain libtallis::create_swapchain(VkPhysicalDevice physdev,
										  VkDevice dev,
										  VkSurfaceKHR surface)
{
	VkSurfaceCapabilities2KHR surface_caps {
		.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR};
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

	lt::swapchain swapchain {.img_count = 3};
	swapchain.extent = surface_caps.surfaceCapabilities.currentExtent;

	if (surface_caps.surfaceCapabilities.currentExtent.width == 0xFFFFFFFF)
	{
		std::print("Wayland detected. Developer, please check swapchain code "
				   "if this does not work :P\n");
		swapchain.extent = {
			.width = surface_caps.surfaceCapabilities.maxImageExtent.width,
			.height = surface_caps.surfaceCapabilities.maxImageExtent.height};
	}

	uint32_t fmt_count {0};
	rv = vkGetPhysicalDeviceSurfaceFormats2KHR(physdev,
											   &surface_info,
											   &fmt_count,
											   nullptr);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't enumerate surface formats");
	}

	std::vector<VkSurfaceFormat2KHR> surface_formats(
		fmt_count,
		VkSurfaceFormat2KHR {.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR});

	rv = vkGetPhysicalDeviceSurfaceFormats2KHR(physdev,
											   &surface_info,
											   &fmt_count,
											   surface_formats.data());

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't get surface formats");
	}

	VkFormat image_format {};
	for (const auto surface_format : surface_formats)
	{
		if (surface_format.surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB)
		{
			image_format = surface_format.surfaceFormat.format;
			break;
		}
	}

	if (!image_format)
	{
		throw std::runtime_error("Couldn't find required image format");
	}

	VkSwapchainCreateInfoKHR swapchain_info {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface,
		.minImageCount = std::clamp(
			swapchain.img_count,
			surface_caps.surfaceCapabilities.minImageCount,
			surface_caps.surfaceCapabilities.maxImageCount),
		.imageFormat = image_format,
		.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		.imageExtent = {.width = swapchain.extent.width,
						.height = swapchain.extent.height},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR};

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

lt::image libtallis::create_depth_image(lt::device& dev,
										lt::swapchain& swapchain)
{
	VkFormat depth_format {VK_FORMAT_UNDEFINED};
	std::array depth_formats {VK_FORMAT_D24_UNORM_S8_UINT,
							  VK_FORMAT_D32_SFLOAT_S8_UINT};

	for (VkFormat& format : depth_formats)
	{
		VkFormatProperties2 format_props {
			.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2};

		vkGetPhysicalDeviceFormatProperties2(dev.physdev,
											 format,
											 &format_props);

		if (format_props.formatProperties.optimalTilingFeatures &
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			depth_format = format;
			break;
		}
	}

	VkImageCreateInfo image_info {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = depth_format,
		.extent = {.width = swapchain.extent.width,
				   .height = swapchain.extent.height,
				   .depth = 1},
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED};

	lt::image depth_image {lt::create_image(image_info, dev.allocator)};

	return depth_image;
}
