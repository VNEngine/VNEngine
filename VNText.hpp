#pragma once

#ifndef OPENGL_INCLUDED
#include"VNLibsImport.hpp"
#endif // !OPENGL_INCLUDED

class VNText
{
public:
	VNText(const char* path, int height, const char* text, float col_r, float col_g, float col_b, float col_a);
	VNText(const char* path, int height, const char* text, VNColor col);
	~VNText();
	void VNSetTextColor(int begin, int end, int step, float col_r, float col_g, float col_b, float col_a);
	void VNSetTextColor(int begin, int end, int step, VNColor col);
	void VNSetTextColor(char chr, float col_r, float col_g, float col_b, float col_a);
	void VNSetTextColor(char chr, VNColor col);

private:
	FT_Library mFreeType;
	FT_Face mFace;
	std::vector<VNCharacter> Characters;
};

VNText::VNText(const char* path, int height, const char* text, float col_r, float col_g, float col_b, float col_a)
{
	if (FT_Init_FreeType(&mFreeType))
		std::cout << "ERROR::TEXT::FREETYPE_INITALIZING_FAILED" << std::endl;
	if (FT_New_Face(mFreeType, path, 0, &mFace))
		std::cout << "ERROR::TEXT::FACE_LOADING_FAILED" << std::endl;
	FT_Set_Pixel_Sizes(mFace, 0, height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
	int tlen = strlen(text);
	for (int i = 0; i < tlen; i++)
	{
		int chr = (int)text[i];
		if (FT_Load_Char(mFace, chr, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::TEXT::LOADING_GLYPH_FAILED" << std::endl;
			continue;
		}
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mFace->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		VNCharacter character
		{
			texture,
			mFace->glyph->bitmap.width,
			mFace->glyph->bitmap.rows,
			mFace->glyph->bitmap_left,
			mFace->glyph->bitmap_top,
			mFace->glyph->advance.x,
			chr,
			col_r,
			col_g,
			col_b,
			col_a
		};
		Characters.push_back(character);
	}
}

VNText::VNText(const char* path, int height, const char* text, VNColor col)
{
	if (FT_Init_FreeType(&mFreeType))
		std::cout << "ERROR::TEXT::FREETYPE_INITALIZING_FAILED" << std::endl;
	if (FT_New_Face(mFreeType, path, 0, &mFace))
		std::cout << "ERROR::TEXT::FACE_LOADING_FAILED" << std::endl;
	FT_Set_Pixel_Sizes(mFace, 0, height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
	int tlen = strlen(text);
	for (int i = 0; i < tlen; i++)
	{
		int chr = (int)text[i];
		if (FT_Load_Char(mFace, chr, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::TEXT::LOADING_GLYPH_FAILED" << std::endl;
			continue;
		}
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mFace->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		VNCharacter character
		{
			texture,
			mFace->glyph->bitmap.width,
			mFace->glyph->bitmap.rows,
			mFace->glyph->bitmap_left,
			mFace->glyph->bitmap_top,
			mFace->glyph->advance.x,
			chr,
			col.r,
			col.g,
			col.b,
			col.a
		};
		Characters.push_back(character);
	}
}

VNText::~VNText()
{
}

void VNText::VNSetTextColor(int begin, int end, int step, float col_r, float col_g, float col_b, float col_a)
{
	if (begin > Characters.size() || end > Characters.size() || begin < 0 || end < 0)
	{
		std::cout << "ERROR::TEXT::INDEX_OUT_OF_RANGE" << std::endl;
		return;
	}
	for (int i = begin; i <= end; i += step)
	{
		Characters[i].col_r = col_r;
		Characters[i].col_g = col_g;
		Characters[i].col_b = col_b;
		Characters[i].col_a = col_a;
	}
	return;
}

void VNText::VNSetTextColor(int begin, int end, int step, VNColor col)
{
	this->VNSetTextColor(begin, end, step, col.r, col.g, col.b, col.a);
	return;
}

void VNText::VNSetTextColor(char chr, float col_r, float col_g, float col_b, float col_a)
{
	for (int i = 0; i < Characters.size(); i++)
	{
		if (Characters[i].chr == chr)
		{
			Characters[i].col_r = col_r;
			Characters[i].col_g = col_g;
			Characters[i].col_b = col_b;
			Characters[i].col_a = col_a;
		}
	}
	return;
}

void VNText::VNSetTextColor(char chr, VNColor col)
{
	this->VNSetTextColor(chr, col.r, col.g, col.b, col.a);
	return;
}