#pragma once

#include <glad/glad.h>

unsigned int load_texture(const char* path);
void activate_texture(unsigned int ID, unsigned int texture_unit = GL_TEXTURE0);