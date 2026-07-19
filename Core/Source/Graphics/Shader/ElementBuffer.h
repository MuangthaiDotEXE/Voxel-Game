#pragma once

#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <glad/gl.h>

namespace Core
{
	class ElementBuffer
	{
	private:
		GLuint eboID;

	public:
		ElementBuffer(GLuint* indices);
		ElementBuffer(GLuint* indices, GLsizeiptr size);
		virtual ~ElementBuffer();

		void Bind();
		void Unbind();
	};
}

#endif
