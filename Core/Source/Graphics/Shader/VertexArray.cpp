#include "VertexArray.h"

Core::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vaoID);
}

Core::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vaoID);
}

void Core::VertexArray::LinkAttributes(VertexBuffer& vbo, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, const void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void Core::VertexArray::Bind()
{
	glBindVertexArray(vaoID);
}

void Core::VertexArray::Unbind()
{
	glBindVertexArray(0);
}
