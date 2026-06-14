//Silver Template

#define	WIDTH_		800
#define	HEIGHT_		600

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Cube.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow* window);
void processMouse(GLFWwindow* window, double xpos, double ypos);

int window_width = WIDTH_;
int window_height = HEIGHT_;

float deltaTime = 0;
float lastFrame = 0;

float fov = 45.0f;

bool first_mouse = true;
float lastX = window_width / 2;
float lastY = window_height / 2;

Camera cam(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0, 1.0f, 0.0));

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Ventana", NULL, NULL);

	if (!window) {
		std::cout << "Error al crear la ventana." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, processMouse);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error al cargar GLAD." << std::endl;
		return -1;
	}

	//Objects

	Cube cb(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0f, 1.0f, 1.0f));

	//Coordinate System
	glm::mat4 model = glm::mat4(1.0);

	glm::mat4 view = glm::mat4(1.0);

	glm::mat4 projection;

	projection = glm::perspective(glm::radians(fov), (float) window_width / (float) window_height, 0.1f, 100.0f);

	//Shaders

	Shader basic_shader("assets/Shaders/BasicShader.vert", "assets/Shaders/BasicShader.frag");

	while (!glfwWindowShouldClose(window)) {
		//Procesamiento de entrada
		processInput(window);

		//DeltaTime 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Renderizado

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.01f, 0.09f, 1.0f);

		view = cam.lookAt();

		basic_shader.use();

		cb.bindVAO();
		cb.draw();

		basic_shader.setMat4("model", model);
		basic_shader.setMat4("view", view);
		basic_shader.setMat4("projection", projection);

		//Obtener eventos e intercambiar buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam.process_keyboard(FRONT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam.process_keyboard(BACK, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.process_keyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.process_keyboard(LEFT, deltaTime);
	}
}
void processMouse(GLFWwindow* window, double xpos, double ypos) {
	float x = static_cast<float>(xpos), y = static_cast<float>(ypos);
	if (first_mouse) {
		lastX = x;
		lastY = y;
		first_mouse = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	cam.process_mouse(xoffset, yoffset);
}