#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/gl.h>

namespace Core
{
	class VertexBuffer
	{
	private:
		GLuint vboID;

	public:
		VertexBuffer(GLfloat* vertices);
		VertexBuffer(GLfloat* vertices, GLsizeiptr size);
		virtual ~VertexBuffer();

		void Bind();
		void Unbind();
	};
}

#endif
