#include <string>
#include <string_view>
#include <ranges>
#include <print>
#include <stdexcept>
#include <filesystem>
#include <GLFW/glfw3.h>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_util.hpp>
#include <libtallis/lt_cleanup.hpp>

namespace fs = std::filesystem;
namespace vs = std::views;
namespace rg = std::ranges;
namespace lt = libtallis;

void libtallis::run(lt::window& win)
{
	lt::context context {lt::init(win)};

	while (!win.should_close())
	{
		glfwWaitEvents();
	}

	lt::cleanup(context, win);
}

void libtallis::context::load_models(std::string_view const dir)
{
	auto const dirs = rg::subrange(fs::recursive_directory_iterator(dir));
	auto const paths {dirs | vs::filter(is_obj) | vs::transform(path_str) |
					  rg::to<std::vector>()};

	if (paths.empty())
	{
		throw std::runtime_error("No models found");
	}

	model_list.reserve(model_list.capacity() + paths.size());
	for (auto const& path : paths)
	{
		model_list.emplace_back().load_obj(path);
	}
}
