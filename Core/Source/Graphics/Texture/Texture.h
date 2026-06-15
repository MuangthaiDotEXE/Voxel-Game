#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <filesystem>

#include <glad/gl.h>
#include <stb_image.h>

#include "../Shader/Shader.h"

namespace Core
{
	class Texture
	{
	private:
		std::vector<GLuint> textureID;
		std::string type;
		GLuint unit;

	public:
		Texture(const std::string& texture, const std::string& type, GLuint slot);
		Texture(const std::vector<std::string>& textures, const std::string& type, GLuint slot);
		virtual ~Texture();

		void SetUnit(Shader& shader, const std::string& uniform, GLuint unit);
		void Bind(size_t index);
		void Unbind();
		void Delete();

		GLuint GetID(size_t index) const;
		size_t GetSize() const;

	private:
		static GLuint LoadTexture(const std::string& path, GLuint slot);
	};
}

#endif
