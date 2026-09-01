#include <string>
#include <filesystem>

bool is_obj(std::filesystem::directory_entry const& e)
{
	return e.is_regular_file() && e.path().extension() == ".obj";
}

std::string path_str(std::filesystem::directory_entry const& e)
{
	return e.path().string();
}
