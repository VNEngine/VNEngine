#pragma once

struct VNColor
{
	float r;
	float g;
	float b;
	float a;
};

struct VNCharacter
{
	//unsigned int vao, vbo, ebo;
	unsigned int id;
	float width;
	float height;
	float bearingX;
	float bearingY;
	float advance;
	char chr;
	float col_r;
	float col_g;
	float col_b;
	float col_a;
};
