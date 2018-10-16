#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::string texturePath)
{

	drawcount = indices.size();

	this->vertices = vertices;
	this->indices = indices;
	
	Texture tex;
	tex.filePath = texturePath;
	textures.push_back(tex);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//LOCATION
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//COLOR
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//TEX COORD
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string filePath = textures[i].filePath;

		unsigned char* image = SOIL_load_image(filePath.c_str(), &textures[i].width, &textures[i].height, 0, SOIL_LOAD_RGBA);

		glGenTextures(1, &textures[i].id);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i].width, textures[i].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Mesh::draw()
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(vao);

	//glDrawArrays(GL_TRIANGLES, 0, drawcount);
	glDrawElements(GL_TRIANGLES, drawcount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}