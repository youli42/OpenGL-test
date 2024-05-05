#pragma once

#include<string>

#include "core.h"

class Texture {
public:
	Texture(const std::string path, unsigned int unit);
	~Texture();

	void bindTexture();

	//±©Â¶³¤¿í
	int getWidth()const { return mWidth; };
	int getHeight()const { return mHeight; };

private:
	GLuint mTexture;
	int mWidth{ 0 };
	int mHeight{ 0 };
	unsigned int mUnit{ 0 };
};