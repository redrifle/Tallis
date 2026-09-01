#ifndef LT_MODEL_HPP_01a01d7b_4456_784e_9b3f_4acf61df380c
#define LT_MODEL_HPP_01a01d7b_4456_784e_9b3f_4acf61df380c
#include <string_view>
#include <glm/glm.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
namespace libtallis
{
	struct vertex
	{
		glm::vec3 pos, normal;
		glm::vec2 uv;
	};
	/*
	struct mesh
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> mats;
	};*/
	struct model
	{
		std::string path;
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> mats;
		void load_obj(std::string_view const);
		void load_gltf(std::string_view const);
	};
} /* namespace libtallis */
#endif /* LT_MODEL_HPP_01a01d7b_4456_784e_9b3f_4acf61df380c */
