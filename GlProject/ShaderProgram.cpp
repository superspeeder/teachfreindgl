#include "ShaderProgram.h"
#include "Utils.h"

#include <GL/glew.h>

unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader." << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int ShaderProgram::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
{

	std::string vertexShader = Read(vertexPath);
	std::string fragmentShader = Read(fragmentPath);

	//std::cout << vertexShader << std::endl << "========================================" << std::endl;
	//std::cout << fragmentShader << std::endl << "========================================" << std::endl;

	shader_id = CreateShader(vertexShader, fragmentShader);
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shader_id);
}

void ShaderProgram::Use() const {
	glUseProgram(shader_id);
}

unsigned int ShaderProgram::GetUniformLocation(std::string name) {
	return glGetUniformLocation(shader_id, name.c_str());
}