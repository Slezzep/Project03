#pragma once
#ifndef IMAGE_H
#define IMAGE_H

class Image {
	public:
		unsigned char* data;
		int width, height, nrChannels;
		Image(const char* img_path);
		void load(const char* img_path);
		~Image();
};

#endif