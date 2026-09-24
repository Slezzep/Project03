#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <iostream>

class Shader {
	public:
		unsigned int ID;
		Shader(const char* vertexPath, const char* fragmentPath);
		void use();
		void setBool(const std::string& name, int value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec3(const std::string& name, float a, float b, float c) const;
		void setVec3(const std::string& name, glm::vec3 &value) const;
		void setMat3(const std::string& name, glm::mat3 &value) const;
		void setMat4(const std::string& name, glm::mat4 &value) const;
	private:
		void printErrors(std::string type, unsigned int id);
};

#endif