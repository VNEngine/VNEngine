#pragma once

#ifndef OPENGL_INCLUDED
#include"VNLibsImport.hpp"
#include "VNImage.hpp"
#include "VNShader.hpp"
#endif // !OPENGL_INCLUDED

class VNWindow
{
public:
	VNWindow(int width = 800, int height = 600, const char* title = "title", int posX = 100, int posY = 50);
	~VNWindow();
	void VNSetWindowTitle(const char* title);
	const char* VNGetWindowTitle() const;
	void VNSetWindowSize(int width, int height);
	int VNGetWindowWidth() const;
	int VNGetWindowHeight() const;
	void VNSetWindowPos(int posX, int posY);
	void VNSetScreenRatio(int width, int height);
	GLFWwindow* VNGetWindowPointer() const;
	void VNInitViewport();


private:
	int mWidth;
	int mHeight;
	int mPosX;
	int mPosY;
	const char* mTitle;
	int mScreenRatioWidth;
	int mScreenRatioHeight;
	GLFWwindow* mWindow;//基本不需要也无法直接调用
	//void VNFramebufferSizeCallback(GLFWwindow* window, int width, int height);
	//friend class VNGame;
};

VNWindow::VNWindow(int width, int height, const char* title, int posX, int posY)
{
	mWidth = width;
	mHeight = height;
	mPosX = posX;
	mPosY = posY;
	mTitle = title;
	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);
	if (!mWindow) {
		std::cout << "Create window failed!" << std::endl;
		glfwTerminate();
	}
	//glViewport(0, 0, mWidth, mHeight);
	glfwMakeContextCurrent(mWindow);
	glfwSetWindowPos(mWindow, mPosX, mPosY);
	VNSetScreenRatio(mWidth, mHeight);
}

VNWindow::~VNWindow()
{
	glfwDestroyWindow(mWindow);
	mWindow = nullptr;
}

void VNWindow::VNSetWindowTitle(const char* title)
{
	mTitle = title;
	glfwSetWindowTitle(mWindow, mTitle);
	return;
}

const char* VNWindow::VNGetWindowTitle() const
{
	return mTitle;
}

void VNWindow::VNSetWindowSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
	glfwSetWindowSize(mWindow, mWidth, mHeight);
	glViewport(0, 0, mWidth, mHeight);
	return;
}

int VNWindow::VNGetWindowWidth() const
{
	return mWidth;
}

int VNWindow::VNGetWindowHeight() const
{
	return mHeight;
}

void VNWindow::VNSetWindowPos(int posX, int posY)
{
	mPosX = posX;
	mPosY = posY;
	glfwSetWindowPos(mWindow, mPosX, mPosY);
	return;
}

void VNWindow::VNSetScreenRatio(int width, int height)
{
	mScreenRatioWidth = width;
	mScreenRatioHeight = height;
}

GLFWwindow* VNWindow::VNGetWindowPointer() const
{
	return mWindow;
}

void VNWindow::VNInitViewport()
{
	glViewport(0, 0, mHeight * (mScreenRatioWidth / mScreenRatioHeight), mHeight);
	//glfwSetFramebufferSizeCallback(mWindow, this->VNFramebufferSizeCallback);
	return;
}
/*
void VNWindow::VNFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	mWidth = width;
	mHeight = height;
	glViewport(0, 0, mWidth, mHeight);
	return;
}
*/
