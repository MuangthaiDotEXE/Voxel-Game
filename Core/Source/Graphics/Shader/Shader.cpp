#include "Shader.h"

std::string ReadFile(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);

	if (!file)
	{
		throw std::runtime_error("Failed to read the file: {} (Input/Output)\n");
	}

	std::string content;
	file.seekg(0, std::ios::end);
	content.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	file.close();

	return content;
}

Core::Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::string vertexCode = ReadFile(vertexFile);
	std::string fragmentCode = ReadFile(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	Error(vertexShader, "Vertex shader");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	Error(fragmentShader, "Fragment shader");

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	Error(programID, "Shader program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Core::Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Core::Shader::Activate()
{
	glUseProgram(programID);
}

void Core::Shader::Delete()
{
	glDeleteProgram(programID);
}

void Core::Shader::Error(GLuint shader, const std::string& type)
{
	GLint compiled;
	char infoLog[1024];

	if (type == "Shader program")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &compiled);

		if (compiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::print(stdout, "\033[33m{} linking failed: {}\033[0m\n", shader, infoLog);
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::print(stdout, "\033[33m{} compilation failed: {}\033[0m\n", shader, infoLog);
		}
	}
}
