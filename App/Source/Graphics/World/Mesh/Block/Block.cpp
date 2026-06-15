#include "Block.h"

GLfloat vertices[] =
{
	// Position             // Color             // Texture
	-1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    // Front face bottom left vertex
	 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    1.0f, 0.0f,    // Front face bottom right vertex
	 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,	// Front face top right vertex
	-1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f,	// Front face top left vertex

	 1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,    // Back face bottom left vertex
	-1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f,    // Back face bottom right vertex
	-1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,	// Back face top right vertex
	 1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,	// Back face top left vertex

	 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    0.0f, 0.0f,    // Left face bottom left vertex
	 1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,	// Left face bottom right vertex
	 1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,	// Left face top right vertex
	 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,	// Left face top left vertex

	-1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f,    // Right face bottom left vertex
	-1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,	// Right face bottom right vertex
	-1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f,	// Right face top right vertex
	-1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,	// Right face top left vertex

	-1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f,    // Bottom face bottom left vertex
	 1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,	// Bottom face bottom right vertex
	 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    1.0f, 1.0f,	// Bottom face top right vertex
	-1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,	// Bottom face top left vertex

	-1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f,    // Top face bottom left vertex
	 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,	// Top face bottom right vertex
	 1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,	// Top face top right vertex
	-1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f 	// Top face top left vertex
};

GLuint indices[] =
{
	// Front face
	 0, 1, 2,
	 2, 3, 0,

	// Back face
	 4, 5, 6,
	 6, 7, 4,

	// Left face
	 8, 9, 10,
	10, 11, 8,

	// Right face
	12, 13, 14,
	14, 15, 12,

	// Bottom face
	16, 17, 18,
	18, 19, 16,

	// Top face
	20, 21, 22,
	22, 23, 20
};

std::vector<std::string> textures =
{
	ProjectDirectory "/Asset/Texture/Block Side.png",
	ProjectDirectory "/Asset/Texture/Block Side.png",
	ProjectDirectory "/Asset/Texture/Block Side.png",
	ProjectDirectory "/Asset/Texture/Block Side.png",
	ProjectDirectory "/Asset/Texture/Block Bottom.png",
	ProjectDirectory "/Asset/Texture/Block Top.png",
};

glm::mat4 App::Block::Transform::GetMatrix() const
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);

	return matrix;
}

App::Block::Block()
	: shader(ProjectDirectory "/Resource/Shader/Block.vert", ProjectDirectory "/Resource/Shader/Block.frag"),
	vao(),
	vbo(vertices, sizeof(vertices)),
	ebo(indices, sizeof(indices)),
	texture(textures, "texture", 0)
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	texture.SetUnit(shader, "textureSampler", 0);
}

void App::Block::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void App::Block::Update()
{
	shader.Activate();
	vao.Bind();

	for (size_t i = 0; i < 6; i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.GetID(i));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint)));
	}
}
