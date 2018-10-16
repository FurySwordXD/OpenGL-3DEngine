#pragma once

#include "libs.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::string texturePath);
	~Mesh();

	void draw();

	Transform transform;
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	std::vector<Vertex> vertices; 
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	GLuint drawcount;
};

