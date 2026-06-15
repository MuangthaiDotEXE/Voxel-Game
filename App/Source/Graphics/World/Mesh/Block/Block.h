#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/VertexArray.h"
#include "Graphics/Shader/VertexBuffer.h"
#include "Graphics/Shader/ElementBuffer.h"
#include "Graphics/Texture/Texture.h"

namespace App
{
	class Block
	{
	public:
		Core::Shader shader;
		Core::VertexArray vao;
		Core::VertexBuffer vbo;
		Core::ElementBuffer ebo;
		Core::Texture texture;

		struct Transform
		{
			glm::vec3 position = glm::vec3(0.0f);
			glm::vec3 rotation = glm::vec3(0.0f);
			glm::vec3 scale = glm::vec3(1.0f);

			glm::mat4 GetMatrix() const;
		};

		Transform transform;

	public:
		Block();
		virtual ~Block() = default;

		void Render();
		void Update();
	};
}

#endif
