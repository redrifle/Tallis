#ifndef LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#define LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#include <string_view>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <libtallis/lt_device.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_swapchain.hpp>
#include <libtallis/lt_model.hpp>
namespace libtallis
{
	struct context
	{
		VkInstance instance;
		libtallis::device dev;
		libtallis::swapchain swapchain;
		std::vector<libtallis::model> model_list;
		void load_models(std::string_view const);
	};
	void run(libtallis::window&);
} /* namespace libtallis */
#endif /* LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde */
