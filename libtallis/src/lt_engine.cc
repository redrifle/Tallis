#include <string>
#include <print>
#include <stdexcept>
#include <filesystem>
#include <GLFW/glfw3.h>
#include <libtallis/lt_engine.hpp>
#include <libtallis/lt_init.hpp>
#include <libtallis/lt_window.hpp>
#include <libtallis/lt_cleanup.hpp>

namespace fs = std::filesystem;
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

void libtallis::context::load_models(std::string const dir)
{
	auto current_dir {fs::recursive_directory_iterator(dir)};

	std::vector<std::string> paths;
	for (const auto& file : current_dir)
	{
		if (!file.is_directory())
		{
			static int model_index {0};
			std::string extension {file.path().extension().string()};
			if (extension == ".obj")
			{
				paths.emplace_back(file.path().string());
			}
		}
	}

	if (paths.empty())
	{
		throw std::runtime_error("No models found");
	}

	model_list.resize(paths.size());
	for (auto i {0}; i < paths.size(); ++i)
	{
		std::println("{}", paths[i]);
		model_list[i].load(paths[i]);
	}
}
