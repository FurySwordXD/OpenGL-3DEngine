#pragma once

#include "libs.h"

class OBJLoader
{
public:
	OBJLoader(std::string meshFilePath)
	{
		std::string line;

		std::ifstream meshfile;
		meshfile.open(meshFilePath);
		
		std::vector<float> U, V;
		if (meshfile.is_open())
		{
			while (std::getline(meshfile, line))
			{
				std::istringstream iss;
				iss.str(line);
				std::string word;
				iss >> word;
				if (word == "v")
				{
					float x, y, z;
					iss >> x;
					iss >> y;
					iss >> z;
					x /= 100;
					y /= 100;
					z /= 100;
					Vertex vertex;
					vertex.position = glm::vec3(x, y, z);
					vertices.push_back(vertex);
				}
				/*if (word == "vt")
				{
					float u, v;
					iss >> u;
					iss >> v;
					U.push_back(u);
					V.push_back(v);
				}*/
				if (word == "f")
				{
					std::string temp;
					size_t pos;
					for(int i = 0; i < 3; i++)
					{ 
						iss >> temp;
						pos = 0;
						std::string token;
						//unsigned int index;
						pos = temp.find("//");
						token = temp.substr(0, pos);
						unsigned int index = stoi(token) - 1;
						indices.push_back(index);
						temp.erase(0, pos + 1);
						if (temp.find("//") != std::string::npos)
						{
							token = temp.substr(pos + 1, temp.find("//"));
							std::cout << token << std::endl;
						}
						/*int c = 0;
						while ((pos = temp.find("/")) != std::string::npos) {
							token = temp.substr(0, pos);
							
							switch (c)
							{
							case 0:
								index = stoi(token) - 1;
								indices.push_back(index);
								break;
							case 1:
								if (token != "")
								{
									index = stoi(token) - 1;
									vertices[indices.back()].texCoord = glm::vec2(U[index],					V[index]);
								}
								break;
							default:
								break;
							}
							temp.erase(0, pos + 1);
							c++;
						}*/
					}
					
				}
			}
		}
		meshfile.close();
	}

	void getData()
	{
		std::cout << std::endl;
		for (int i = 0; i < vertices.size(); i++)
		{
			std::cout << "Vertex " << i << " Position: " << vertices[i].position.x << " " << vertices[i].position.y << " " <<vertices[i].position.z << " UV: " << vertices[i].texCoord.x << " " << vertices[i].texCoord.y << std::endl;
		}
		std::cout << "Draw Order: " << std::endl;
		for (int i = 0; i < indices.size(); i+=3)
		{
			std::cout << indices[i] << " " << indices[i+1] << " " << indices[i+2] << std::endl;
		}
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
private:

};