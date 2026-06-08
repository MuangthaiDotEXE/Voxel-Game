#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <print>
#include <filesystem>
#include <stdexcept>

#include <glad/gl.h>

namespace Core
{
	class Shader
	{
	public:
		GLuint programID;

	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);
		virtual ~Shader();

		void Activate();
		void Delete();

	private:
		void Error(GLuint shader, const std::string& type);
	};
}

#endif
