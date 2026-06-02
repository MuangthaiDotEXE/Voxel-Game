#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GLFW/glfw3.h>

namespace Core
{
	class Graphics
	{
	protected:
		GLFWwindow* window;

	public:
		Graphics(GLFWwindow* window);
		virtual ~Graphics() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
