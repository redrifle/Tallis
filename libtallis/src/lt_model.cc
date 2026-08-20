#include <string>
#include <stdexcept>
#include <tinyobjloader/tiny_obj_loader.h>
#include <libtallis/lt_model.hpp>

void libtallis::model::load(std::string const path)
{
	auto rv {tinyobj::LoadObj(&mesh.attrib,
							  &mesh.shapes,
							  &mesh.mats,
							  nullptr,
							  nullptr,
							  path.c_str())};

	if (not rv)
	{
		throw std::runtime_error("Couldn't load obj file");
	}
}
