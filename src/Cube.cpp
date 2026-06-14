#include "Cube.h"
#include "Shapes.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

Cube::Cube(glm::vec3 pos_, glm::vec3 size_) : Object(pos_, size_){
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_), cube_, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
}

void Cube::draw() {
	glDrawArrays(GL_TRIANGLES, 0, 36);
}