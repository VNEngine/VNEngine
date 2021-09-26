#pragma once

#ifndef OPENGL_INCLUDED
#include"VNLibsImport.hpp"
#endif // !OPENGL_INCLUDED

class VNImage
{
public:
	VNImage(const char* path);
	~VNImage();
	unsigned int VNGetImageID() const;
	int VNGetImageWidth() const;
	int VNGetImageHeight() const;
	int VNGetImageNrChannels() const;

private:
	int mWidth, mHeight, mNrChannels;
	unsigned int mId;

};

VNImage::VNImage(const char* path)
{
	unsigned char* tData = stbi_load(path, &mWidth, &mHeight, &mNrChannels, 0);
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (tData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::IMAGE::LOADING_FILE_FAILED" << std::endl;
	}
	stbi_image_free(tData);
	tData = nullptr;

}

VNImage::~VNImage()
{
	glDeleteTextures(1, &mId);
}

unsigned int VNImage::VNGetImageID() const
{
	return mId;
}

int VNImage::VNGetImageWidth() const
{
	return mWidth;
}

int VNImage::VNGetImageHeight() const
{
	return mHeight;
}

int VNImage::VNGetImageNrChannels() const
{
	return mNrChannels;
}
