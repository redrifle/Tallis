#include <string_view>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include <libtallis/lt_model.hpp>

namespace to = tinyobj;

void libtallis::model::load_obj(std::string_view const p)
{
	auto rv {to::LoadObj(&attrib, &shapes, &mats, nullptr, nullptr, p.data())};

	if (not rv)
	{
		throw std::runtime_error("Couldn't load obj file");
	}

	path = p;

	VkDeviceSize const index_count {shapes[0].mesh.indices.size()};
	std::vector<libtallis::vertex> vertices;
	std::vector<uint16_t> indices;
	vertices.reserve(index_count);
	indices.reserve(index_count);

	for (auto& index : shapes[0].mesh.indices)
	{
		libtallis::vertex v {
			{attrib.vertices[index.vertex_index * 3],
			 -attrib.vertices[index.vertex_index * 3 + 1],
			 attrib.vertices[index.vertex_index * 3 + 2]},
			{attrib.normals[index.normal_index * 3],
			 -attrib.normals[index.normal_index * 3 + 1],
			 attrib.normals[index.normal_index * 3 + 2]},
			{attrib.texcoords[index.texcoord_index * 2],
			 1.0f - attrib.texcoords[index.texcoord_index * 2 + 1]}};
		vertices.push_back(v);
		indices.push_back(indices.size());
	}

	VkDeviceSize v_size {sizeof(libtallis::vertex) * vertices.size()};
	VkDeviceSize i_size {sizeof(uint16_t) * indices.size()};
	VkBufferCreateInfo buffer_info {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = v_size + i_size,
		.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
				 VK_BUFFER_USAGE_INDEX_BUFFER_BIT};

	//libtallis::buffer buff (buffer_info);
}
