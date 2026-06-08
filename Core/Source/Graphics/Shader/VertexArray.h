#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/gl.h>

#include "VertexBuffer.h"

namespace Core
{
	class VertexArray
	{
	private:
		GLuint vaoID;

	public:
		VertexArray();
		virtual ~VertexArray();

		void LinkAttributes(VertexBuffer& vbo, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, const void* offset);
		void Bind();
		void Unbind();
	};
}

#endif
