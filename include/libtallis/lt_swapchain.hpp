#ifndef LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae
#define LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae
#include <vector>
#include <vulkan/vulkan.h>
namespace libtallis
{
	struct swapchain
	{
		VkSwapchainKHR vkswapchain;
		std::vector<VkImage> images;
	};
	libtallis::swapchain create_swapchain(VkPhysicalDevice,
										  VkDevice,
										  VkSurfaceKHR);
} /* namespace libtallis */
#endif /* LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae */
