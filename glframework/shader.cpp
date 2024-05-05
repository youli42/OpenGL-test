#include"shader.h"

#include<string>//��Ҫ���ַ����н� Shader ����
#include<fstream>//Ϊ�˶�ȡ�ļ������� C++ ���ļ���ȡ��
#include<sstream>//�ַ�����
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	//01.����dװ�� Shader �����ַ��������� string
	std::string vertexCode;
	std::string	fragmentCode;
	//���������ڶ�ȡ vs �� fs �ļ��� infilestream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//��֤ if stream ���������ʱ�򣬿����׳��쳣
	//(�ļ���ȡʧ��|�ļ���)
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//try:�Ƚϱ�׼�� C++ �쳣����ʹ���
	try {
		//1 ���ļ�
		vShaderFile.open(vertexPath); 
		fShaderFile.open(fragmentPath);

	//2 ���ļ����������е��ַ������뵽 stringstream ��
		//������Ҫ�ı���
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//3 �ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		//4 ���ַ����� stringstream �ж�ȡ����,ת���� code string ��
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "shader�ļ�����: " << e.what() << std::endl;
	}

	//������������� shadow ����
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//Ϊ��������shader����
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    

	//����
    glCompileShader(vertex);
	checkShaderErrors(vertex, "COMPILE");
    glCompileShader(fragment);
	checkShaderErrors(fragment, "COMPILE");

    //ʹ�����ڵı���
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

//����������Uniform����
void Shader::setUFloat(const std::string& name, float value)
{
	//1.ͨ�����ƣ��õ�Uniform������λ��
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//��Ϊ��ͨ�ô��룬���Լ��ϲ��;

	//2.ͨ��Location����Uniform������ֵ
	GL_CALL(glUniform1f(location, value));
}

void Shader::setInt(const std::string& name, int value) {
	//1.ͨ�����ƣ��õ�Uniform������λ��
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//��Ϊ��ͨ�ô��룬���Լ��ϲ��;

	//2.ͨ��Location����Uniform������ֵ
	GL_CALL(glUniform1i(location, value));

}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value) {
	//1.ͨ�����ƣ��õ�Uniform������λ��
	GLuint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));//��Ϊ��ͨ�ô��룬���Լ��ϲ��;

	//2.ͨ��Location����Uniform������ֵ
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
			std::cout << "����GLSL��" << target <<"�������: " << infoLog << std::endl;
		}
	}
	else if (type == "LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "����GLSL��" << target << "���� ���� : " << infoLog << std::endl;
		}
	}
	else { std::cout << "���������ʹ���" << std::endl; }
}