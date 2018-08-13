#pragma once

#include "libs.h"


class Shaders
{
public:
	Shaders(std::string fileName = "shader");
	~Shaders();

	void useShaderProgram(){ glUseProgram(program); }
	void unuseShaderProgram(){ glUseProgram(0); }

	void update(Transform& transform);
	void setCamera(Camera* camera) { this->camera = camera; }

	GLuint& getShaderProgram() { return program; }
private:
	
	void loadShaders();
	void attachShaders();

	std::string shaderFile;

	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

	Camera* camera;
};
