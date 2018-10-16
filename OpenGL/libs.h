#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

#include <gl\glew.h>
#include <glfw\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include <SOIL2\SOIL2.h>

#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\material.h>

#include "Window.h"
#include "Vertex.h"
#include "Transform.h"
#include "Camera.h"
#include "Shaders.h"
#include "OBJLoader.h"
#include "Mesh.h"

#include <stdio.h>
#include <direct.h>