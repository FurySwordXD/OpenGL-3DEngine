#pragma once

#include "libs.h"

class Camera
{
public:
	Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		fieldOfView = fov;
		this->aspectRatio = aspectRatio;
		nearClipPlane = nearPlane;
		farClipPlane = farPlane;
		transform.constrainPitch = true;

		projectionMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
	}
	~Camera()
	{
	}

	void setFieldOfView(float fov) { fieldOfView = fov; }
	void setAspectRatio(float aspectRatio){ this->aspectRatio = aspectRatio; }
	void setClipPlanes(float nearPlane = 0.01f, float farPlane = 1000.0f)
	{
		nearClipPlane = nearPlane;
		farClipPlane = farPlane;
	}

	glm::mat4& getCameraViewMatrix()
	{
		viewMatrix = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getForwardVector(), transform.getUpVector());
		return viewMatrix;
	}
	glm::mat4& getCameraProjectionMatrix()
	{
		projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane);
		return projectionMatrix;
	}

	Transform transform;
private:
	

	float fieldOfView;
	float aspectRatio;
	float nearClipPlane, farClipPlane;
	float yaw, pitch;
	glm::mat4 projectionMatrix, viewMatrix;

};