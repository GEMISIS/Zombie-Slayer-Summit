#include <Windows.h>
#include <GL/glew.h>

#include "graphics/Drawable.h"

Drawable::Drawable()
{
	this->vao = 0;
	this->vbo = 0;
	this->ebo = 0;
	glGenVertexArrays(1, &this->vao);
}

void Drawable::loadVertices(float data[], size_t size)
{
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);
}

void Drawable::loadVertices(std::vector<float> data)
{
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
}

void Drawable::loadElements(GLuint data[], size_t size)
{
	this->totalElementsCount = size;
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, data, GL_STATIC_DRAW);
}
void Drawable::loadElements(std::vector<GLuint> data)
{
	this->totalElementsCount = data.size();
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * data.size(), data.data(), GL_STATIC_DRAW);
}

void Drawable::loadTexture(GLuint& textureID, std::string fileName)
{
	SDL_Surface* texture = SDL_LoadBMP(fileName.c_str());

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic"))
	{
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(texture);
}

void Drawable::bindVAO()
{
	glBindVertexArray(this->vao);
}

void Drawable::unbindVAO()
{
	glBindVertexArray(0);
}

bool Drawable::Draw(GLuint textureID)
{
	if (!this->vao || !this->vbo || !this->ebo)
	{
		return false;
	}
	this->bindVAO();
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawElements(GL_TRIANGLES, this->totalElementsCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->unbindVAO();
	return true;
}

Drawable::~Drawable()
{
	if (this->ebo)
	{
		glDeleteBuffers(1, &this->ebo);
	}
	if (this->vbo)
	{
		glDeleteBuffers(1, &this->vbo);
	}
	glDeleteVertexArrays(1, &this->vao);
}


