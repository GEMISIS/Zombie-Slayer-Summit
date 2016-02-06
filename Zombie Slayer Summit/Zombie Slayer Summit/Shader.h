#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader(std::string vertexFileName, std::string fragmentFileName);
	bool Use();
	GLint getAttribute(std::string name);
private:
	std::ifstream vertFile, fragFile;
	std::string vertexFileName, fragmentFileName;
	std::stringstream vertexSourceStream, fragmentSourceStream;
	std::string vertexSource, fragmentSource;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	bool ready;
	int Load();
	int Compile();
	int Link();
};