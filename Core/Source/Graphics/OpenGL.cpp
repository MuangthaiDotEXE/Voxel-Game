#include "OpenGL.h"

Core::OpenGL::OpenGL(GLFWwindow* window)
	: Graphics(window)
{
	version = gladLoadGL(glfwGetProcAddress);

	if (version == 0)
	{
		throw std::runtime_error("Failed to load OpenGL contexts (OpenGL graphics API)\n");
	}

	glEnable(GL_DEPTH_TEST);
}

void Core::OpenGL::Render()
{
}

void Core::OpenGL::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Core::OpenGL::ViewportResize()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}
