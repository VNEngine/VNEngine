#pragma once

#ifndef OPENGL_INCLUDED
#include"VNLibsImport.hpp"
#endif // !OPENGL_INCLUDED

#define VN_SHADER_DEFAULT NULL

class VNShader
{
public:
	VNShader();
	VNShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	VNShader(VNShader* Shader);
	~VNShader();
	void VNUseShader();
	unsigned int VNGetShaderID() const;

private:
	unsigned int mId;
	const char* mVertexShaderSource;
	const char* mFragmentShaderSource;
	const char* mVertexShaderSourceDefault =
		"#version 460 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"
		"out vec3 Color;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 0.0, 1.0);\n"
		"	Color = aColor;\n"
		"	TexCoord = aTexCoord;\n"
		"}\n";

	const char* mFragmentShaderSourceDefault =
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec3 Color;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D Texture;\n"
		"void main()\n"
		"{\n"
		"	vec4 TexColor = texture(Texture, TexCoord);\n"
		"	if(TexColor.a < 0.1)\n"
		"	{\n"
		"		discard;\n"
		"	}\n"
		"	FragColor = texture(Texture, TexCoord);\n"
		"}\n";
};

VNShader::VNShader()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mVertexShaderSource = mVertexShaderSourceDefault;
	mFragmentShaderSource = mFragmentShaderSourceDefault;

	unsigned int tVertexShader, tFragmentShader;
	int tSuccess;
	char tLog[512];
	tVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(tVertexShader, 1, &mVertexShaderSource, NULL);
	glCompileShader(tVertexShader);
	glGetShaderiv(tVertexShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tVertexShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	tFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(tFragmentShader, 1, &mFragmentShaderSource, NULL);
	glCompileShader(tFragmentShader);
	glGetShaderiv(tFragmentShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tFragmentShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	mId = glCreateProgram();
	glAttachShader(mId, tVertexShader);
	glAttachShader(mId, tFragmentShader);
	glLinkProgram(mId);
	glGetProgramiv(mId, GL_LINK_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetProgramInfoLog(mId, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl << tLog << std::endl;
	}
	glDeleteShader(tVertexShader);
	glDeleteShader(tFragmentShader);
}

VNShader::VNShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	if (vertexShaderSource != VN_SHADER_DEFAULT)
	{
		mVertexShaderSource = vertexShaderSource;
	}
	else
	{
		mVertexShaderSource = mVertexShaderSourceDefault;
	}

	if (fragmentShaderSource != VN_SHADER_DEFAULT)
	{
		mFragmentShaderSource = fragmentShaderSource;
	}
	else
	{
		mFragmentShaderSource = mFragmentShaderSourceDefault;
	}

	unsigned int tVertexShader = 0, tFragmentShader = 0;
	int tSuccess = 0;
	char tLog[512];
	tVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(tVertexShader, 1, &mVertexShaderSource, NULL);
	glCompileShader(tVertexShader);
	glGetShaderiv(tVertexShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tVertexShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	tFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(tFragmentShader, 1, &mFragmentShaderSource, NULL);
	glCompileShader(tFragmentShader);
	glGetShaderiv(tFragmentShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tFragmentShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	mId = glCreateProgram();
	glAttachShader(mId, tVertexShader);
	glAttachShader(mId, tFragmentShader);
	glLinkProgram(mId);
	glGetProgramiv(mId, GL_LINK_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetProgramInfoLog(mId, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl << tLog << std::endl;
	}
	glDeleteShader(tVertexShader);
	glDeleteShader(tFragmentShader);
}

VNShader::VNShader(VNShader* shader)
{
	mVertexShaderSource = shader->mVertexShaderSource;
	mFragmentShaderSource = shader->mFragmentShaderSource;

	unsigned int tVertexShader, tFragmentShader;
	int tSuccess;
	char tLog[512];
	tVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(tVertexShader, 1, &mVertexShaderSource, NULL);
	glCompileShader(tVertexShader);
	glGetShaderiv(tVertexShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tVertexShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	tFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(tFragmentShader, 1, &mFragmentShaderSource, NULL);
	glCompileShader(tFragmentShader);
	glGetShaderiv(tFragmentShader, GL_COMPILE_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetShaderInfoLog(tFragmentShader, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << tLog << std::endl;
	}
	mId = glCreateProgram();
	glAttachShader(mId, tVertexShader);
	glAttachShader(mId, tFragmentShader);
	glLinkProgram(mId);
	glGetProgramiv(mId, GL_LINK_STATUS, &tSuccess);
	if (!tSuccess)
	{
		glGetProgramInfoLog(mId, 512, NULL, tLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl << tLog << std::endl;
	}
	glDeleteShader(tVertexShader);
	glDeleteShader(tFragmentShader);
}

VNShader::~VNShader()
{
	delete mVertexShaderSource;
	mVertexShaderSource = nullptr;
	delete mFragmentShaderSource;
	mFragmentShaderSource = nullptr;

	delete mVertexShaderSourceDefault;
	mVertexShaderSourceDefault = nullptr;
	delete mFragmentShaderSourceDefault;
	mFragmentShaderSourceDefault = nullptr;
	
	glDeleteShader(mId);
}

void VNShader::VNUseShader()
{
	glUseProgram(mId);
	return;
}

unsigned int VNShader::VNGetShaderID() const
{
	return mId;
}
