#include <Windows.h>
#include <GL/glew.h>

#include "Shader.h"

using namespace std;

Shader::Shader(string vertexFileName, string fragmentFileName)
{
	this->ready = false;
	this->vertexFileName = vertexFileName;
	this->fragmentFileName = fragmentFileName;
	if (this->Load() < 1)
	{
		cout << "Error loading shader sources!" << endl;
		return;
	}
	if (this->Compile() < 1)
	{
		cout << "Error compling shader sources!" << endl;
		return;
	}
	if (this->Link() < 1)
	{
		cout << "Error linking shader sources!" << endl;
		return;
	}
	this->ready = true;
}

bool Shader::Use()
{
	if (this->ready)
	{
		glUseProgram(this->shaderProgram);
	}
	return this->ready;
}

GLint Shader::getAttribute(std::string name)
{
	return glGetAttribLocation(this->shaderProgram, name.c_str());
}

int Shader::Load()
{
	this->vertFile.open(this->vertexFileName, ios::in);
	if (!vertFile)
	{
		return -1;
	}
	this->vertexSourceStream << vertFile.rdbuf();

	this->fragFile.open(this->fragmentFileName, ios::in);
	if (!fragFile)
	{
		return -2;
	}
	this->fragmentSourceStream << fragFile.rdbuf();

	this->vertexSource = this->vertexSourceStream.str();
	this->fragmentSource = this->fragmentSourceStream.str();

	return 1;
}

int Shader::Compile()
{
	const char* tempSource = this->vertexSource.c_str();
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &tempSource, 0);
	glCompileShader(this->vertexShader);
	GLint compiled;
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* vertexCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->vertexShader, maxLength, (GLsizei*)&maxLength, vertexCompileLog);
		cout << "Vertex shader error: " << endl << vertexCompileLog << endl << endl;
		free(vertexCompileLog);
		return -1;
	}

	tempSource = this->fragmentSource.c_str();
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &tempSource, 0);
	glCompileShader(this->fragmentShader);
	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->fragmentShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* fragmentCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->fragmentShader, maxLength, (GLsizei*)&maxLength, fragmentCompileLog);
		cout << "Fragment shader error: " << endl << fragmentCompileLog << endl << endl;
		free(fragmentCompileLog);
		return -2;
	}
	return 1;
}

int Shader::Link()
{
	this->shaderProgram = glCreateProgram();

	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);
	glLinkProgram(this->shaderProgram);

	GLint linked;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &linked);
	if (linked == false)
	{
		unsigned int maxLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* programCompileLog = (char*)malloc(maxLength);
		glGetProgramInfoLog(this->shaderProgram, maxLength, (GLsizei*)&maxLength, programCompileLog);
		cout << "Program compilation error: " << endl << programCompileLog << endl << endl;
		free(programCompileLog);
		return -1;
	}
	return 1;
}
