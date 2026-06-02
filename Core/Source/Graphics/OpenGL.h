#pragma once

#ifndef OPENGL_API_H
#define OPENGL_API_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Graphics.h"

namespace Core
{
	class OpenGL : public Graphics
	{
	private:
		int version;

	public:
		OpenGL(GLFWwindow* window);
		virtual ~OpenGL() = default;

		void Render() override;
		void Update() override;

		void ViewportResize();
	};
}

#endif
