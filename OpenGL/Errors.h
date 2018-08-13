#pragma once

#include "libs.h"

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	glfwTerminate();
}