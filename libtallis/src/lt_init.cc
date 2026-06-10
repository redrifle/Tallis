#include <vulkan/vulkan.h>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_instance.hpp>

lt_data lt_init()
{
    lt_data data {.instance = lt_instance()};
    return data;
}
