#pragma once

#include "libs.h"

class Window
{
public:
	Window(int width = 800, int height = 600, std::string Title = "3D");
	~Window();

	GLFWwindow* glfwWindow;

	void clear(glm::vec4 color = glm::vec4(0,0,0,1))
	{
		glfwGetFramebufferSize(glfwWindow, &frameBufferWidth, &frameBufferHeight);
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void swapBuffers()
	{
		glfwSwapBuffers(glfwWindow);
		glFlush();
	}

	int frameBufferWidth;
	int frameBufferHeight;
};

extern Window window;