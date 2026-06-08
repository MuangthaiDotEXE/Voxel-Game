#include "ElementBuffer.h"

Core::ElementBuffer::ElementBuffer(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

Core::ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &eboID);
}

void Core::ElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void Core::ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
