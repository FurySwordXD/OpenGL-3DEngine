#include "libs.h"

float mouseX = 0, mouseY = 0;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
}

void processInput(GLFWwindow* window, Camera& camera)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.transform.addPosition(camera.transform.getForwardVector() / glm::vec3(100));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.transform.addPosition(-camera.transform.getForwardVector() / glm::vec3(100));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.transform.addPosition(-camera.transform.getRightVector() / glm::vec3(100));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.transform.addPosition(camera.transform.getRightVector() / glm::vec3(100));
	}
	static float xpos = mouseX, ypos = mouseY;
	float deltaX = mouseX - xpos;
	float deltaY = mouseY - ypos;
	xpos = mouseX, ypos = mouseY;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.transform.addRotation(glm::vec3(deltaY / -100, deltaX / 100, 0.f));
	}
	
	
}

int main(int argc, char** argv)
{
	char full[_MAX_PATH];
	std::string cwd = _fullpath(full, "", _MAX_PATH);

	Window window;
	Shaders shaders( cwd + "\\Shaders\\shader");

	glfwSetCursorPosCallback(window.glfwWindow, cursor_position_callback);
	Camera camera(90.0f, 4.0f / 3.0f, 0.01f, 1000.0f);
	camera.transform.setPosition(glm::vec3(0.f, 0.f, -5.f));
	camera.transform.setRotation(glm::vec3(0.f, 90 * 0.0175, 0.f));

	shaders.setCamera(&camera);

	std::string path = cwd + "\\Assets\\car.obj";
	std::string texpath = cwd + "\\Assets\\wood.png";
	std::cout << path;

	OBJLoader objloader(path);
	//objloader.getData();

	std::vector<Mesh> meshes;

	for (int i = 0; i < 1; i++)
		meshes.emplace_back(objloader.vertices, objloader.indices, texpath);

	/*const aiScene* pScene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	std::vector<Vertex> vertices;
	std::vector<GLuint> Indices;
	for (unsigned int j = 0; j < pScene->mNumMeshes; j++)
	{
		const aiMesh* aimesh = pScene->mMeshes[j];

		for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
		{
			Vertex vertex;
			vertex.position = glm::vec3(aimesh->mVertices[i].x / 100, aimesh->mVertices[i].y / 100, aimesh->mVertices[i].z / 100);
			std::cout << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << " " << std::endl;
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
			const aiFace& Face = aimesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
			std::cout << Face.mIndices[0] << " " << Face.mIndices[1] << " " << Face.mIndices[2] << " " << std::endl;
		}
	}*/

	//meshes.emplace_back(vertices, Indices);
	//aiReleaseImport(pScene);
	

	while (!glfwWindowShouldClose(window.glfwWindow))
	{
		glfwPollEvents();

		window.clear(glm::vec4(0.f, 0.5f, 0.5f, 1.f));

		processInput(window.glfwWindow, camera);

		shaders.useShaderProgram();

		camera.setAspectRatio(static_cast<float>(window.frameBufferWidth) / window.frameBufferHeight);

		for (int i = 0; i < meshes.size(); i++)
		{
			shaders.update(meshes[i].transform);
			meshes[i].draw();
		}
		
		shaders.unuseShaderProgram();

		window.swapBuffers();
	}
	return 0;
}