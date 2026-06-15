#include "Camera.h"

App::Camera::Camera(GLFWwindow* window, glm::vec3 position)
	: window(window), position(position)
{
}

void App::Camera::UpdateMatrix(float fov, float nearPlane, float farPlane)
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	glfwGetFramebufferSize(window, &width, &height);
	if (width == 0 || height == 0) return;

	float aspect = (float)width / (float)height;

	view = glm::lookAt(position, position + front, up);
	projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void App::Camera::Matrix(const Core::Shader& shader, const std::string& uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void App::Camera::Input()
{
	Framerate();
	speed = walkSpeed * deltaTime * (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ? sprintMultiplier : 1.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= speed * glm::normalize(glm::cross(front, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= speed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(front, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position -= speed * up;
	}
		
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
	{
		if (clicked)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			clicked = false;
			
			return;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotateX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotateY = sensitivity * (float)(mouseX - (width / 2)) / width;

		pitch -= rotateX;
		yaw += rotateY;

		pitch = glm::clamp(pitch, -89.999f, 89.999f);

		front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		front.y = glm::sin(glm::radians(pitch));
		front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

		front = glm::normalize(front);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
}

glm::vec3 App::Camera::GetPosition() const
{
	return position;
}

void App::Camera::Framerate()
{
	double currentFrame = glfwGetTime();

	deltaTime = currentFrame - previousFrame;
	previousFrame = currentFrame;

	fps = 1.0f / deltaTime;
}
