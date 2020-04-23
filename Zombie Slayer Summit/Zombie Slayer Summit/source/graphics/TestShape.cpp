#include <Windows.h>
#include <GL/glew.h>

#include "graphics/TestShape.h"

GLfloat vData[] = {
	-0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Top-left
	0.5f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f  // Bottom-left
};

GLuint eData[] = {
	0, 1, 2,
	2, 3, 0
};


TestShape::TestShape(Shader* shader) : Drawable()
{
	this->bindVAO();
	this->loadVertices(vData, 32);
	this->loadElements(eData, 6);
	this->positionAttribute = shader->getAttribute("position");
	this->colorAttribute = shader->getAttribute("color");
	this->uvAttribute = shader->getAttribute("uv");

	glEnableVertexAttribArray(this->positionAttribute);
	glVertexAttribPointer(this->positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(this->colorAttribute);
	glVertexAttribPointer(this->colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(this->uvAttribute);
	glVertexAttribPointer(this->uvAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	this->loadTexture(this->textureID, "test.bmp");
	this->unbindVAO();
}

bool TestShape::Draw()
{
	return Drawable::Draw(this->textureID);
}

TestShape::~TestShape()
{
}