#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), const glm::vec3& scl = glm::vec3(1.0f))
	{
		constrainPitch = false;
		setPosition(pos);
		setRotation(rot);
		setScale(scl);
		calculateVectors();
	}
	~Transform()
	{

	}

	inline glm::mat4 GetModelMatrix()
	{
		glm::mat4 modelMatrix(1.0f);

		modelMatrix = glm::translate(modelMatrix, position);

		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		modelMatrix = glm::scale(modelMatrix, scale);

		return modelMatrix;
	}

	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getRotation() { return rotation; }
	inline glm::vec3 getScale() { return scale; }
	inline glm::vec3 getForwardVector() { return forwardVector; }
	inline glm::vec3 getUpVector() { return upVector; }
	inline glm::vec3 getRightVector() { return rightVector; }

	inline void setPosition(const glm::vec3 position) { this->position = position; }
	inline void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
		constrainPitchF();
		calculateVectors();
	}
	inline void setScale(const glm::vec3 scale) { this->scale = scale; }

	inline void addPosition(const glm::vec3 position) { this->position += position; }
	inline void addRotation(const glm::vec3 rotation)
	{
		this->rotation += rotation;
		constrainPitchF();
		calculateVectors();
	}
	inline void addScale(const glm::vec3 scale) { this->scale += scale; }

	bool constrainPitch;
	
private:
	
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 position, rotation, scale;
	glm::vec3 forwardVector, upVector, rightVector;

	void calculateVectors()
	{

		forwardVector = glm::vec3(cos(rotation.x) * cos(rotation.y), sin(rotation.x), cos(rotation.x) * sin(rotation.y));

		rightVector = glm::normalize(glm::cross(forwardVector, worldUp));

		upVector = glm::normalize(glm::cross(rightVector, forwardVector));
	}

	void constrainPitchF()
	{
		if (constrainPitch)
		{
			if (rotation.x * 57.2958 > 89.0f)
				rotation.x = 89.0f * 0.0175;
			if (rotation.x * 57.2958 < -89.0f)
				rotation.x = -89.0f * 0.0175;
		}
	}
};