#include <Windows.h>
#include <GL/glew.h>

#include "graphics/RoomCube.h"

GLfloat roomData[] = {
	-10.0f,  10.0f, -10.0f,		0.0f, 1.0f, 1.0f,	0, 0, // 0 Top-left-front
	10.0f,  10.0f, -10.0f,		1.0f, 0.0f, 0.0f,	0, 0, // 1 Top-right-front
	10.0f, -0.5f, -10.0f,		0.0f, 0.0f, 1.0f,	0, 0, // 2 Bottom-right-front
	-10.0f, -0.5f, -10.0f,		1.0f, 1.0f, 0.0f,	0, 0, // 3 Bottom-left-front

	-10.0f,  10.0f, 10.0f,		0.0f, 1.0f, 1.0f,	0, 0, // 4 Top-left-back
	10.0f,  10.0f, 10.0f,		1.0f, 0.0f, 0.0f,	0, 0, // 5 Top-right-back
	10.0f, -0.5f, 10.0f,		0.0f, 0.0f, 1.0f,	0, 0, // 6 Bottom-right-back
	-10.0f, -0.5f, 10.0f,		1.0f, 1.0f, 0.0f,	0, 0  // 7 Bottom-left-back
};

GLuint roomElements[] = {
	// Front
	0, 1, 2,
	2, 3, 0,

	// Back
	4, 5, 6,
	6, 7, 4,

	// Left
	4, 0, 3,
	3, 7, 4,

	// Right
	1, 5, 6,
	6, 2, 1,

	// Top
	4, 5, 1,
	1, 0, 4,

	// Bottom
	7, 6, 2,
	2, 3, 7,
};

RoomCube::RoomCube(Shader* shader) : Drawable()
{
	this->bindVAO();
	this->loadVertices(roomData, 64);
	this->loadElements(roomElements, 36);
	this->positionAttribute = shader->getAttribute("position");
	this->colorAttribute = shader->getAttribute("color");
	this->uvAttribute = shader->getAttribute("uv");

	glEnableVertexAttribArray(this->positionAttribute);
	glVertexAttribPointer(this->positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(this->colorAttribute);
	glVertexAttribPointer(this->colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(this->uvAttribute);
	glVertexAttribPointer(this->uvAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	this->unbindVAO();
}

RoomCube::~RoomCube()
{
}