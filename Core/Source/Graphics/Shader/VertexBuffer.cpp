#include "VertexBuffer.h"

Core::VertexBuffer::VertexBuffer(GLfloat* vertices)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

Core::VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Core::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vboID);
}

void Core::VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void Core::VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
