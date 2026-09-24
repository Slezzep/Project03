#include "Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexStr;
	std::string fragmentStr;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	try {
		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexStr = vertexStream.str();
		fragmentStr = fragmentStream.str();
	}
	catch (std::exception &e) {
		std::cout << "ERROR::SHADER::FILE_COULD_NOT_LOAD" << std::endl;
	}

	const char* vertexSrc = vertexStr.c_str();
	const char* fragmentSrc = fragmentStr.c_str();


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);
	this->printErrors("VERTEX", vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);
	this->printErrors("FRAGMENT", fragmentShader);

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	glLinkProgram(this->ID);
	this->printErrors("PROGRAM", this->ID);

	int attached_Shaders;
	glGetProgramiv(this->ID, GL_ATTACHED_SHADERS, &attached_Shaders);
	std::cout << "ATTACHED_SHADERS: " << attached_Shaders << std::endl;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
//-------------------------------Vec3
void Shader::setVec3(const std::string& name, float a, float b, float c) const {
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), a, b, c);
}
void Shader::setVec3(const std::string& name, glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
}
//-------------------------------Mat3
void Shader::setMat3(const std::string &name, glm::mat3& value) const {
	glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
//-------------------------------Mat4
void Shader::setMat4(const std::string &name, glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}


void Shader::printErrors(std::string type, unsigned int id_) {
	int success;
	char InfoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(id_, 1024, NULL, InfoLog);
			std::cout << "ERROR::SHADER::COMPILE_ERROR_OF_TYPE::" << type << "::ERROR:: \n" << InfoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(id_, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(id_, 1024, NULL, InfoLog);
			std::cout << "ERROR::SHADER::COMPILE_ERROR_OF_TYPE::PROGRAM::ERROR:: \n" << InfoLog << std::endl;
		}
	}
}