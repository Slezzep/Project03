#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos_, glm::vec3 front_, glm::vec3 up_) {
	this->pos = pos_;
	this->front = front_;
	this->up = up_;

	this->right = glm::normalize(glm::cross(front_, up_));
}
glm::mat4 Camera::lookAt() {
	return glm::lookAt(this->pos, this->pos + this->front, this->up);
}
void Camera::process_mouse(float xpos, float ypos) {
	xpos *= this->sensitivity;
	ypos *= this->sensitivity;

	this->yaw += xpos;
	this->pitch += ypos;

	if (pitch >= 89.0f)
		pitch = 89.0f;
	if (pitch <= -89.0f)
		pitch = -89.0f;

	this->update_vectors();
}

void Camera::process_keyboard(MOVES move, float deltaTime) {
	float move_speed = this->speed * deltaTime;

	if (move == FRONT)
		this->pos += this->front * move_speed;
	if (move == BACK)
		this->pos -= this->front * move_speed;
	if (move == RIGHT)
		this->pos += this->right * move_speed;
	if (move == LEFT)
		this->pos -= this->right * move_speed;
}

void Camera::update_vectors() {
	glm::vec3 direction;

	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(direction);
	this->right = glm::normalize(glm::cross(this->front, this->up));
}