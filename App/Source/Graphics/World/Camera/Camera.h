#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Graphics/Shader/Shader.h"

namespace App
{
	class Camera
	{
	private:
		glm::vec3 position;

		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		float pitch = 0.0f;
		float yaw = -90.0f;

		glm::mat4 view;
		glm::mat4 projection;

		bool clicked = true;

		int width, height;
		GLFWwindow* window;

		float speed;
		const float walkSpeed = 10.0f;
		const float sprintMultiplier = 2.5f;

		const float sensitivity = 100.0f;

		float previousFrame;
		float deltaTime = 0.0f;
		float fps;

	public:
		Camera(GLFWwindow* window, glm::vec3 position);
		virtual ~Camera() = default;

		void UpdateMatrix(float fov, float nearPlane, float farPlane);
		void Matrix(const Core::Shader& shader, const std::string& uniform);
		void Input();

		glm::vec3 GetPosition() const;

	private:
		void Framerate();
	};
}

#endif
