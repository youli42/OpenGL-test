#pragma once

#include"core.h"
#include<string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();

	void end();

	//允许外界更新Uniform变量
	void setUFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
	void setMatrix4x4(const std::string& name, glm::mat4 value);

private:
	void checkShaderErrors(GLuint target, std::string type);

private:
	GLuint mProgram{ 0 };
};