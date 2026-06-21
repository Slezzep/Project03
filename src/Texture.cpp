#include "Texture.h"
#include "Image.h"

unsigned int load_texture(const char* path) {
	Image img(path);

	unsigned int texture;

	unsigned int rgb_type = (img.nrChannels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (img.data) {
		glTexImage2D(GL_TEXTURE_2D, 0, rgb_type, img.width, img.height, 0, rgb_type, GL_UNSIGNED_BYTE, img.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return texture;
}

void activate_texture(unsigned int ID, unsigned int texture_unit) {
	glBindTexture(GL_TEXTURE_2D, ID);
	glActiveTexture(texture_unit);
}