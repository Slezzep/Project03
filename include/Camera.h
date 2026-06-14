#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum MOVES {
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

class Camera {
	public:
		glm::vec3 pos;
		glm::vec3 front;
		glm::vec3 up;
		/// <summary>
		/// Camera class constructor, this constructor need as parameters three vectors 3D to set the camera direction and position.
		/// </summary>
		/// <param name="pos_">Camera position</param>
		/// <param name="front_">Camera direction</param>
		/// <param name="up_">Camera up</param>
		Camera(glm::vec3 pos_, glm::vec3 front_, glm::vec3 up_);
		glm::mat4 lookAt();
		void process_mouse(float xpos, float ypos);
		void process_keyboard(MOVES move, float deltaTime);
	private:
		void update_vectors();
		glm::vec3 right;
		float speed = 2.0f;
		float sensitivity = 0.1f;
		float yaw = -90.0f;
		float pitch = 0.0;
};

#endif