#ifndef LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#define LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde
#include <vulkan/vulkan.h>
#include <libtallis/lt_window.hpp>
struct lt_data
{
    VkInstance instance {nullptr};
    VkPhysicalDevice physdev {nullptr};
};

int lt_run(lt_window&);
#endif /* LT_ENGINE_HPP_019e4c9c_059a_7b83_8218_e2c964985fde */
