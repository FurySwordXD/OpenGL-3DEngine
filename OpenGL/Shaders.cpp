#include "Shaders.h"

Shaders::Shaders(std::string fileName)
{
	shaderFile = fileName;
	loadShaders();
}


Shaders::~Shaders()
{
	glDeleteProgram(program);
}

void Shaders::loadShaders()
{
	char infoLog[512];
	GLint success;
	std::string fileName;
	std::string temp = "";
	std::string src = "";
	std::ifstream file;

	fileName = shaderFile + ".vertex";
	file.open(fileName);
	if (file.is_open())
	{
		while (std::getline(file, temp))
			src += temp + "\n";
	}
	else
		std::cout << "Could not load " << shaderFile << ".vertex file!";
	file.close();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Could not compile " << shaderFile << ".vertex file!" << std::endl;
		std::cout << infoLog;
	}

	temp = "";
	src = "";
	fileName = shaderFile + ".fragment";
	file.open(fileName);
	if (file.is_open())
	{
		while (std::getline(file, temp))
			src += temp + "\n";
	}
	else
		std::cout << "Could not load " << shaderFile << ".fragment file!";
	file.close();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Could not compile " << shaderFile << ".fragment file!" << std::endl;
		std::cout << infoLog;
	}

	attachShaders();
}

void Shaders::attachShaders()
{
	char infoLog[512];
	GLint success;

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Could not link " << shaderFile << "!" << std::endl;
		std::cout << infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shaders::update(Transform& transform)
{
	glUniform1i(glGetUniformLocation(program, "diffuseTexture"), 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, &transform.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, &camera->getCameraViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, &camera->getCameraProjectionMatrix()[0][0]);
}