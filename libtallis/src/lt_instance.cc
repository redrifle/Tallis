#include <cstdint>
#include <stdexcept>
#include <libtallis/lt_instance.hpp>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

VkInstance libtallis::create_instance()
{
	const VkApplicationInfo app_info {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Tallis",
		.apiVersion = VK_API_VERSION_1_3};

	std::uint32_t ext_count {0};
	char const* const* const exts {
		glfwGetRequiredInstanceExtensions(&ext_count)};

	const VkInstanceCreateInfo inst_info {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
		.enabledExtensionCount = ext_count,
		.ppEnabledExtensionNames = exts};

	VkInstance instance {nullptr};
	VkResult rv = vkCreateInstance(&inst_info, nullptr, &instance);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create vulkan instance.");
	}

	return instance;
}
