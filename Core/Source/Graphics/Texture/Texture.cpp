#include "Texture.h"

Core::Texture::Texture(const std::string& texture, const std::string& type, GLuint slot)
	: type(type), unit(slot)
{
	if (!texture.empty() && std::filesystem::exists(texture))
	{
		textureID.clear();
		textureID.emplace_back(LoadTexture(texture, slot));
	}
}

Core::Texture::Texture(const std::vector<std::string>& textures, const std::string& type, GLuint slot)
	: type(type), unit(slot)
{
	if (!textures.empty())
	{
		textureID.clear();
		textureID.reserve(textures.size());

		for (const auto& texture : textures)
		{
			if (std::filesystem::exists(texture))
			{
				textureID.emplace_back(LoadTexture(texture, slot));
			}
		}
	}
}

Core::Texture::~Texture()
{
	if (!textureID.empty())
	{
		glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
		textureID.clear();
	}
}

void Core::Texture::SetUnit(Shader& shader, const std::string& uniform, GLuint unit)
{
	shader.Activate();
	GLuint textureUniform = glGetUniformLocation(shader.programID, uniform.c_str());
	glUniform1i(textureUniform, unit);
}

void Core::Texture::Bind(size_t index)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID[index]);
}

void Core::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Core::Texture::Delete()
{
	if (!textureID.empty())
	{
		glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
		textureID.clear();
	}
}

GLuint Core::Texture::GetID(size_t index) const
{
	return textureID[index];
}

size_t Core::Texture::GetSize() const
{
	return textureID.size();
}

GLuint Core::Texture::LoadTexture(const std::string& path, GLuint slot)
{
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!image)
	{
		throw std::runtime_error(std::format("Failed to load texture: {} (STB image library)\n", path));
	}

	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	else if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	else if (channels == 1) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, image);
	else throw std::runtime_error("Texture type recognition failed (OpenGL graphics API)\n");

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}
