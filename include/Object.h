#pragma once
#include <glm/glm.hpp>

class Object {
	public:
		glm::vec3 pos;
		glm::vec3 size;
		Object(glm::vec3 pos, glm::vec3 size);
		void bindVAO();
		virtual void draw() = 0;
	protected:
		unsigned int VBO;
		unsigned int VAO;
};