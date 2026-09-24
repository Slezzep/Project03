//<<<>>>
//Silver (Slezzep) Template <>

#define	WIDTH_		800
#define	HEIGHT_		600

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Lightning.h"
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

float x_mouse = 0.0f;
float y_mouse = 0.0f;

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
	Cube light(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.3f, 0.3f, 0.3f));

	// Textures

	unsigned int baldosas = load_texture("assets/Textures/baldosas.jpg");
	unsigned int baldosas_spec = load_texture("assets/Textures/baldosas-spec.png");

	//Lightning

	glm::vec3 sun_light_color = glm::vec3(0.6f, 0.8f, 0.5f);
	glm::vec3 point_light_color = glm::vec3(0.6f, 0.8f, 0.5f);

	DirectionalLight sun_light = {
				glm::vec3(1.0f, -1.0f, 0.5f),

				sun_light_color * 0.7f,
				sun_light_color,
				glm::vec3(1.0f, 1.0f, 1.0f)
	};

	PointLight point_light = {
				glm::vec3(0.0f, 0.0f, 0.0f),

				sun_light_color * 0.7f,
				sun_light_color,
				glm::vec3(1.0f, 1.0f, 1.0f)
	};


	//Materials


	//Coordinate System

	glm::mat4 model = glm::mat4(1.0);

	glm::mat4 view = glm::mat4(1.0);

	glm::mat4 projection;

	projection = glm::perspective(glm::radians(fov), (float) window_width / (float) window_height, 0.1f, 100.0f);

	//Shaders

	Shader basic_shader("assets/Shaders/BasicShader.vert", "assets/Shaders/BasicShader.frag");
	Shader lightning_shader("assets/Shaders/LightningShader.vert", "assets/Shaders/LightningShader.frag");
	Shader light_shader("assets/Shaders/LightShader.vert", "assets/Shaders/LightShader.frag");

	lightning_shader.use();
	lightning_shader.setInt("diffuse_0", 0);
	lightning_shader.setInt("specular_0", 1);
	lightning_shader.setVec3("dirLight.direction", sun_light.direction);
	lightning_shader.setVec3("dirLight.ambient", sun_light.ambient);
	lightning_shader.setVec3("dirLight.diffuse", sun_light.diffuse);

	//Motor configs

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		//Procesamiento de entrada
		processInput(window);

		//DeltaTime 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Renderizado


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.01f, 0.09f, 1.0f);

		view = cam.lookAt();

		activate_texture(baldosas, GL_TEXTURE0);
		activate_texture(baldosas_spec, GL_TEXTURE1);

		lightning_shader.use();

		model = glm::mat4(1.0);

		glm::mat3 normal_matrix = glm::transpose(glm::inverse(model));

		cb.bindVAO();
		cb.draw();

		lightning_shader.setVec3("dirLight.direction", glm::vec3(glm::vec4(sun_light.direction, 1.0f)));
		lightning_shader.setVec3("viewPos", cam.pos);

		lightning_shader.setMat3("normal_matrix", normal_matrix);
		lightning_shader.setMat4("model", model);
		lightning_shader.setMat4("view", view);
		lightning_shader.setMat4("projection", projection);


		//-------------------------Light

		light_shader.use();

		model = glm::mat4(1.0);
		model = glm::translate(model, light.pos);
		model = glm::scale(model, light.size);

		light.bindVAO();
		light.draw();

		light_shader.setMat4("model", model);
		light_shader.setMat4("view", view);
		light_shader.setMat4("projection", projection);

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

	x_mouse = xoffset;
	y_mouse = yoffset;
	cam.process_mouse(xoffset, yoffset);
}