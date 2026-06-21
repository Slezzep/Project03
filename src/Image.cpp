#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stb_image.h>
#include <stdexcept>
#include <string>

Image::Image(const char* image_path = "") {
	try {
		if (image_path != nullptr && image_path[0] == '\0') {
			throw std::invalid_argument("ERROR::REQUIRED_PATH_VALUE");
		}
		this->data = stbi_load(image_path, &width, &height, &nrChannels, NULL);
	}
	catch (std::invalid_argument& e) {
		const char* error = e.what();
		
		if (error == "ERROR::REQUIRED_PATH_VALUE") {
			std::cout << "REQUIRED" << std::endl;
		}
	}
}
void Image::load(const char* image_path) {
	try {
		if (image_path != nullptr && image_path[0] == '\0') {
			throw std::invalid_argument("ERROR::REQUIRED_PATH_VALUE");
		}
		this->data = stbi_load(image_path, &width, &height, &nrChannels, NULL);
	}
	catch (std::invalid_argument& e) {
		const char* error = e.what();

		if (error == "ERROR::REQUIRED_PATH_VALUE") {
			std::cout << "REQUIRED" << std::endl;
		}
	}
}
Image::~Image() {
	stbi_image_free(this->data);
}