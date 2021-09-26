/*
Virtual novel engine PreVer1.0 -- "The First One"
Author: ZZhangC
OpenGL version: 4.6
GLFW version: 3.3
GLAD version: 0.1.34
*/
#pragma once

#include "VNImage.hpp"
#include "VNShader.hpp"
#include "VNText.hpp"
#include "VNWindow.hpp"

class VNGame
{
public:
	VNGame();
	~VNGame();
	int VNInit(VNWindow** window, int width, int height, const char* title, int posX, int posY);
	int VNSetVertex(VNImage* img, int posX, int posY);
	void VNSetShader(VNShader* shader);
	void VNSetWindow(VNWindow* window);
	void VNSetBackgroundColor(float r, float g, float b, float a);
	void VNSetBackgroundColor(VNColor col);
	void VNRun();

private:
	std::vector<unsigned int> mVAOs;
	std::vector<unsigned int> mVBOs;
	std::vector<unsigned int> mEBOs;
	std::vector<VNImage*> mImgs;
	VNWindow* mWindow = nullptr;
	VNShader* mShader = nullptr;
	float mBG_R;
	float mBG_G;
	float mBG_B;
	float mBG_A;
	void VNRenderText(VNText* text, int posX, int posY, float col_r, float col_g, float col_b, float col_a);
	void VNRenderText(VNText* text, int posX, int posY, VNColor col);
	void VNRenderImage(VNImage* img);
	void VNRenderBackground();
	/*
	讲道理，用vector实在是太蠢了
	如果有思路可以用指针重写一下
	2/17/2021    现在还没有重写，我估计算了吧
	*/

};

VNGame::VNGame()
{
}

VNGame::~VNGame()
{
}

int VNGame::VNInit(VNWindow** window, int width, int height, const char* title, int posX, int posY)
{
	int success;
	success = glfwInit();
	if (!success)
	{
		std::cout << "GLFW initialize failed!" << std::endl;
		return 0;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	VNWindow* twindow = new VNWindow(width, height, title, posX, posY);
	success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!success)
	{
		std::cout << "GLAD initialize failed!" << std::endl;
		return 0;
	}
	twindow->VNInitViewport();
	*window = twindow;
	VNSetWindow(twindow);
	mBG_R = 1.0;
	mBG_G = 1.0;
	mBG_B = 1.0;
	mBG_A = 1.0;
	return 1;
}

int VNGame::VNSetVertex(VNImage* img, int posX, int posY)
{
	unsigned int tId = img->VNGetImageID();
	int tX_MAX = mWindow->VNGetWindowWidth();
	int tY_MAX = mWindow->VNGetWindowHeight();
	int tWidth = img->VNGetImageWidth();
	int tHeight = img->VNGetImageHeight();

	unsigned int tVAO, tVBO, tEBO;

	//--------Warnings--------//
	//Debug
	std::cout << "posX = " << posX << std::endl;
	std::cout << "posY = " << posY << std::endl;
	std::cout << "tX_MAX = " << tX_MAX << std::endl;
	std::cout << "tY_MAX = " << tY_MAX << std::endl;
	std::cout << "tWidth = " << tWidth << std::endl;
	std::cout << "tHeight = " << tHeight << std::endl;
	std::cout << std::endl;
	//
	if (posX >= tX_MAX) std::cout << "Warning: X position out of range." << std::endl;
	if (posY >= tY_MAX) std::cout << "Warning: Y position out of range." << std::endl;
	if (tWidth > tX_MAX) std::cout << "Warning: Image width out of range." << std::endl;
	if (tHeight > tY_MAX) std::cout << "Warning: Image height out of range." << std::endl;
	//------------------------//

	float tVertexes[] = {
		-1 + (float)2 * (float)( (float)posX / (float)tX_MAX),                   1 - (float)2 * (float)( (float)posY / (float)tY_MAX),                   (float)1, (float)1, (float)1, (float)0, (float)0, //左上角
		-1 + (float)2 * (float)(((float)posX + (float)tWidth) / (float)tX_MAX),  1 - (float)2 * (float)( (float)posY / (float)tY_MAX),                   (float)1, (float)1, (float)1, (float)1, (float)0, //右上角
		-1 + (float)2 * (float)( (float)posX / (float)tX_MAX),                   1 - (float)2 * (float)(((float)posY + (float)tHeight) / (float)tY_MAX), (float)1, (float)1, (float)1, (float)0, (float)1, //左下角
		-1 + (float)2 * (float)(((float)posX + (float)tWidth) / (float)tX_MAX),  1 - (float)2 * (float)(((float)posY + (float)tHeight) / (float)tY_MAX), (float)1, (float)1, (float)1, (float)1, (float)1, //右下角
	};

	for (int i = 0; i < sizeof(tVertexes) / sizeof(float); i++)
	{
		if (i % 8 == 0)
		{
			std::cout << std::endl;
			std::cout << tVertexes[i] << std::endl;
		}
		else if (i == 1 or (i - 1) % 8 == 0)
		{
			std::cout << tVertexes[i] << std::endl;
		}
		else
		{
		}
	}
	std::cout << std::endl;

	unsigned int tIndices[] = {
		0, 1, 3,
		0, 2, 3
	};


	//顶点数组对象
	glGenVertexArrays(1, &tVAO);
	glBindVertexArray(tVAO);
	//顶点缓冲对象
	glGenBuffers(1, &tVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tVertexes), tVertexes, GL_STATIC_DRAW);
	//索引缓冲对象
	glGenBuffers(1, &tEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tIndices), tIndices, GL_STATIC_DRAW);
	//设置顶点属性指针
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	//保存
	this->mVAOs.push_back(tVAO);
	this->mVBOs.push_back(tVBO);
	this->mEBOs.push_back(tEBO);
	this->mImgs.push_back(img);

	return 1;
}

void VNGame::VNSetWindow(VNWindow* window)
{
	mWindow = window;
	return;
}

void VNGame::VNSetShader(VNShader* shader)
{
	mShader = shader;
	return;
}

void VNGame::VNSetBackgroundColor(float r, float g, float b, float a)
{
	mBG_R = r;
	mBG_G = g;
	mBG_B = b;
	mBG_A = a;
	return;
}

void VNGame::VNSetBackgroundColor(VNColor col)
{
	this->VNSetBackgroundColor(col.r, col.g, col.b, col.a);
	return;
}

void VNGame::VNRenderText(VNText* text, int posX, int posY, float col_r, float col_g, float col_b, float col_a)
{

	return;
}

void VNGame::VNRenderBackground()
{
	glClearColor(mBG_R, mBG_G, mBG_B, mBG_A);
	glClear(GL_COLOR_BUFFER_BIT);
	return;
}

void VNGame::VNRun()
{
	while (!glfwWindowShouldClose(mWindow->VNGetWindowPointer()))
	{
		mWindow->VNSetWindowSize(mWindow->VNGetWindowWidth(), mWindow->VNGetWindowHeight());
		//Render
		VNRenderBackground();
		glBindTexture(GL_TEXTURE_2D, mImgs[0]->VNGetImageID());
		mShader->VNUseShader();
		glBindVertexArray(mVAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//Events
		glfwPollEvents();
		//Swap buffers
		glfwSwapBuffers(mWindow->VNGetWindowPointer());
	}
	return;
}
