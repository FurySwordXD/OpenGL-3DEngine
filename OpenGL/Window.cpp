#include "Window.h"

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

Window::Window(int width, int height, std::string Title)
{
	glfwInit();

	frameBufferWidth = 0;
	frameBufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glfwWindow = glfwCreateWindow(width, height, Title.c_str(), NULL, NULL);

	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	//glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	glfwMakeContextCurrent(glfwWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew failed to initialize!";
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


Window::~Window()
{
	glfwDestroyWindow(glfwWindow);
}
