#pragma once

#include "libs.h"

struct Vertex
{
	Vertex()
	{
		position = glm::vec3(0.f);
		color = glm::vec3(1.0f);
		texCoord = glm::vec2(0.f);
	}
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;
};

struct Texture
{
	std::string filePath;
	GLuint id;
	int width, height;
};