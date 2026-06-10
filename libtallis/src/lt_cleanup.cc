#include <vulkan/vulkan.h>
#include <libtallis/lt_engine.hpp>

int lt_cleanup(lt_data& data)
{
    if (data.instance)
    {
        vkDestroyInstance(data.instance, nullptr);
    }
    return 0;
}
