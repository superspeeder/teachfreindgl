#pragma once

#include <string>

class ShaderProgram // uses vertex and shader
{
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int shader_id;
public:
	ShaderProgram(std::string vertexPath, std::string fragmentPath); // expects a vertexShader.shader and a fragmentShader.shader
	~ShaderProgram();
	void Use() const;

	unsigned int GetUniformLocation(std::string name);
};

