#include"shader.h"

#include<string>//需要用字符串承接 Shader 代码
#include<fstream>//为了读取文件，引入 C++ 的文件读取流
#include<sstream>//字符串流
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	//01.声明d装入 Shader 代码字符串的两个 string
	std::string vertexCode;
	std::string	fragmentCode;
	//声明，用于读取 vs 和 fs 文件的 infilestream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//保证 if stream 遇到问题的时候，可以抛出异常
	//(文件读取失败|文件损坏)
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//try:比较标准的 C++ 异常捕获和处理
	try {
		//1 打开文件
		vShaderFile.open(vertexPath); 
		fShaderFile.open(fragmentPath);

	//2 将文件输入流当中的字符串输入到 stringstream 中
		//声明需要的变量
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//3 关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//4 将字符串从 stringstream 中读取出来,转化到 code string 中
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "shader文件错误: " << e.what() << std::endl;
	}

	//定义变量并给予 shadow 代码
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//为程序输入shader代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    

	//编译
    glCompileShader(vertex);
	checkShaderErrors(vertex, "COMPILE");
    glCompileShader(fragment);
	checkShaderErrors(fragment, "COMPILE");

    //使用类内的变量
    mProgram = glCreateProgram();

    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);

    glLinkProgram(mProgram);
	checkShaderErrors(mProgram, "LINK");


    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {

}

void Shader::begin() {
	GL_CALL(glUseProgram(mProgram));
}

void Shader::end() {
	GL_CALL(glUseProgram(0));
}

//允许外界更新Uniform变量
void Shader::setUFloat(const std::string& name, float value)
{
	//1.通过名称，拿到Uniform变量的位置
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//因为是通用代码，所以加上查错;

	//2.通过Location更新Uniform变量的值
	GL_CALL(glUniform1f(location, value));
}

void Shader::setInt(const std::string& name, int value) {
	//1.通过名称，拿到Uniform变量的位置
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//因为是通用代码，所以加上查错;

	//2.通过Location更新Uniform变量的值
	GL_CALL(glUniform1i(location, value));

}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value) {
	//1.通过名称，拿到Uniform变量的位置
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//因为是通用代码，所以加上查错;

	//2.通过Location更新Uniform变量的值
	GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));

}






void Shader::checkShaderErrors(GLuint target, std::string type) {
	int success = 0;
	char infoLog[1024];

	//type:COMPILE & LINK
	if (type == "COMPILE")
	{
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "错误：GLSL，" << target <<"编译错误: " << infoLog << std::endl;
		}
	}
	else if (type == "LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "错误：GLSL，" << target << "链接 错误 : " << infoLog << std::endl;
		}
	}
	else { std::cout << "错误检查类型错误" << std::endl; }
}