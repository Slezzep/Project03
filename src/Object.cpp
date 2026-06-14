#include "Object.h"
#include <glad/glad.h>

Object::Object(glm::vec3 pos_, glm::vec3 size_) {
	this->pos = pos_;
	this->size = size_;
}
void Object::bindVAO() {
	glBindVertexArray(this->VAO);
}
