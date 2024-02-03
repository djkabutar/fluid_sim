#include <GL/glew.h>

#include <iostream>
#include <fstream>

#include <Shader.h>

Shader::Shader(const std::string& vertSLPath, const std::string& fragSLPath)
	: m_RendererID(0), vertShaderID(0), fragShaderID(0)
{
	std::string vertSL = ParseShader(vertSLPath);
	std::string fragSL = ParseShader(fragSLPath);
	m_RendererID = CreateShader(vertSL, fragSL);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

std::string Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::string shaderCode;
	while (getline(stream, line))
	{
		shaderCode += line + "\n";
	}
	return shaderCode;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " 
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	vertShaderID = CompileShader(GL_VERTEX_SHADER, vertexShader);
	fragShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vertShaderID);
	glAttachShader(program, fragShaderID);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	return program;
}
