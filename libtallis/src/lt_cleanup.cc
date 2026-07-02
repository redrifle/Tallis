#include <vulkan/vulkan.h>
#include <libtallis/lt_cleanup.hpp>
#include <libtallis/lt_engine.hpp>

namespace lt = libtallis;

int libtallis::cleanup(lt::context& c)
{
	if (c.instance)
	{
		vkDestroyInstance(c.instance, nullptr);
	}
	return 0;
}
