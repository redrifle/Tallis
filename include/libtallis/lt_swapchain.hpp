#ifndef LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae
#define LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae
#include <vector>
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <libtallis/lt_resource.hpp>
#include <libtallis/lt_device.hpp>
namespace libtallis
{
	struct swapchain
	{
		uint32_t img_count;
		VkSwapchainKHR vkswapchain;
		VkExtent2D extent;
		std::vector<VkImage> images;
		void create_swapchain(libtallis::device&, VkSurfaceKHR);
		libtallis::image depth_image;

	  private:
		libtallis::image create_depth_image(libtallis::device&);
	};
	libtallis::image create_depth_image(libtallis::device&,
										libtallis::swapchain&);
} /* namespace libtallis */
#endif /* LT_SWAPCHAIN_HPP_019e824d_d0d3_7e7c_9a95_f95c1831a8ae */
