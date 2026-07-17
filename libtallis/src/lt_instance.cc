#include <print>
#include <vector>
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
	const char** glfw_exts {glfwGetRequiredInstanceExtensions(&ext_count)};

	if (!glfw_exts)
	{
		throw std::runtime_error("Couldn't get required glfw extensions");
	}

	std::array exts {VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME};
	std::vector<const char*> instance_extensions;
	instance_extensions.reserve(ext_count + exts.size());
	instance_extensions.insert(instance_extensions.end(),
							   glfw_exts,
							   glfw_exts + ext_count);
	instance_extensions.insert(instance_extensions.end(),
							   exts.begin(),
							   exts.end());

	const VkInstanceCreateInfo inst_info {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
		.enabledExtensionCount = static_cast<uint32_t>(
			instance_extensions.size()),
		.ppEnabledExtensionNames = instance_extensions.data()};

	VkInstance instance {nullptr};
	VkResult rv = vkCreateInstance(&inst_info, nullptr, &instance);

	if (rv != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create vulkan instance.");
	}

	return instance;
}
